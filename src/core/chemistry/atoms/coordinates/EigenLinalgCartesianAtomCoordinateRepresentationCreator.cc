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

/// @file src/base/managers/engine/EigenLinalgCartesianAtomCoordinateRepresentationCreator.cc
/// @brief A creator for Eigen linear algebra Cartesian atom coordinate data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project headers:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentationCreator.hh>

// Core headers:
#include <core/chemistry/atoms/coordinates/EigenLinalgCartesianAtomCoordinateRepresentation.hh>

// STL headers:
#include <string>

namespace core {
namespace chemistry {
namespace atoms {
namespace coordinates {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the class name.
    /// @returns "EigenLinalgCartesianAtomCoordinateRepresentationCreator".
    std::string EigenLinalgCartesianAtomCoordinateRepresentationCreator::class_name() const { return "EigenLinalgCartesianAtomCoordinateRepresentationCreator"; }

    /// @brief Get the class namespace.
    /// @returns "core::chemistry::atoms::coordinates"
    std::string EigenLinalgCartesianAtomCoordinateRepresentationCreator::class_namespace() const { return "core::chemistry::atoms::coordinates"; }


////////////////////////////////////////////////////////////////////////////////
// PROTECTED MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Creators must implement a create_data_representation() function.
/// @details Protected so that this can only be called by the MasalaDataRepresentationManager,
/// for which this is a friend class.
base::managers::engine::MasalaDataRepresentationBaseSP
EigenLinalgCartesianAtomCoordinateRepresentationCreator::create_data_representation() const {
    return std::make_shared< EigenLinalgCartesianAtomCoordinateRepresentation >();
}


} // namespace coordinates
} // namespace atoms
} // namespace chemistry
} // namespace core
