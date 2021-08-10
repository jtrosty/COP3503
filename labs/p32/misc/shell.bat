@echo off

REM TODO  - can we just build both with one exe? 

subst w: C:\Users\Trost\Documents\0-CS\code\cop3503
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path = w:\labs\p3noSFML;%path%



