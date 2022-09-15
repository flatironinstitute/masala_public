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

/// @file src/core/chemistry/MoleculesCollection.hh
/// @brief A class contiaining a collection of molecules.
/// @details Each Molecules object contains atoms and bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MoleculesCollection_hh
#define Masala_src_core_chemistry_MoleculesCollection_hh

// Forward declarations:
#include <core/chemistry/MoleculesCollection.fwd.hh>

// Core headers:
#include <core/types.hh>
#include <core/chemistry/Molecules.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <set>

namespace masala {
namespace core {
namespace chemistry {

/// @brief A class contiaining a collection of molecules.
/// @details Each Molecules object contains atoms and bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MoleculesCollection : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MoleculesCollection() = default;

    /// @brief Copy constructor.
    MoleculesCollection( MoleculesCollection const & ) = default;

    /// @brief Default destructor.
    ~MoleculesCollection() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    MoleculesCollectionSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual
    MoleculesCollectionSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

    /// @brief Returns "MoleculesCollection".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "core::chemistry".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the number of molecules in this MoleculesCollection container.
    masala::core::Size size() const;

    /// @brief Get an iterator to the first Molecules object stored in this MoleculesCollection
    /// container.
    std::set< MoleculesSP >::const_iterator molecules_set_begin() const;

    /// @brief Get an iterator to the end of the set of Molecules objects stored in
    /// this MoleculesCollection container.
    std::set< MoleculesSP >::const_iterator molecules_set_end() const;

private:

    /// @brief The Molecules objects that we're storing.
    std::set< MoleculesSP > molecule_set_;

};

} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_MoleculesCollection_hh