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

/// @file src/core/chemistry/Molecules.hh
/// @brief A class contiaining a collection of molecules.
/// @details Each molecule contains atoms and bonds.  The Molecules container can also
/// define intermolecular bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_Molecules_hh
#define Masala_src_core_chemistry_Molecules_hh

// Forward declarations:
#include <core/chemistry/Molecules.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace core {
namespace chemistry {


/// @brief A class contiaining a collection of molecules.
/// @details Each molecule contains atoms and bonds.  The Molecules container can also
/// define intermolecular bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Molecules : public base::MasalaObject {

    public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    Molecules() = default;

    /// @brief Copy constructor.
    Molecules( Molecules const & ) = default;

    /// @brief Default destructor.
    ~Molecules() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    MoleculesSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual
    MoleculesSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

};

} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_Molecules_hh