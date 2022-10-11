/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file tests/unit/core/pose/PoseUnitTests.cc
/// @brief Unit tests for the Pose class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#define CATCH_CONFIG_MAIN

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <core/pose/Pose.hh>

namespace masala {
namespace tests {
namespace unit {
namespace core {
namespace pose {

TEST_CASE( "Instantiate a pose", "[core::pose::Pose][Instantiation]" ) {
    REQUIRE_NOTHROW([&](){
        std::make_shared< masala::core::pose::Pose >();
    }() );
}

} // namespace pose
} // namespace core
} // namespace unit
} // namespace tests
} // namespace masala
