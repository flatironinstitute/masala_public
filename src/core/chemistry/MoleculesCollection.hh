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

/// @file src/core/chemistry/MoleculesCollection.hh
/// @brief A class contiaining a collection of molecules.
/// @details Each Molecules object contains atoms and bonds.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_MoleculesCollection_hh
#define Masala_src_core_chemistry_MoleculesCollection_hh

// Forward declarations:
#include <core/chemistry/MoleculesCollection.fwd.hh>

// Core headers:
#include <base/types.hh>
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

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the number of molecules in this MoleculesCollection container.
    masala::base::Size size() const;

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