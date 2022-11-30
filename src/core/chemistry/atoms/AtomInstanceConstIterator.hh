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

/// @file src/core/chemistry/atoms/AtomInstanceConstIterator.hh
/// @brief Headers for a const iterator over a set of AtomInstances.
/// @details Not threadsafe!  Intended for single-thread access.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_AtomInstanceConstIterator_hh
#define Masala_src_core_chemistry_atoms_AtomInstanceConstIterator_hh

// Forward declarations:
#include <core/chemistry/atoms/AtomInstanceConstIterator.fwd.hh>
#include <core/chemistry/atoms/AtomInstance.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <set>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {


/// @brief A const iterator over a set of AtomInstances.
/// @details Not threadsafe!  Intended for single-thread access.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomInstanceConstIterator : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor, deleted.
    AtomInstanceConstIterator() = default;

    /// @brief Constructor from set iterator.
    AtomInstanceConstIterator(
        std::set< AtomInstanceSP >::const_iterator const & it
    );

    /// @brief Copy constructor.
    AtomInstanceConstIterator( AtomInstanceConstIterator const & ) = default;

    /// @brief Clone operator.
    AtomInstanceConstIteratorSP clone() const;

    /// @brief Deep clone operator.
    AtomInstanceConstIteratorSP deep_clone() const;

    /// @brief Make this object independent by deep-cloning anything to
    /// which it holds a shared pointer.
    /// @details All that this version does is to reset the api_definition_
    /// shared pointer to nullptr.
    void make_independent();

    /// @brief Default destructor.
    ~AtomInstanceConstIterator() override = default;

	/// @brief Returns "AtomInstanceConstIterator".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Pre-incrementation operator.
    AtomInstanceConstIterator &
    operator++();

    /// @brief Pre-decrementation operator.
    AtomInstanceConstIterator &
    operator--();

    /// @brief Post-incrementation operator.
    AtomInstanceConstIterator
    operator++( int const dummy );

    /// @brief Post-decrementation operator.
    AtomInstanceConstIterator
    operator--( int const dummy );

    /// @brief Const access.
    AtomInstance const &
    operator*();

    /// @brief Comparison.
    bool
    operator==(
        AtomInstanceConstIterator const & other
    ) const;

    /// @brief Anticomparison.
    bool
    operator!=(
        AtomInstanceConstIterator const & other
    ) const;

    /// @brief Pointer access.
    AtomInstanceCSP
    ptr() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API FUNCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the API definition for an atom instance.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The contained iterator to a nonconst pointer.
    std::set< AtomInstanceSP >::const_iterator iterator_;

    /// @brief The API definition.  Nullptr until generated.
    base::api::MasalaObjectAPIDefinitionCSP api_definition_;

};

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_AtomInstanceConstIterator_hh