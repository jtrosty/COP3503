CPP=clang++
FLAGS= -o game -g -Wall -std=c++11
LIB= lib/libraylib.a
FRAMEWORK= -framework CoreVideo -framework IOkit -framework Cocoa -framework GLUT -framework OpenGL

default:
	pushd build
	cl -Zi ../src/main.c
	popd