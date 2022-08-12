@echo off

pushd ..\debug
rm ../main1
cl ../main1.cpp -Zi -o main1
popd