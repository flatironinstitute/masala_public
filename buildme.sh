mkdir bin && echo "Created bin/ directory." || echo "Directory bin/ already exists."
mkdir build && echo "Created build/ directory." || echo "Directory build/ already exists."
cd build
mkdir cmake_generated && echo "Created build/cmake_generated/ sub-directory." || echo "Sub-directory build/cmake_generated/ already exists."
cmake ../cmake/
make -j `nproc` && echo "Build completed." || echo "Build errors!  Check output log."
cd ..
mkdir headers && echo "Created headers/ directory." || echo "Directory headers/ already exists."
cd headers && rm -r *
python3 ../cmake/copy_headers.py base ../src ./
#python3 ../cmake/copy_headers.py numeric_api
python3 ../cmake/copy_headers.py core_api ../src ./
cd ..