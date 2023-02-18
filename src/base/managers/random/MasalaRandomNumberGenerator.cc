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
// METROPOLIS-HASTINGS FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Apply the Metropolis criterion.
/// @note Incremenets random generator, to avoid knife's-edge cases that could
/// otherwise result in trajectory divergence.
/// @details The change in energy and k_B * T must be given in the same units.
/// @returns True to accept a the move that produces this delta_E, false to reject it.
bool
MasalaRandomNumberGenerator::apply_metropolis_criterion(
    base::Real const delta_E,
    base::Real const kbT
) {
    if( delta_E < 0.0 ) {
        random_engine_.discard(1); // Step forward one in the random trajectory anyways, to keep trajectory consistent if this is a knife's-edge case.
        return true;
    }
    if( kbT == 0 ) {
        return false; // Always reject increases in delta E at absolute 0.
    }
    base::Real const expval( std::exp( -delta_E / std::abs(kbT) ) );
    base::Real const comparisonval( uniform_real_distribution( 0, 1 ) );
    return expval > comparisonval;
}

/// @brief Apply the Metropolis criterion (for floating-point values.).
/// @note Incremenets random generator, to avoid knife's-edge cases that could
/// otherwise result in trajectory divergence.
/// @details The change in energy and k_B * T must be given in the same units.
/// @returns True to accept a the move that produces this delta_E, false to reject it.
bool
MasalaRandomNumberGenerator::apply_metropolis_criterion(
    float const delta_E,
    float const kbT
) {
    if( delta_E < 0.0 ) {
        random_engine_.discard(1); // Step forward one in the random trajectory anyways, to keep trajectory consistent if this is a knife's-edge case.
        return true;
    }
    if( kbT == 0 ) {
        return false; // Always reject increases in delta E at absolute 0.
    }
    float const expval( std::exp( -delta_E / std::abs(kbT) ) );
    float const comparisonval( uniform_float_distribution( 0, 1 ) );
    return expval > comparisonval;
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

/// @brief Generate a real (double-precision floating-point) number drawn from a Gaussian distribution
/// with a given mean and standard deviation.
base::Real
MasalaRandomNumberGenerator::gaussian_real_distribution(
    base::Real const mean,
    base::Real const stddev
) {
    std::normal_distribution< base::Real > gaussian_gen( mean, stddev );
    return gaussian_gen( random_engine_ );
}

/// @brief Generate a single-precision floating-point number drawn from a Gaussian distribution
/// with a given mean and standard deviation.
float
MasalaRandomNumberGenerator::gaussian_float_distribution(
    float const mean,
    float const stddev
) {
    std::normal_distribution< float > gaussian_gen( mean, stddev );
    return gaussian_gen( random_engine_ );
}

/// @brief Generate an unsigned long integer drawn from a Poisson distribution
/// with a given mean.
base::Size
MasalaRandomNumberGenerator::poisson_size_distribution(
    base::Size const mean
) {
    std::poisson_distribution< base::Size > poisson_gen( mean );
    return poisson_gen( random_engine_ );
}

/// @brief Generate a signed long integer drawn from a Poisson distribution
/// with a given mean.
signed long int
MasalaRandomNumberGenerator::poisson_signed_long_int_distribution(
    signed long int const mean
) {
    std::poisson_distribution< signed long int > poisson_gen( mean );
    return poisson_gen( random_engine_ );
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// NON-CLASS FUNCTIONS FOR CONVENIENCE
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
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

/// @brief Generate a signed long int number drawn from a Poisson distribution with a given mean.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->poisson_size_distribution( mean )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Size
poisson_size_distribution(
    base::Size const mean
) {
    return MasalaRandomNumberGenerator::get_instance()->poisson_size_distribution( mean );
}

/// @brief Generate a signed long int number drawn from a Poisson distribution with a mean of 0.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->poisson_size_distribution( 0 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Size
poisson_size_distribution() {
    return MasalaRandomNumberGenerator::get_instance()->poisson_size_distribution( 0 );
}

/// @brief Generate a signed long int number drawn from a Poisson distribution with a given mean.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->poisson_unsinged_long_int_distribution( mean )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
signed long int
poisson_singed_long_int_distribution(
    signed long int const mean
) {
    return MasalaRandomNumberGenerator::get_instance()->poisson_signed_long_int_distribution( mean );
}

/// @brief Generate a signed long int number drawn from a Poisson distribution with a mean of 0.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->poisson_unsinged_long_int_distribution( 0 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
signed long int
poisson_singed_long_int_distribution() {
    return MasalaRandomNumberGenerator::get_instance()->poisson_signed_long_int_distribution( 0 );
}

/// @brief Apply the Metropolis criterion.
/// @details This is a convenience function that calls MasalaRandomNumberGenerator::apply_metropolis_criterion()
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function directly.
/// @note The change in energy and k_B * T must be given in the same units.
/// @returns True to accept a the move that produces this delta_E, false to reject it.
bool
apply_metropolis_criterion(
    base::Real const delta_E,
    base::Real const kbT
) {
    return MasalaRandomNumberGenerator::get_instance()->apply_metropolis_criterion( delta_E, kbT );
}

/// @brief Apply the Metropolis criterion (for floating-point values.).
/// @details This is a convenience function that calls MasalaRandomNumberGenerator::apply_metropolis_criterion()
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function directly.
/// @note The change in energy and k_B * T must be given in the same units.
/// @returns True to accept a the move that produces this delta_E, false to reject it.
bool
apply_metropolis_criterion(
    float const delta_E,
    float const kbT
) {
    return MasalaRandomNumberGenerator::get_instance()->apply_metropolis_criterion( delta_E, kbT );
}

} // namespace random
} // namespace managers
} // namespace base
} // namespace masala
