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

/// @file src/base/managers/tracer/CoreAtomCoordinateRepresentationRegistrator.hh
/// @brief A static singleton that registers representations for atom coordinates
/// on first initialization.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_initialization_registrators_CoreAtomCoordinateRepresentationRegistrator_hh
#define Masala_src_core_initialization_registrators_CoreAtomCoordinateRepresentationRegistrator_hh

// Parent header:
#include <base/managers/engine/MasalaDataRepresentationRegistratorBase.hh>

// Forward declarations:
#include <core/initialization/registrators/CoreAtomCoordinateRepresentationRegistrator.fwd.hh>

// Base headers:

// STL headers:
#include <map>
#include <mutex>

namespace masala {
namespace core {
namespace initialization {
namespace registrators {


/// @brief A static singleton that registers representations for atom coordinates
/// on first initialization.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CoreAtomCoordinateRepresentationRegistrator : public masala::base::managers::engine::MasalaDataRepresentationRegistratorBase {

public:

    /// @brief Instantiate the static singleton, triggering registration of the
    /// atom coordinate representations.
    static void register_atom_coordinate_representations();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    CoreAtomCoordinateRepresentationRegistrator();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    CoreAtomCoordinateRepresentationRegistrator( CoreAtomCoordinateRepresentationRegistrator const & ) = delete;

    /// @brief No assignment operator.
    void operator=( CoreAtomCoordinateRepresentationRegistrator const & ) = delete;

    /// @brief Default destructor.
    ~CoreAtomCoordinateRepresentationRegistrator() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "CoreAtomCoordinateRepresentationRegistrator".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::core::initialization::registrators".
    std::string
    class_namespace() const override;

};

} // namespace registrators
} // namespace initialization
} // namespace core
} // namespace masala

#endif //Masala_src_core_initialization_registrators_CoreAtomCoordinateRepresentationRegistrator_hh
