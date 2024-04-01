@echo off
premake5 gmake2
cd Generated
make
cd ../Build/Bin/App/Debug
App.exe