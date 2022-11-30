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

/// @file src/base/managers/configuration/ConfigurationBase.hh
/// @brief Pure virtual base class for containers that store configuration
/// settings for modules.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_configuration_ConfigurationBase_hh
#define Masala_src_base_managers_configuration_ConfigurationBase_hh

// Forward declarations:
#include <base/managers/configuration/ConfigurationBase.fwd.hh>

// Parent header:
#include <base/MasalaObject.hh>

// Base headers:
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>

namespace masala {
namespace base{
namespace managers{
namespace configuration{

class ConfigurationBase : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    ConfigurationBase() = delete;
    
    /// @brief MasalaConfigurationManager-authorized constructor.
    /// @details The MasalaConfigurationManagerAuthorization object is an object that only the
    /// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
    /// ConfigurationBase-derived object.
    ConfigurationBase( MasalaConfigurationManagerAuthorization const & );

    /// @brief Copy constructor.
    ConfigurationBase( ConfigurationBase const & src ) = default;

    /// @brief Default destructor.
    ~ConfigurationBase() override = default;

private:

////////////////////////////////////////////////////////////////////////////////
// DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace configuration
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_configuration_ConfigurationBase_hh
