#!/bin/sh

swig -python hw.i
gcc -fPIC $(pkg-config --cflags --libs python3) -c hw.c hw_wrap.c
gcc -shared -fPIC -o _hw.so hw.o hw_wrap.o
python3 test.py 