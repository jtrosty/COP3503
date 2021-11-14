@echo off

REM TODO  - can we just build both with one exe? 

subst x: C:\Users\Trost\Documents\0-CS\code
call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
set path = w:\dsa\p1;%path%



