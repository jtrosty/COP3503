@echo off

pushd ..\debug
rm ../main
cl ../main.cpp -Zi -o main
popd