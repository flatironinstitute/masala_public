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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreterCreator.hh
/// @brief Headers for a pure virtual base class for creators for file interpreters.
/// @details Creators must be registered with the MasalaFileInterpreterManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_file_interpreter_MasalaFileInterpreterCreator_hh
#define Masala_src_base_managers_file_interpreter_MasalaFileInterpreterCreator_hh

// Forward declarations:
#include <base/managers/file_interpreter/MasalaFileInterpreterCreator.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginCreator.hh>
#include <base/managers/file_interpreter/MasalaFileInterpreterAPI.fwd.hh>
#include <base/managers/file_interpreter/MasalaFileInterpreterManager.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief A pure virtual base class for creators for file interpreters.
/// @details Creators must be registered with the MasalaFileInterpreterManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaFileInterpreterCreator : public masala::base::managers::plugin_module::MasalaPluginCreator {

    friend class masala::base::managers::engine::MasalaFileInterpreterManager;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaFileInterpreterCreator() = default;

    /// @brief Copy constructor.
    MasalaFileInterpreterCreator( MasalaFileInterpreterCreator const & ) = delete;

    /// @brief Destructor.
    ~MasalaFileInterpreterCreator() override = default;

    /// @brief Get the class name, static version.
    /// @returns "MasalaFileInterpreterCreator".
    static
    std::string
    class_name_static();

    /// @brief Get the class namespace, static version.
    /// @returns "masala::base::managers::engine".
    static
    std::string
    class_namespace_static();

    /// @brief Get the class namespace and name, static version.
    /// @returns "masala::base::managers::engine::MasalaFileInterpreterCreator".
    static
    std::string
    class_namespace_and_name_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Creators must implement a create_file_interpreter() function.  Under the
    /// hood this just calls create_plugin_object().
    MasalaFileInterpreterAPISP
    create_file_interpreter() const;

};

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_file_interpreter_MasalaFileInterpreterCreator_hh