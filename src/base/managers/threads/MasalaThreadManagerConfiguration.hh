/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/base/managers/threads/MasalaThreadManagerConfiguration.hh
/// @brief A container of configuration settings for the MasalaThreadManager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_hh
#define Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_hh

// Parent header
#include <base/managers/configuration/ConfigurationBase.hh>

// Project headers:
#include <base/managers/threads/MasalaThreadManagerConfiguration.fwd.hh>

// Base headers
#include <base/managers/configuration/MasalaConfigurationManagerAuthorization.fwd.hh>
#include <base/types.hh>

// STL headers
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief A container of configuration settings for the MasalaThreadManager singleton.
class MasalaThreadManagerConfiguration : public masala::base::managers::configuration::ConfigurationBase {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaThreadManagerConfiguration() = delete;

    /// @brief MasalaConfigurationManager-authorized constructor.
    /// @details The MasalaConfigurationManagerAuthorization object is an object that only the
    /// MasalaConfigurationManager can create.  One needs to have one in hand to instantiate a
    /// ConfigurationBase-derived object.
    MasalaThreadManagerConfiguration( masala::base::managers::configuration::MasalaConfigurationManagerAuthorization const & passkey );

    /// @brief Copy constructor.
    MasalaThreadManagerConfiguration( MasalaThreadManagerConfiguration const & src ) = default;

    /// @brief Default destructor.
    ~MasalaThreadManagerConfiguration() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared_ptr to the copy.
    MasalaThreadManagerConfigurationSP clone() const;

    /// @brief Deep operation: make an independent copy of this object and return a shared_ptr to the copy.
    MasalaThreadManagerConfigurationSP deep_clone() const;

    /// @brief Returns "MasalaThreadManagerConfiguration".
    std::string class_name() const override;

    /// @brief Returns "masala::base::managers::threads".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// Getters
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the number of threads to hold in the thread pool, by default.
    /// @details The thread pool will be one smaller than this, since the
    /// master thread of the process is counted.  A value of 0 means to launch
    /// one thread per hardware thread on the node.
    inline base::Size default_total_threads() const { return default_total_threads_; }

private:

////////////////////////////////////////////////////////////////////////////////
// Data
////////////////////////////////////////////////////////////////////////////////

    /// @brief The number of threads to hold in the thread pool, by default.
    /// @details The thread pool will be one smaller than this, since the
    /// master thread of the process is counted.  A value of 0 means to launch
    /// one thread per hardware thread on the node.
    base::Size default_total_threads_ = 1;

};

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadManagerConfiguration_hh
