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

    /// @brief Incrementation operator.
    AtomInstanceConstIterator &
    operator++();

    /// @brief Decrementation operator.
    AtomInstanceConstIterator &
    operator--();

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