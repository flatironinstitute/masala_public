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

/// @file src/base/managers/environment/MasalaEnvironmentManager.hh
/// @brief Headers for a static singleton for managing environment variables.
/// @details All environment variables are queried once and cached by this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_environment_MasalaEnvironmentManager_hh
#define Masala_src_base_managers_environment_MasalaEnvironmentManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/environment/MasalaEnvironmentManager.fwd.hh>

// Base headers:
#include <base/managers/environment/MasalaEnvironmentVariable.fwd.hh>

// STL headers:
#include <mutex>
#include <map>

namespace masala {
namespace base {
namespace managers {
namespace environment {

/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
class MasalaEnvironmentManager : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaEnvironmentManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaEnvironmentManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaEnvironmentManager( MasalaEnvironmentManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaEnvironmentManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaEnvironmentManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaEnvironmentManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::environment".
    std::string
    class_namespace() const override;

    /// @brief Get the value of an environment variable.
    /// @details If the environment variable is set, then value_receiver is
    /// populated with its value.  If not, then this function returns false,
    /// and the value of value_receiver is not changed.
    /// @note Triggers read from system environment the first time that a
    /// value is accessed.
    bool
    get_environment_variable(
        std::string const & environment_variable_name,
        std::string & value_receiver
    ) const;

private: // Data

    /// @brief A mutex for locking this singleton.
    mutable std::mutex environment_manager_mutex_;

    /// @brief A vector of MasalaEnvironmentVariable objects, indexed by environment variable name.
    mutable std::map< std::string, MasalaEnvironmentVariable const * > environment_variables_;

};

} // namespace environment
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_environment_MasalaEnvironmentManager_hh