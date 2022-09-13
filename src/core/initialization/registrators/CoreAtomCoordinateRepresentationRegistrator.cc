/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file src/base/managers/tracer/CoreAtomCoordinateRepresentationRegistrator.cc
/// @brief A static singleton that registers representations for atom coordinates
/// on first initialization.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <core/initialization/registrators/CoreAtomCoordinateRepresentationRegistrator.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationManager.hh>

// Core headers:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentationCreator.hh>


namespace core {
namespace initialization {
namespace registrators {

/// @brief Instantiate the static singleton, triggering registration of the
/// atom coordinate representations.
void
CoreAtomCoordinateRepresentationRegistrator::register_atom_coordinate_representations() {
    static CoreAtomCoordinateRepresentationRegistrator atom_coord_rep_registrator;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

/// @brief Private constructor: object can only be instantiated with getInstance().
CoreAtomCoordinateRepresentationRegistrator::CoreAtomCoordinateRepresentationRegistrator() :
    base::managers::engine::MasalaDataRepresentationRegistratorBase()
{
    base::managers::engine::MasalaDataRepresentationManagerHandle manager(
        base::managers::engine::MasalaDataRepresentationManager::get_instance()
    );
    // TODO: register all atom coordinate representations defined in core here.
    manager->register_data_representation( "core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentation", std::make_shared< core::chemistry::atoms::coordinates::EigenLinalgCartesianAtomCoordinateRepresentationCreator >() );
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "CoreAtomCoordinateRepresentationRegistrator".
std::string
CoreAtomCoordinateRepresentationRegistrator::class_name() const {
    return "CoreAtomCoordinateRepresentationRegistrator";
}

/// @brief Get the namespace of this object.
/// @details Returns "core::initialization::registrators".
std::string
CoreAtomCoordinateRepresentationRegistrator::class_namespace() const {
    return "core::initialization::registrators";
}

} // namespace registrators
} // namespace initialization
} // namespace core
