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

/// @file src/core/chemistry/MoleculesConfiguration.hh
/// @brief A container of configuration settings for a Molecules object.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MoleculesConfiguration_hh
#define Masala_src_core_chemistry_MoleculesConfiguration_hh

// Parent header
#include <base/managers/configuration/ConfigurationBase.hh>

// Project headers:
#include <core/chemistry/MoleculesConfiguration.fwd.hh>

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>

// STL headers
#include <string>

namespace masala {
namespace core {
namespace chemistry {

class MoleculesConfiguration : public masala::base::managers::configuration::ConfigurationBase {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MoleculesConfiguration() = delete;

    /// @brief MasalaConfigurationManager-authorized constructor.
    /// @details The MasalaConfigurationManagerAuthorization object is an object that only the
    /// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
    /// ConfigurationBase-derived object.
    MoleculesConfiguration( masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey );

    /// @brief Copy constructor.
    MoleculesConfiguration( MoleculesConfiguration const & src ) = default;

    /// @brief Default destructor.
    ~MoleculesConfiguration() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared_ptr to the copy.
    MoleculesConfigurationSP clone() const;

    /// @brief Deep operation: make an independent copy of this object and return a shared_ptr to the copy.
    MoleculesConfigurationSP deep_clone() const;

    /// @brief Returns "MoleculesConfiguration".
    std::string class_name() const override;

    /// @brief Returns "masla::core::chemistry".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the default kinematic representation.
    std::string const &
    default_atom_coordinate_representation() const;

private:

////////////////////////////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////////////////////////////

    /// @brief The default atom coordinate representation.
    std::string const default_atom_coordinate_representation_ = "masla::core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentation";

};

} // namespace chemistry
} // namespace core
} // namespace masala

#endif //Masala_src_core_chemistry_MoleculesConfiguration_hh
