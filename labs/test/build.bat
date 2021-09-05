@echo off
if not exist build mkdir build
pushd build
g++ ..\src\main.cpp -o main.exe
popd