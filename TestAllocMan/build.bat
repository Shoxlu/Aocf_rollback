@echo off
REM Build the executable
i686-w64-mingw32-g++ -g -std=c++20 -lstdc++ -o testAllocMan.exe ./*.cpp 
IF ERRORLEVEL 1 (
    echo Failed to build th155r.exe
    exit /b 1
)

echo Build completed successfully.
