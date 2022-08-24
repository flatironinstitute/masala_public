mkdir bin && echo "Created bin/ directory." || echo "Directory bin/ already exists."
mkdir build && echo "Created build/ directory." || echo "Directory build/ already exists."
cd build
mkdir cmake_generated && echo "Created build/cmake_generated/ sub-directory." || echo "Sub-directory build/cmake_generated/ already exists."
cmake ../cmake/
make -j `nproc` && echo "Build completed.  Executables may be found in the bin/ directory." || echo "Build errors!  Check output log."
cd ..
