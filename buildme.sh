#!/bin/bash
mkdir bin && echo "Created bin/ directory." || echo "Directory bin/ already exists."
mkdir bin/tests && echo "Created bin/tests directory." || echo "Directory bin/tests already exists."
mkdir bin/api && echo "Created bin/api directory." || echo "Directory bin/api already exists."
mkdir build && echo "Created build/ directory." || echo "Directory build/ already exists."
cd build
mkdir cmake_generated && echo "Created build/cmake_generated/ sub-directory." || echo "Sub-directory build/cmake_generated/ already exists."
cmake ../cmake/
make -j `nproc`

test "${PIPESTATUS[0]}" != '0' && { echo "Build errors!  Check output log for details."; exit 1; } || { echo "Build completed."; }

cd ..
mkdir headers && echo "Created headers/ directory." || echo "Directory headers/ already exists."
rm -r headers/*
cd headers && ln -s ../external && cd ..
python3 ./code_templates/copy_headers.py masala base src headers
python3 ./code_templates/copy_headers.py masala numeric_api src headers
python3 ./code_templates/copy_headers.py masala core_api src headers
python3 ./code_templates/copy_headers.py masala numeric src headers

cd bin/tests
ln -s ../../build/base_tests ./
ln -s ../../build/numeric_tests ./
ln -s ../../build/core_tests ./
cd ../api
ln -s ../../build/generate_numeric_api ./
ln -s ../../build/generate_core_api ./
cd ../..

echo "Finished building project and copying headers."
