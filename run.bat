@echo off
premake5 ninja
cd Generated
ninja
cd ../Build/Bin/App/Debug
App.exe > Debug.txt
type Debug.txt