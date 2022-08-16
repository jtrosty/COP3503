@echo off
pushd debug
    cl /Zi -nologo /EHsc /INCREMENTAL w:\src\chip8.cpp w:\src\Renderer.cpp w:\src\main.cpp -o main /I "C:\Users\MIDNT\Documents\0-CS\code\SDL2\include" /link /LIBPATH:C:\Users\MIDNT\Documents\0-CS\code\SDL2\lib\x64 SDL2.lib SDL2main.lib SDL2.lib SDL2_image.lib user32.lib shell32.lib /SUBSYSTEM:CONSOLE
    main.exe
popd

REM Compiler Flags:
REM -DDISABLE_TESTS flag
REM Zi  : debug info (Z7 older debug format for complex builds)
REM Zo  : More debug info for optimized builds
REM FC  : Full path on errors
REM Oi  : Always do intrinsics with you can
REM Od  : No optimizations
REM O2  : Full optimizations
REM MT  : Use the c static lib instead of searching for dll at run-time
REM MTd : Sabe as MT but using the debug version of CRT
REM GR- : Turn off C++ run-time type info
REM Gm- : Turn off incremental build
REM EHa-: Turn off exception handling
REM WX  : Treat warning as errors
REM W4  : Set Warning level to 4 (Wall to all levels)
REM wd  : Ignore warning
REM fp:fast    : Ignores the rules in some cases to optimize fp operations
REM Fmfile.map : Outputs a map file (mapping of the functions on the exr)

REM Linker Options:

REM subsystem:windows,5.1 : Make exe compatible with Windows XP (only works on x86)
REM opt:ref               : Don't put unused things in the exe
REM incremental:no        : Don't need to do incremental builds
REM LD                    : Build a dll
REM PDB:file.pdb          : Change the .pdb's path
popd