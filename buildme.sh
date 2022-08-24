mkdir bin
mkdir build
cd build
mkdir cmake_generated
python3 ../cmake/generate_cmake_build.py base ../src/base cmake_generated/base.cmake
python3 ../cmake/generate_cmake_build.py numeric ../src/numeric cmake_generated/numeric.cmake
python3 ../cmake/generate_cmake_build.py core ../src/core cmake_generated/core.cmake
cmake ../cmake/
make -j `nproc` && echo "Build completed.  Executables may be found in the bin/ directory." || echo "Build errors!  Check output log."
cd ..
