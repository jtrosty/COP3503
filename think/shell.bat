@echo off

REM TODO  - can we just build both with one exe? 

REM subst w: C:\Users\Trost\Documents\0-CS\Projects
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x86
set path = C:\Users\Trost\Documents\0-CS\code\COP3503;%path%
