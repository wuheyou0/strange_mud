@echo off
cmake --build build --config Release
if %errorlevel% neq 0 pause
