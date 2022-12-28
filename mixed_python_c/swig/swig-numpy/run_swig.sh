#!/bin/sh

swig -python simple.i
python setup.py build_ext
python setup.py install --install-platlib=.
python test.py

# Uncomment below if you don't want to run with distutils

# #!/bin/sh

# swig -python simple.i
# gcc -I/home/pavithra/Desktop/sublimeTesting/mixed_python_c/swig/venv/lib/python3.6/site-packages/numpy/core/include -fPIC $(pkg-config --cflags --libs python3) -c simple.c simple_wrap.c
# gcc -shared -fPIC -o _simple.so simple.o simple_wrap.o
# python3 test.py 

