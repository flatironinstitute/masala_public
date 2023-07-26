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

/// @file src/base/managers/engine/MasalaDataRepresentationBase.hh
/// @brief A pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of
/// those data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationBase_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationBase_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationBase.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of
/// those data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationBase : public masala::base::MasalaObject {

    friend class MasalaDataRepresentationCreator;

protected:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR -- PROTECTED
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationBase() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Copy constructor.
    MasalaDataRepresentationBase( MasalaDataRepresentationBase const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationBase() override = default;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationBase_hh