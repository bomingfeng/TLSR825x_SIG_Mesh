@echo off
:start

echo.|set /p dir=%~dp0

set /p in=输入 1 make clean. 输入 2 make all. 输入 3 make flash. 输入 4 make monitor.
if "%in%"=="1" goto 1 
if "%in%"=="2" goto 2
if "%in%"=="3" goto 3
if "%in%"=="4" goto 4
exit

:1
echo.|cd %dir%
make clean
goto start

:2
echo.|cd %dir%
make all
goto start

:3
echo.|cd %dir%
make flash
goto start

:4
echo.|cd %dir%
make monitor
goto start