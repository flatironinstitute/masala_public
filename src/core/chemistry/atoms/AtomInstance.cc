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

/// @file src/core/chemistry/atoms/AtomInstance.cc
/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/AtomInstance.hh>

// Core headers:
#include <core/chemistry/atoms/data/PDBAtomData.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

    /// @brief Constructor from PDB atom.
    AtomInstance::AtomInstance(
        std::string const & pdb_atom_name,
        signed long pdb_atom_index,
        std::string const & pdb_element_name
    ) :
        masala::base::MasalaObject(),
        additional_atom_data_{ std::make_shared< data::PDBAtomData >( pdb_atom_name, pdb_atom_index, pdb_element_name ) }
    {}

/// @brief Clone operation: make a copy of this object and return a shared pointer
/// to the copy.
AtomInstanceSP
AtomInstance::clone() const {
    return std::make_shared< AtomInstance >( *this );
}

/// @brief Deep clone operation: make a deep copy of this object and return a shared
/// pointer to the deep copy.
AtomInstanceSP
AtomInstance::deep_clone() const {
    AtomInstanceSP AtomInstance_copy( std::make_shared< AtomInstance >( *this ) );
    AtomInstance_copy->make_independent();
    return AtomInstance_copy;
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Be sure to update this function whenever a private member is added!
void
AtomInstance::make_independent() {
    // Currently GNDN.
}

/// @brief Returns "AtomInstance".
std::string
AtomInstance::class_name() const {
    return "AtomInstance";
}

/// @brief Every class can provide its own namespace.  This returns "masla::core::chemistry::atoms".
std::string
AtomInstance::class_namespace() const {
    return "masla::core::chemistry::atoms";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
