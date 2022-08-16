@echo off

@echo off
pushd debug
    cl /Zi -nologo /EHsc /INCREMENTAL w:\src\chip8.cpp w:\src\Renderer.cpp w:\src\main.cpp -o main /I "C:\Users\MIDNT\Documents\0-CS\code\SDL2\include" /link /LIBPATH:C:\Users\MIDNT\Documents\0-CS\code\SDL2\lib\x64 SDL2.lib SDL2main.lib SDL2.lib SDL2_image.lib user32.lib shell32.lib /SUBSYSTEM:CONSOLE
popd