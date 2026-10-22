@echo off
cd /d "%~dp0"
if not exist build\OnlineCourseManagement.exe call build_windows.bat
if exist build\OnlineCourseManagement.exe build\OnlineCourseManagement.exe
pause
