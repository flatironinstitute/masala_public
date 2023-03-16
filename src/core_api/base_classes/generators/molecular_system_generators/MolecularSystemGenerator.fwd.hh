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

/// @file src/core_api/base_classes/generators/molecular_system_generators/MolecularSystemGenerator.fwd.hh
/// @brief Forward declarations for a pure virtual base class for MolecularSystemGenerators.
/// @details MolecularSystemGenerators generate molecular systems based on some input or some set of
/// user-supplied parameters.
/// @note Since this class does not implement class_name() or class_namespace()
/// functions required by the MasalaObject base class, it remains pure virtual.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_api_base_classes_generators_molecular_system_generators_MolecularSystemGenerator_fwd_hh
#define Masala_src_core_api_base_classes_generators_molecular_system_generators_MolecularSystemGenerator_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace core_api {
namespace base_classes {
namespace generators {
namespace molecular_system_generators {

	class MolecularSystemGenerator;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using MolecularSystemGeneratorSP = MASALA_SHARED_POINTER< MolecularSystemGenerator >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using MolecularSystemGeneratorCSP = MASALA_SHARED_POINTER< MolecularSystemGenerator const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using MolecularSystemGeneratorWP = MASALA_WEAK_POINTER< MolecularSystemGenerator >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using MolecularSystemGeneratorCWP = MASALA_WEAK_POINTER< MolecularSystemGenerator const >;

} // namespace molecular_system_generators
} // namespace generators
} // namespace base_classes
} // namespace core_api
} // namespace masala

#endif // Masala_src_core_api_base_classes_generators_molecular_system_generators_MolecularSystemGenerator_fwd_hh