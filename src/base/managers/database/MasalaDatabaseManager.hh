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

/// @file src/base/managers/database/MasalaDatabaseManager.hh
/// @brief Headers for a static singleton for managing data loaded
/// from the Masala database.
/// @details The core Masala database stores minimal chemical information, such as
/// element properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_MasalaDatabaseManager_hh
#define Masala_src_base_managers_database_MasalaDatabaseManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/database/MasalaDatabaseManager.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/database/elements/MasalaElementDatabase.hh>

// STL headers:
#include <map>
#include <mutex>
#include <thread>

namespace masala {
namespace base {
namespace managers {
namespace database {



/// @brief A static singleton for managing data loaded from the Masala database.
/// @details The core Masala database stores minimal chemical information, such as
/// element properties.
class MasalaDatabaseManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaDatabaseManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaDatabaseManager();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaDatabaseManager( MasalaDatabaseManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaDatabaseManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaDatabaseManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaDatabaseManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::database".
    std::string
    class_namespace() const override;

    /// @brief Access the element database.
    /// @details Triggers initialization of this database (i.e. read from disk) the
    /// first time this is called.  Initialization is threadsafe.
    masala::base::managers::database::elements::MasalaElementDatabase const &
    element_database() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex to lock this object.
    mutable std::mutex masala_database_manager_mutex_;

    /// @brief The location of the Masala database.
    /// @details This will ultimately be user-configurable, but for now this is hard-coded.
    /// @note This is an absolute path.
    std::string absolute_database_path_;

////////////////////////////////////////////////////////////////////////////////
// COLLECTIONS OF STORED DATA
// Each of these is lazily loaded (in a threadsafe manner) on first demand,
// then const-accessed.
////////////////////////////////////////////////////////////////////////////////

    /// @brief Element data, loaded lazily and once from the database.
    /// @details Mutable to allow lazy initialization one time from const function.
    mutable masala::base::managers::database::elements::MasalaElementDatabaseCSP element_database_ = nullptr;

};

} // namespace database
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_database_MasalaDatabaseManager_hh