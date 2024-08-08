@echo off
REM Build the executable

REM Build the DLL
i686-w64-mingw32-gcc -Wl,--kill-at -shared -I "th155r/Netcode/include" -o  ..\..\thcrap\bin\Netcode.dll th155r/Netcode/*.cpp th155r/Netcode/squirrel/*.cpp -std=c++20 -lstdc++ -lws2_32 -Wno-narrowing 
REM i686-w64-mingw32-gcc -g -Wl,--exclude-all-symbols,--kill-at -shared -I th155r\Netcode\include -o ..\..\thcrap\bin\Netcode.dll th155r/Netcode/*.cpp -std=c++20 -lstdc++ -Wno-narrowing

IF ERRORLEVEL 1 (
    echo Failed to build Netcode.dll
    exit /b 1
)

echo Build completed successfully.
