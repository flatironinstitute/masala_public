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

/// @file src/base/managers/engine/MasalaEngineBase.hh
/// @brief A base class for Masala engines, which perform hard calculations of a given type using
/// a given method.
/// @details Subclasses will be defined for kinematic calculations, packing calculations, minimization
/// calculations, etc.  Each of these in turn will have subclasses for performing these using different
/// math libraries, optimizers, hardware, etc.
/// @note Only a MasalaEngineCreator can create a MasalaEngine.  Only a MasalaEngineRegistrator can
/// create a MasalaEngineCreator.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineBase_hh
#define Masala_src_base_managers_engine_MasalaEngineBase_hh

// Forward declarations:
#include <base/managers/engine/MasalaEngineBase.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/MasalaEngineCreatorBase.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A base class for Masala engines, which perform hard calculations of a given type using
/// a given method.
/// @details Subclasses will be defined for kinematic calculations, packing calculations, minimization
/// calculations, etc.  Each of these in turn will have subclasses for performing these using different
/// math libraries, optimizers, hardware, etc.
/// @note Only a MasalaEngineCreator can create a MasalaEngine.  Only a MasalaEngineRegistrator can
/// create a MasalaEngineCreator.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineBase : public masala::base::MasalaObject {

    friend class MasalaEngineCreatorBase;

protected:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR -- PROTECTED
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaEngineBase() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

	/// @brief Copy constructor.
	MasalaEngineBase( MasalaEngineBase const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~MasalaEngineBase() = default;

}; // class MasalaEngineBase

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngineBase_hh