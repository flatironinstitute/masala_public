mkdir bin
mkdir build
cd build
cmake ../cmake/
make . -j `nproc`
cd ..
echo "Build completed.  Executables may be found in the bin/ directory."
