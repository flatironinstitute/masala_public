/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

/// @file src/base/managers/engine/MasalaRandomNumberGenerator.cc
/// @brief Implementations for a static singleton for generating random numbers, with unique random seeds
/// for each process and thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/random/MasalaRandomNumberGenerator.hh>

// Base headers:
#include <base/managers/threads/MasalaThreadManager.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <chrono>

namespace masala {
namespace base {
namespace managers {
namespace random {

////////////////////////////////////////////////////////////////////////////////
// NON-CLASS FUNCTIONS FOR CONVENIENCE
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a random unsigned integer uniformly distributed in the range [beginrange, endrange].
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_size_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Size
uniform_size_distribution(
    base::Size const beginrange,
    base::Size const endrange
) {
    return MasalaRandomNumberGenerator::get_instance()->uniform_size_distribution( beginrange, endrange );
}

/// @brief Get a random signed long integer uniformly distributed in the range [beginrange, endrange].
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_signed_long_int_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
signed long int
uniform_signed_long_int_distribution(
    signed long int const beginrange,
    signed long int const endrange
) {
    return MasalaRandomNumberGenerator::get_instance()->uniform_signed_long_int_distribution( beginrange, endrange );
}

/// @brief Generate a real (double-precision floating-point) number uniformly drawn from the
/// interval [beginrange, endrange).
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_real_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
uniform_real_distribution(
    base::Real const beginrange,
    base::Real const endrange
) {
    return MasalaRandomNumberGenerator::get_instance()->uniform_real_distribution( beginrange, endrange );
}

/// @brief Generate a real (double-precision floating-point) number uniformly drawn from the
/// interval [0, 1).
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_real_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
uniform_real_distribution() {
    return MasalaRandomNumberGenerator::get_instance()->uniform_real_distribution( 0, 1 );
}

/// @brief Generate a single-precision floating-point number uniformly drawn from the
/// interval [beginrange, endrange).
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_float_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
uniform_float_distribution(
    float const beginrange,
    float const endrange
) {
    return MasalaRandomNumberGenerator::get_instance()->uniform_float_distribution( beginrange, endrange );
}

/// @brief Generate a single-precision floating-point number uniformly drawn from the
/// interval [0, 1).
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_float_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
uniform_float_distribution() {
    return MasalaRandomNumberGenerator::get_instance()->uniform_float_distribution( 0, 1 );
}

/// @brief Generate a real (double-precision floating-point) number drawn from a gaussian distribution
/// with mean and standard deviation given by mean and stddev, respectively.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
gaussian_real_distribution(
    base::Real const mean,
    base::Real const stddev
) {
    return MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( mean, stddev );
}

/// @brief Generate a real (double-precision floating-point) number drawn from a gaussian distribution
/// with mean 0 and standard deviation 1.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
gaussian_real_distribution() {
    return MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( 0, 1 );
}

/// @brief Generate a single-precision floating-point number drawn from a gaussian distribution
/// with mean and standard deviation given by mean and stddev, respectively.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
gaussian_float_distribution(
    float const mean,
    float const stddev
) {
    return MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( mean, stddev );
}

/// @brief Generate a single-precision floating-point number drawn from a gaussian distribution
/// with mean 0 and standard deviation 1.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
gaussian_float_distribution() {
    return MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( 0, 1 );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// CLASS MasalaRandomNumberGenerator
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Instantiate the static singleton and get a handle to it.
MasalaRandomNumberGeneratorHandle
MasalaRandomNumberGenerator::get_instance() {
    static thread_local MasalaRandomNumberGenerator random_generator;
    return &random_generator;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor: object can only be instantiated with getInstance().
/// @details Sets seed value by time perturbed by thread index.
MasalaRandomNumberGenerator::MasalaRandomNumberGenerator() :
    masala::base::MasalaObject()
{
    base::Size const thread_id( base::managers::threads::MasalaThreadManager::get_instance()->get_thread_manager_thread_id() );
    base::Size const clock_ticks( std::chrono::high_resolution_clock::now().time_since_epoch().count() );
    random_engine_.seed( thread_id * 10000 + clock_ticks );
}

/// @brief Private constructor with seed: object can only be instantiated with getInstance().
MasalaRandomNumberGenerator::MasalaRandomNumberGenerator(
    base::Size const seed_value
) :
    masala::base::MasalaObject(),
    random_engine_( seed_value )
{
    // Note that we can't use write_to_tracer() from a constructor.
    masala::base::managers::tracer::MasalaTracerManagerHandle const tracer_handle( masala::base::managers::tracer::MasalaTracerManager::get_instance() );
    std::string const tracername( "masala::base::managers::random::MasalaRandomNumberGenerator" );
    if( tracer_handle->tracer_is_enabled( tracername ) ) {
        tracer_handle->write_to_tracer( tracername, "Initialized random generator with seed value " + std::to_string( seed_value ) + ".", true );
    }
}


////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaRandomNumberGenerator".
std::string
MasalaRandomNumberGenerator::class_name() const {
    return "MasalaRandomNumberGenerator";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::random".
std::string
MasalaRandomNumberGenerator::class_namespace() const {
    return "masala::base::managers::random";
}

////////////////////////////////////////////////////////////////////////////////
// RANDOM NUMBER GENERATING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get a random unsigned integer uniformly distributed in the range [beginrange, endrange].
base::Size
MasalaRandomNumberGenerator::uniform_size_distribution(
    base::Size const beginrange,
    base::Size const endrange
) {
    std::uniform_int_distribution< base::Size > int_gen( beginrange, endrange );
    return int_gen( random_engine_ );
}

/// @brief Get a random signed long integer uniformly distributed in the range [beginrange, endrange].
signed long int
MasalaRandomNumberGenerator::uniform_signed_long_int_distribution(
    signed long int const beginrange,
    signed long int const endrange
) {
    std::uniform_int_distribution< signed long int > int_gen( beginrange, endrange );
    return int_gen( random_engine_ );
}

/// @brief Generate a real (double-precision floating-point) number uniformly drawn from the
/// interval [beginrange, endrange).
base::Real
MasalaRandomNumberGenerator::uniform_real_distribution(
    base::Real const beginrange,
    base::Real const endrange
) {
    std::uniform_real_distribution< base::Real > real_gen( beginrange, endrange );
    return real_gen( random_engine_ );
}

/// @brief Generate a single-precision floating-point number uniformly drawn from the
/// interval [beginrange, endrange).
float
MasalaRandomNumberGenerator::uniform_float_distribution(
    float const beginrange,
    float const endrange
) {
    std::uniform_real_distribution< float > real_gen( beginrange, endrange );
    return real_gen( random_engine_ );
}

} // namespace random
} // namespace managers
} // namespace base
} // namespace masala
