mkdir bin && echo "Created bin/ directory." || echo "Directory bin/ already exists."
mkdir build && echo "Created build/ directory." || echo "Directory build/ already exists."
mkdir catch2_build && echo "Created catch2_build/ directory." || echo "Directory catch2_build/ already exists."
cd catch2_build
cmake ../external/catch2/
make -j `nproc` && echo "Built Catch2." || echo "Error building Catch2!  Check output log."
cd ..
cd build
mkdir cmake_generated && echo "Created build/cmake_generated/ sub-directory." || echo "Sub-directory build/cmake_generated/ already exists."
cmake ../cmake/
make -j `nproc` && echo "Build completed." || echo "Build errors!  Check output log."
cd ..
