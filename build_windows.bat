@echo off
cd /d "%~dp0"
if not exist build mkdir build
g++ -std=c++11 -Wall -Wextra Source_Code\main.cpp Source_Code\Student.cpp Source_Code\Course.cpp Source_Code\Instructor.cpp Source_Code\Enrollment.cpp Source_Code\FileManager.cpp Source_Code\CourseSystem.cpp -o build\OnlineCourseManagement.exe
if errorlevel 1 (echo Build failed. Check the error above. & pause & exit /b 1)
echo Build successful.
pause
