mkdir bin && echo "Created bin/ directory." || echo "Directory bin/ already exists."
mkdir build && echo "Created build/ directory." || echo "Directory build/ already exists."
cd build
mkdir cmake_generated && echo "Created build/cmake_generated/ sub-directory." || echo "Sub-directory build/cmake_generated/ already exists."
cmake ../cmake/
make -j `nproc` && echo "Build completed." || echo "Build errors!  Check output log."
cd ..
mkdir headers && echo "Created headers/ directory." || echo "Directory headers/ already exists."
rm -r headers/*
python3 ./cmake/copy_headers.py base src headers
python3 ./cmake/copy_headers.py base_api src headers
#python3 ../cmake/copy_headers.py numeric_api
python3 ./cmake/copy_headers.py core_api src headers