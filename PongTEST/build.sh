mkdir build-psp
psp-cmake -S . -B build-psp
cd build-psp/
make clean
make
