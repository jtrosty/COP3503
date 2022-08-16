@echo off

REM TODO  - can we just build both with one exe? 

subst w: C:\Users\MIDNT\Documents\0-CS\code\school\chip8
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
REM call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\Common7\Tools\vsdevcmd.bat" 
set path = w:;%path%
