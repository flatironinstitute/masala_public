mkdir bin && echo "Created bin/ directory." || echo "Directory bin/ already exists."
mkdir build && echo "Created build/ directory." || echo "Directory build/ already exists."
cd build
mkdir cmake_generated && echo "Created build/cmake_generated/ sub-directory." || echo "Sub-directory build/cmake_generated/ already exists."
cmake ../cmake/
make -j `nproc` && echo "Build completed." || echo "Build errors!  Check output log."
cd ..
mkdir headers && echo "Created headers/ directory." || echo "Directory headers/ already exists."
rm -r headers/*
cd headers && ln -s ../external && cd ..
python3 ./code_templates/copy_headers.py masala base src headers
python3 ./code_templates/copy_headers.py masala numeric_api src headers
python3 ./code_templates/copy_headers.py masala core_api src headers
