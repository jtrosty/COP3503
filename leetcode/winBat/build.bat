@echo off

pushd debug
    pwd
    cl ../main1.cpp -Zi -o main1
    REM cl C:\Users\MIDNT\Documents\0-CS\code\school\leetcode\main1.cpp -Zi -o main1
popd