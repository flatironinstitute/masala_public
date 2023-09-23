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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreterManager.hh
/// @brief Header for a static singleton for managing modules responsible for reading and writing particular
/// file formats, and converting these to and from particular data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_file_interpreter_MasalaFileInterpreterManager_hh
#define Masala_src_base_managers_file_interpreter_MasalaFileInterpreterManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/file_interpreter/MasalaFileInterpreterManager.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/api/names_from_types.tmpl.hh>

// STL headers:
#include <map>
#include <mutex>
#include <vector>
#include <set>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief A static singleton for managing modules responsible for reading and writing particular
/// file formats, and converting these to and from particular data representations.
class MasalaFileInterpreterManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaFileInterpreterManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaFileInterpreterManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaFileInterpreterManager( MasalaFileInterpreterManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaFileInterpreterManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaFileInterpreterManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaFileInterpreterManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::file_interpreter".
    std::string
    class_namespace() const override;

    /// @brief Completely reset the manager.
    /// @details Unregisters all file interpreters.
    void reset();

    /// @brief Get the number of registered file interpreters.
    base::Size total_file_interpreters() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////


};

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_file_interpreter_MasalaFileInterpreterManager_hh