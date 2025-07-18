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
#include <base/MasalaObjectAPI.fwd.hh>

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

	/// @brief Is the file type read by this file interpreter ASCII or binary?
	/// @details Must be implemented by subclasses.  Returns true if the file interpreter interprets ASCII
	/// files, and false if it interprets binary files.
	virtual
	bool
	filetype_is_ascii() const = 0;

	/// @brief MasalaFileInterpreter subclasses can implement a function to generate a Masala class
	/// from the contents of a text file (expressed as a vector of strings).
	/// @details The base class version of this function throws.
	virtual
	masala::base::MasalaObjectAPISP
	object_from_ascii_file_contents(
		std::vector< std::string > const & file_contents
	) const;

	/// @brief The MasalaFileInterpreter base class can read a file (using the MasalaDiskAccessManager)
	/// and produce an object.  This function calls object_from_ascii_file_contents() or
	/// object_from_binary_file_contents(), implemented by a subclass, depending on whether filetype_is_ascii()
	/// returns true or false.
	masala::base::MasalaObjectAPISP
	object_from_file(
		std::string const & filename
	) const;

	/// @brief MasalaFileInterpreter subclasses can implement a function to generate a text file
	/// from the contents of a Masala Object (expressed as a vector of strings).
	/// @details The base class version of this function throws.
	virtual
	std::string
	ascii_file_contents_from_object(
		MasalaObjectAPICSP const & object
	) const;

	/// @brief The MasalaFileInterpreter base class can write a file (using the MasalaDiskAccessManager).
	void
	object_to_file(
        MasalaObjectAPICSP const & object,
		std::string const & filename
	) const;

};

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_file_interpreter_MasalaFileInterpreter_hh