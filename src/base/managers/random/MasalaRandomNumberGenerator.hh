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

/// @file src/base/managers/random/MasalaRandomNumberGenerator.hh
/// @brief Headers for a static singleton for generating random numbers, with unique random seeds
/// for each process and thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_random_MasalaRandomNumberGenerator_hh
#define Masala_src_base_managers_random_MasalaRandomNumberGenerator_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/random/MasalaRandomNumberGenerator.fwd.hh>

// Base headers:
#include <base/types.hh>

// STL headers:
#include <random>

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
);

/// @brief Get a random signed long integer uniformly distributed in the range [beginrange, endrange].
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_signed_long_int_distribution( beginrange, endrange )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
signed long int
uniform_signed_long_int_distribution(
    signed long int const beginrange,
    signed long int const endrange
);

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
);

/// @brief Generate a real (double-precision floating-point) number uniformly drawn from the
/// interval [0, 1).
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_real_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
uniform_real_distribution();

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
);

/// @brief Generate a single-precision floating-point number uniformly drawn from the
/// interval [0, 1).
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->uniform_float_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
uniform_float_distribution();

/// @brief Generate a real (double-precision floating-point) number drawn from a Gaussian distribution
/// with mean and standard deviation given by mean and stddev, respectively.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( mean, stddev )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
gaussian_real_distribution(
    base::Real const mean,
    base::Real const stddev
);

/// @brief Generate a real (double-precision floating-point) number drawn from a Gaussian distribution
/// with mean 0 and standard deviation 1.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
gaussian_real_distribution();

/// @brief Generate a single-precision floating-point number drawn from a Gaussian distribution
/// with mean and standard deviation given by mean and stddev, respectively.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( mean, stddev )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
gaussian_float_distribution(
    float const mean,
    float const stddev
);

/// @brief Generate a single-precision floating-point number drawn from a Gaussian distribution
/// with mean 0 and standard deviation 1.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( 0, 1 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
gaussian_float_distribution();

/// @brief Generate a real (double-precision floating-point) number drawn from a Poisson distribution
/// with a given mean.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( mean )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
poisson_real_distribution(
    base::Real const mean
);

/// @brief Generate a real (double-precision floating-point) number drawn from a Poisson distribution
/// with mean 0.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_real_distribution( 0 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
base::Real
poisson_real_distribution();

/// @brief Generate a single-precision floating-point number drawn from a Poisson distribution
/// with a given mean.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( mean )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
poisson_float_distribution(
    float const mean
);

/// @brief Generate a single-precision floating-point number drawn from a Poisson distribution
/// with mean 0.
/// @details This is a convenience function that calls
/// MasalaRandomNumberGenerator::get_instance()->gaussian_float_distribution( 0 )
/// under the hood, to save developer typing.  For repeated calls, it is more efficient to get a handle to the
/// random generator and call the class member function.
float
poisson_float_distribution();

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// CLASS MasalaRandomNumberGenerator
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/// @brief A static singleton for generating random numbers, with unique random seeds
/// for each process and thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaRandomNumberGenerator : public masala::base::MasalaObject {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaRandomNumberGeneratorHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor: object can only be instantiated with getInstance().
    /// @details Sets seed value by time perturbed by thread index.
    MasalaRandomNumberGenerator();

    /// @brief Private constructor with seed: object can only be instantiated with getInstance().
    MasalaRandomNumberGenerator( base::Size const seed_value );

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaRandomNumberGenerator( MasalaRandomNumberGenerator const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaRandomNumberGenerator const & ) = delete;

    /// @brief Default destructor.
    ~MasalaRandomNumberGenerator() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaRandomNumberGenerator".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::random".
    std::string
    class_namespace() const override;

////////////////////////////////////////////////////////////////////////////////
// RANDOM NUMBER GENERATING FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get a random unsigned integer uniformly distributed in the range [beginrange, endrange].
    base::Size
    uniform_size_distribution(
        base::Size const beginrange,
        base::Size const endrange
    );

    /// @brief Get a random signed long integer uniformly distributed in the range [beginrange, endrange].
    signed long int
    uniform_signed_long_int_distribution(
        signed long int const beginrange,
        signed long int const endrange
    );

    /// @brief Generate a real (double-precision floating-point) number uniformly drawn from the
    /// interval [beginrange, endrange).
    base::Real
    uniform_real_distribution(
        base::Real const beginrange,
        base::Real const endrange
    );

    /// @brief Generate a single-precision floating-point number uniformly drawn from the
    /// interval [beginrange, endrange).
    float
    uniform_float_distribution(
        float const beginrange,
        float const endrange
    );

    /// @brief Generate a real (double-precision floating-point) number drawn from a Gaussian distribution
    /// with a given mean and standard deviation.
    base::Real
    gaussian_real_distribution(
        base::Real const mean,
        base::Real const stddev
    );

    /// @brief Generate a single-precision floating-point number drawn from a Gaussian distribution
    /// with a given mean and standard deviation.
    float
    gaussian_float_distribution(
        float const mean,
        float const stddev
    );

    /// @brief Generate a real (double-precision floating-point) number drawn from a Poisson distribution
    /// with a given mean.
    base::Real
    poisson_real_distribution(
        base::Real const mean
    );

    /// @brief Generate a single-precision floating-point number drawn from a Poisson distribution
    /// with a given mean.
    float
    poisson_float_distribution(
        float const mean
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief The actual random generator is the STL's mt19937_64 engine, which uses the
    /// Mersenne Twister algorithm, has 2^64 = 1.8*10^19 unique seeds and trajectories, and
    /// has trajectories with repeat lengths of 2^19937 - 1 calls.
    std::mt19937_64 random_engine_;

};

} // namespace random
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_random_MasalaRandomNumberGenerator_hh