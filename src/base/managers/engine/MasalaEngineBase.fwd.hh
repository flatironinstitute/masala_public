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

/// @file src/base/managers/engine/MasalaEngineBase.fwd.hh
/// @brief Forward declarations for a base class for Masala engines, which perform hard calculations
/// of a given type using a given method.
/// @details Subclasses will be defined for kinematic calculations, packing calculations, minimization
/// calculations, etc.  Each of these in turn will have subclasses for performing these using different
/// math libraries, optimizers, hardware, etc.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineBase_fwd_hh
#define Masala_src_base_managers_engine_MasalaEngineBase_fwd_hh

#include <base/managers/memory/util.hh> // For MASALA_SHARED_POINTER

namespace masala {
namespace base {
namespace managers {
namespace engine {

	class MasalaEngineBase;

	/// @brief We will use the convention that an class name followed by SP
	/// represents a MASALA_SHARED_POINTER for objects of that class.
	using MasalaEngineBaseSP = MASALA_SHARED_POINTER< MasalaEngineBase >;

	/// @brief We will use the convention that an class name followed by CSP
	/// represents a MASALA_SHARED_POINTER for const objects of that class.
	using MasalaEngineBaseCSP = MASALA_SHARED_POINTER< MasalaEngineBase const >;

	/// @brief We will use the convention that an class name followed by WP
	/// represents a MASALA_WEAK_POINTER for objects of that class.
	using MasalaEngineBaseWP = MASALA_WEAK_POINTER< MasalaEngineBase >;

	/// @brief We will use the convention that an class name followed by CWP
	/// represents a MASALA_WEAK_POINTER for const objects of that class.
	using MasalaEngineBaseCWP = MASALA_WEAK_POINTER< MasalaEngineBase const >;

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngineBase_fwd_hh