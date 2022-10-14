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

/// @file tests/unit/base/masla/threads/MasalaThreadManagerTests.cc
/// @brief Unit tests for the Masala thread manager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/managers/threads/MasalaThreadManager.hh>
#include <base/managers/threads/MasalaThreadedWorkRequest.hh>
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>

// STL headers:
#include <vector>

namespace masala {
namespace tests {
namespace unit {
namespace base {
namespace managers {
namespace threads {

TEST_CASE( "Launch one child thread.", "[base::managers::threads::MasalaThreadManager][multi-threading][instantiation]" ) {
    using namespace masala::base::managers::threads;
    REQUIRE_NOTHROW([&](){
        MasalaThreadManagerHandle tm = MasalaThreadManager::get_instance();
        tm->set_total_threads(2);
        tm->set_total_threads(1);
    }() );
}

TEST_CASE( "Launch two child threads.", "[base::managers::threads::MasalaThreadManager][multi-threading][instantiation]" ) {
    using namespace masala::base::managers::threads;
    REQUIRE_NOTHROW([&](){
        MasalaThreadManagerHandle tm = MasalaThreadManager::get_instance();
        tm->set_total_threads(3);
        tm->set_total_threads(1);
    }() );
}

/// @brief A thread function for the "Do some work in four threads total" test case.
/// @details Figures out one billion times 1, 2, 3, or 4 in the worst possible way (by adding
/// 1, 2, 3, or 4 one billion times) and stores the result in a 4-vector.
void
thread_function1(
    std::vector< masala::base::Size > & results,
    masala::base::Size const job_index
) {
    results[job_index] = 0;
    masala::base::Size const increment( job_index + 1 );
    for( masala::base::Size i(1); i <= 100000000; ++i ) {
        results[job_index] += increment;
    }
    masala::base::managers::tracer::MasalaTracerManager::get_instance()->write_to_tracer(
        "MasalaThreadManagerTests", "Completed work for job " + std::to_string(job_index) +
        " in thread " + std::to_string( masala::base::managers::threads::MasalaThreadManager::get_instance()->get_thread_manager_thread_id_from_system_thread_id( std::this_thread::get_id() ) ) + "."
    );
}

TEST_CASE( "Do some work in four threads total.", "[base::managers::threads::MasalaThreadManager][multi-threading][instantiation]" ) {
    using namespace masala::base::managers::threads;
    using namespace masala::base::managers::tracer;

    std::vector< masala::base::Size > vec(4);
    MasalaThreadedWorkExecutionSummary summary;

    MasalaTracerManagerHandle const tracer( MasalaTracerManager::get_instance() );

    REQUIRE_NOTHROW([&](){
        MasalaThreadManagerHandle tm = MasalaThreadManager::get_instance();
        MasalaThreadedWorkRequest request(4);
        request.reserve(4);
        for( masala::base::Size i(0); i<4; ++i ) {
            request.add_job( std::bind( thread_function1, std::ref(vec), i ) );
        }

        tm->set_total_threads(4);
        summary = tm->do_work_in_threads( request );
    }() );

    //Check that the work was done properly:
    tracer->write_to_tracer( "MasalaThreadManagerTests", "Vector output:" );
    for( masala::base::Size i(0); i<4; ++i ) {
        CHECK( vec[i] == (i+1)*100000000 );
        tracer->write_to_tracer( "MasalaThreadManagerTests", std::to_string(vec[i]) );
    }

    tracer->write_to_tracer( "MasalaThreadManagerTests", "Execution time (us):\t" + std::to_string( summary.execution_time_microseconds() ) );
    tracer->write_to_tracer( "MasalaThreadManagerTests", "Number of assigned threads:\t" + std::to_string( summary.nthreads_actual() ) );

    REQUIRE_NOTHROW([&](){
        MasalaThreadManagerHandle tm = MasalaThreadManager::get_instance();
        tm->set_total_threads(1);
    }() );
}

} // namespace threads
} // namespace managers
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
