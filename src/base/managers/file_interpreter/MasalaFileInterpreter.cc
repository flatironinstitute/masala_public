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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreter.cc
/// @brief A pure virtual base class class for modules that control the
/// interconversion of data representations and particular file formats.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/file_interpreter/MasalaFileInterpreter.hh>

// STL headers:
#include <vector>
#include <string>

// Base headers:
#include <base/managers/disk/MasalaDiskManager.hh>
#include <base/error/ErrorHandling.hh>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief MasalaFileInterpreter subclasses can implement a function to generate a Masala class
/// from the contents of a text file (expressed as a vector of strings).
/// @details The base class version of this function throws.
masala::base::MasalaObjectAPISP
MasalaFileInterpreter::object_from_ascii_file_contents(
	std::vector< std::string > const & /*file_contents*/
) const {
	MASALA_THROW( class_namespace_and_name(), "object_from_ascii_file_contents", "This function must be "
		"implemented for the " + class_name() + " class to allow interpretation of ASCII files."
	);
	return nullptr;
}


/// @brief The MasalaFileInterpreter base class can read a file (using the MasalaDiskAccessManager)
/// and produce an object.  This function calls object_from_ascii_file_contents() or
/// object_from_binary_file_contents(), implemented by a subclass, depending on whether filetype_is_ascii()
/// returns true or false.
masala::base::MasalaObjectAPISP
MasalaFileInterpreter::object_from_file(
	std::string const & filename
) const {
	using namespace masala::base::managers::disk;

	CHECK_OR_THROW_FOR_CLASS( filetype_is_ascii(), "object_from_file", "Support for binary files has not yet been "
		"implemented in Masala!"
	);

	return object_from_ascii_file_contents(
		MasalaDiskManager::get_instance()->read_ascii_file_to_string_vector( filename )
	);
}

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala
