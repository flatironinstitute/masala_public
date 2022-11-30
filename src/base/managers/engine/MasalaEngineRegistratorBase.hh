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

/// @file src/base/managers/engine/MasalaEngineRegistratorBase.hh
/// @brief A base class for engine registrators.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineRegistratorBase_hh
#define Masala_src_base_managers_engine_MasalaEngineRegistratorBase_hh

// Parent headers:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/engine/MasalaEngineRegistratorBase.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A base class for engine registrators.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineRegistratorBase : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaEngineRegistratorBase() = default;

	/// @brief Copy constructor.
	MasalaEngineRegistratorBase( MasalaEngineRegistratorBase const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~MasalaEngineRegistratorBase() = default;

}; // class MasalaEngineRegistratorBase

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngineRegistratorBase_hh