@echo off

pushd Othello
    cl ../Othello/test/test.cpp -Zi -o othello
    othello.exe

    REM cl C:\Users\MIDNT\Documents\0-CS\code\school\leetcode\main1.cpp -Zi -o main1
popd