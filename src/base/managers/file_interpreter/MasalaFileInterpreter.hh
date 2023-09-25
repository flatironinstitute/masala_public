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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreter.hh
/// @brief Headers for a pure virtual base class class for modules that control the
/// interconversion of data representations and particular file formats.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_file_interpreter_MasalaFileInterpreter_hh
#define Masala_src_base_managers_file_interpreter_MasalaFileInterpreter_hh

// Forward declarations:
#include <base/managers/file_interpreter/MasalaFileInterpreter.fwd.hh>

// Base headers:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// STL headers:
#include <vector>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief A pure virtual base class class for modules that control the
/// interconversion of data representations and particular file formats.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaFileInterpreter : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaFileInterpreter() = default;

    /// @brief Copy constructor.
    MasalaFileInterpreter( MasalaFileInterpreter const & ) = default;

    // Destructor.
    ~MasalaFileInterpreter() override = default;

public:

	/// @brief All MasalaFileInterpreter subclasses must list the file types that they create.  These are
	/// provided as short descriptors (e.g. "protein_data_bank_file").
	virtual
	std::vector< std::string >
	get_file_descriptors() const = 0;

	/// @brief All MasalaFileInterpreter subclasses must list the file type extensions that they create.
	/// @details Extensions are provided in lower-case (e.g. "pdb").
	virtual
	std::vector< std::string >
	get_file_extensions() const = 0;

};

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_file_interpreter_MasalaFileInterpreter_hh