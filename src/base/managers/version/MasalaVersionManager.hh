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

/// @file src/base/managers/version/MasalaVersionManager.hh
/// @brief Headers for a static singleton for managing the version of Masala's core library and
/// of plugin libraries, along with any inter-library version dependencies.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_version_MasalaVersionManager_hh
#define Masala_src_base_managers_version_MasalaVersionManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/version/MasalaVersionManager.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/version/MasalaModuleVersionInfo.fwd.hh>

// STL headers:
#include <mutex>
#include <unordered_map>

namespace masala {
namespace base {
namespace managers {
namespace version {


/// @brief A static singleton for managing the version of Masala's core library and
/// of plugin libraries, along with any inter-library version dependencies.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaVersionManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaVersionManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaVersionManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaVersionManager( MasalaVersionManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaVersionManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaVersionManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaVersionManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::version".
    std::string
    class_namespace() const override;

    /// @brief Add information for a new library.
    /// @details Stores the input directly, without cloning.
    void
    add_library_information(
        MasalaModuleVersionInfoCSP const & module_version_info
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex to lock this object.
    mutable std::mutex masala_version_manager_mutex_;

    /// @brief The list of MasalaModuleVersionInfo objects.
    /// @details MasalaModuleVersionInfo objects contain information about the version
    /// of each loaded module.
    std::unordered_map< std::string, MasalaModuleVersionInfoCSP > module_version_infos_;

};

} // namespace version
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_version_MasalaVersionManager_hh