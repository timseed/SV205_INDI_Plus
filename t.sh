#!/bin/bash
rm -Rf build
mkdir build && cd build && cmake .. && make 
indiserver -v ./build/libsv205_plus.so
