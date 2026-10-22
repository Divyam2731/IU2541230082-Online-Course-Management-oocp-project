#!/usr/bin/env python3
"""Compile and smoke-test the project. Full manual cases remain in TEST_RESULTS.txt."""
import shutil, subprocess, tempfile
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/"Source_Code"
CPP_FILES=[SOURCE/"main.cpp"]+sorted(p for p in SOURCE.glob("*.cpp") if p.name!="main.cpp")
def main():
    compiler=shutil.which("g++")
    if not compiler:
        print("SKIP: g++ not found; install GCC/MinGW.")
        return 2
    with tempfile.TemporaryDirectory() as td:
        exe=Path(td)/"project_test"
        build=subprocess.run([compiler,"-std=c++11","-Wall","-Wextra"]+[str(p) for p in CPP_FILES]+["-o",str(exe)],capture_output=True,text=True,timeout=45)
        if build.returncode:
            print("FAIL: compilation failed"); print(build.stdout); print(build.stderr); return 1
        print("PASS: compilation completed")
        work=Path(td)/"run"; work.mkdir(); (work/"Data").mkdir()
        user_input="77\n9\n"
        run=subprocess.run([str(exe)],input=user_input,capture_output=True,text=True,cwd=work,timeout=5)
        if run.returncode or "Choose an option from" not in run.stdout:
            print("FAIL: invalid-menu check"); print(run.stdout); print(run.stderr); return 1
        if "Goodbye" not in run.stdout:
            print("FAIL: clean exit check"); print(run.stdout); return 1
        print("PASS: invalid menu is handled and application exits")
        print("NOTE: full manual test cases still require student execution.")
        return 0
if __name__=="__main__":
    raise SystemExit(main())
