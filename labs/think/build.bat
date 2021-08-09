@echo off

mkdir build
pushd build

g++ ..\thinkProblems.cpp -o thinkProblems 

thinkProblems.exe

popd

rem # Compile a single program
rem g++ -Wall -g -std=c++17 test.cpp -o test

rem # Print all possible warning flags available to compile with
rem g++ --help=warnings

rem # Compile program using header files in ./libs
rem # $(pwd) will expand to your current working directory
rem g++ -I /$(pwd)/libs -Wall -g -std=c++17 test.cpp -o test

rem # Compile and optimize in parallel for helpful warnings about potential bugs
rem g++ -O2 -Wall -std=c++17 main.cpp -o main

rem -Wall show all warnings. It turns on all standard C++ warnings about code that might cause unexpected or undefined behavior.
rem -g provides debugging feature for your program. You will need this when you want to use gdb or valgrind.
rem --std=c++<##> uses version <##> of C++ when compiling. This will allow you to use specific features of that C++ version. Typically, we have you use --std=c++17.
rem -o <filename> compiles and links files into an executable named <filename>. The default filename is a.out.
rem -c compiles and assembles files but doesn’t link them. This is useful when building large projects to separate file compilation and minimize what is re-compiled.
rem
rem BOUNUS ROUND OF STUFF
rem --sys-root=<directory> uses <directory> as root directory for headers and libraries.
rem -I /<absolute-path> adds <absolute-path> to the compiler’s search paths. The path must written from the root of the filesystem, /.
rem -Werror make all warnings into errors do this before submitting your code to avoid getting points deducted!
rem -pedantic issues all warnings demanded by strict ISO C++ rules if you want to be extra safe
rem -Wextra enables some extra warnings not turned on by -Wall. These include warnings for bad pointer to integer zero comparisons, base class not initialized in copy constructor of derived class, etc.
rem -Wfatal-errors is similar to -Wall but treats an error as fatal and stops before dumping a long list of errors into the terminal.
rem -fmax-errors=n tells the compiler to stop after encountering n errors in your code. Usually you want to see all errors in your code some error messages may get too long for you to read.
rem -Wshadow warns whenever a local variable or type declaration shadows another variable, parameter, class member, etc.
rem -Wsign-conversion or -Wconversion warn if making unsafe, implicit conversions between signed and unsigned types (i.e. unsigned int + (constant expression) )
rem -O2 optimize code and check for errors in parallel to find potential bugs. (read more about this here)
rem --help gets help on specific options for the compiler.
