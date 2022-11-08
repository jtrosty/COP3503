@echo off

pushd debug
    cl ../lfsr.cpp -Zi -o lfsr
popd