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

/// @file src/core/chemistry/atoms/AtomInstanceConstIterator.cc
/// @brief A const iterator over a set of AtomInstances.
/// @details Not threadsafe!  Intended for single-thread access.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/AtomInstanceConstIterator.hh>

// Core headers:
#include <core/chemistry/atoms/AtomInstance.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_ZeroInput.tmpl.hh>
#include <base/api/work_function/MasalaObjectAPIWorkFunctionDefinition_OneInput.tmpl.hh>
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Constructor from set iterator.
AtomInstanceConstIterator::AtomInstanceConstIterator(
    std::set< AtomInstanceCSP >::const_iterator const & it
) :
    base::MasalaObject(),
    iterator_(it)
{}

/// @brief Clone operator.
AtomInstanceConstIteratorSP
AtomInstanceConstIterator::clone() const {
    return masala::make_shared< AtomInstanceConstIterator >( *this );
}

/// @brief Deep clone operator.
AtomInstanceConstIteratorSP
AtomInstanceConstIterator::deep_clone() const {
    AtomInstanceConstIteratorSP new_obj( masala::make_shared< AtomInstanceConstIterator >() );
    new_obj->iterator_ = iterator_;
    return new_obj;
}

/// @brief Make this object independent by deep-cloning anything to
/// which it holds a shared pointer.
/// @details All that this version does is to reset the api_definition_
/// shared pointer to nullptr.
void AtomInstanceConstIterator::make_independent() {
    api_definition_ = nullptr;
}

/// @brief Returns "AtomInstanceConstIterator".
std::string
AtomInstanceConstIterator::class_name() const {
    return "AtomInstanceConstIterator";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
std::string
AtomInstanceConstIterator::class_namespace() const {
    return "masala::core::chemistry::atoms";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC GETTERS
////////////////////////////////////////////////////////////////////////////////


/// @brief Pre-incrementation operator.
AtomInstanceConstIterator &
AtomInstanceConstIterator::operator++() {
    ++iterator_;
    return *this;
}

/// @brief Pre-decrementation operator.
AtomInstanceConstIterator &
AtomInstanceConstIterator::operator--() {
    --iterator_;
    return *this;
}

/// @brief Post-incrementation operator.
AtomInstanceConstIterator
AtomInstanceConstIterator::operator++(
    int const //dummy
) {
    return AtomInstanceConstIterator( iterator_++ );
}

/// @brief Post-decrementation operator.
AtomInstanceConstIterator
AtomInstanceConstIterator::operator--(
    int const //dummy
) {
    return AtomInstanceConstIterator( iterator_-- );
}

/// @brief Const access.
AtomInstance const &
AtomInstanceConstIterator::operator*() {
    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        *iterator_ != nullptr, "operator*",
        "Cannot access the AtomInstance, since the iterator was nullptr!"
    );
    return **iterator_;
}

/// @brief Comparison.
bool
AtomInstanceConstIterator::operator==(
    AtomInstanceConstIterator const & other
) const {
    return iterator_ == other.iterator_;
}

/// @brief Anticomparison.
bool
AtomInstanceConstIterator::operator!=(
    AtomInstanceConstIterator const & other
) const {
    return iterator_ != other.iterator_;
}

/// @brief Pointer access.
AtomInstanceCSP
AtomInstanceConstIterator::ptr() const {
    return *iterator_;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC API FUNCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the API definition for an atom instance.
masala::base::api::MasalaObjectAPIDefinitionCWP
AtomInstanceConstIterator::get_api_definition() {
    using namespace masala::base::api;
    using namespace masala::base::api::constructor;
    using namespace masala::base::api::getter;
    using namespace masala::base::api::work_function;

    if( api_definition_ == nullptr ) {
        MasalaObjectAPIDefinitionSP api_definition(
            masala::make_shared< MasalaObjectAPIDefinition >(
                *this,
                "A const iterator over a set of AtomInstance objects.  This custom iterator is needed to allow iteration over "
                "const AtomInstance objects from a set containing non-const shared pointers.",
                true
            )
        );

        // api_definition->add_constructor(
        //     masala::make_shared< MasalaObjectAPIConstructorDefinition_ZeroInput < AtomInstanceConstIterator > >(
        //         "AtomInstanceConstIterator", "Constructs an empty iterator.  Do not use!  The pointer is nullptr!"
        //     )
        // );
        api_definition->add_constructor(
            masala::make_shared< MasalaObjectAPIConstructorDefinition_OneInput < AtomInstanceConstIterator, AtomInstanceConstIterator const & > >(
                "AtomInstanceConstIterator", "Default copy constructor.",
                "src", "The AtomInstanceConstIterator from which we are copying."
            )
        );
        // api_definition->add_constructor(
        //     masala::make_shared< MasalaObjectAPIConstructorDefinition_OneInput < AtomInstanceConstIterator, std::set< AtomInstanceCSP >::const_iterator const & > >(
        //         "AtomInstanceConstIterator", "Construct the iterator from a std::set const iterator.",
        //         "iterator", "The source std::set< AtomInstanceCSP >::const_iterator, with which we will initialize this iterator."
        //     )
        // );

        // Functions:
        api_definition->add_work_function(
            masala::make_shared< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< AtomInstanceConstIterator & > >(
                "operator++", "Increment the iterator.  (Pre-incrementation operator.)", false, true,
                "incremented_iterator", "A reference to the incremented iterator (this object).",
                std::bind( static_cast< AtomInstanceConstIterator & (AtomInstanceConstIterator::*)() >( &AtomInstanceConstIterator::operator++ ), this )
            )
        );
        api_definition->add_work_function(
            masala::make_shared< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< AtomInstanceConstIterator & > >(
                "operator--", "Decrement the iterator.  (Pre-decrementation operator.)", false, true,
                "decremented_iterator", "A reference to the decremented iterator (this object).",
                std::bind( static_cast< AtomInstanceConstIterator & (AtomInstanceConstIterator::*)() >( &AtomInstanceConstIterator::operator-- ), this )
            )
        );
        api_definition->add_work_function(
            masala::make_shared< MasalaObjectAPIWorkFunctionDefinition_OneInput< AtomInstanceConstIterator, int > >(
                "operator++", "Increment the iterator.  (Post-incrementation operator.)", false, false,
                "dummy", "A dummy integer, used to distinguish this function from the pre-incrementation override.",
                "original_iterator", "A copy of the iterator PRIOR to incrementation.",
                std::bind( static_cast< AtomInstanceConstIterator (AtomInstanceConstIterator::*)( int ) >( &AtomInstanceConstIterator::operator++ ), this, std::placeholders::_1 )
            )
        );
        api_definition->add_work_function(
            masala::make_shared< MasalaObjectAPIWorkFunctionDefinition_OneInput< AtomInstanceConstIterator, int > >(
                "operator--", "Decrement the iterator.  (Post-decrementation operator.)", false, false,
                "dummy", "A dummy integer, used to distinguish this function from the pre-decrementation override.",
                "original_iterator", "A copy of the iterator PRIOR to decrementation.",
                std::bind( static_cast< AtomInstanceConstIterator (AtomInstanceConstIterator::*)( int ) >( &AtomInstanceConstIterator::operator-- ), this, std::placeholders::_1 )
            )
        );
        // api_definition->add_getter(
        //     masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< AtomInstance const & > >(
        //         "operator*", "Access the AtomInstance (by const reference).",
        //         "atom_instance", "A const reference to the AtomInstance object to which the iterator currently points.",
        //         std::bind( &AtomInstanceConstIterator::operator*, this )
        //     )
        // );
        api_definition->add_work_function(
            masala::make_shared< MasalaObjectAPIWorkFunctionDefinition_OneInput< bool, AtomInstanceConstIterator const & > >(
                "operator==", "Compare to another AtomInstanceConstIterator.", true, false,
                "other", "The other AtomInstanceConstIterator, to which we are comparing.",
                "is_equal", "True if the two iterators point to the same AtomInstance; false otherwise.",
                std::bind( &AtomInstanceConstIterator::operator==, this, std::placeholders::_1 )
            )
        );
        api_definition->add_work_function(
            masala::make_shared< MasalaObjectAPIWorkFunctionDefinition_OneInput< bool, AtomInstanceConstIterator const & > >(
                "operator!=", "Check for inequality with another AtomInstanceConstIterator.", true, false,
                "other", "The other AtomInstanceConstIterator, to which we are comparing.",
                "is_unequal", "True if the two iterators point to different AtomInstances; false if they are the same.",
                std::bind( &AtomInstanceConstIterator::operator!=, this, std::placeholders::_1 )
            )
        );
        api_definition->add_getter(
            masala::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< AtomInstanceCSP > >(
                "ptr", "Access the AtomInstance (by const shared pointer).",
                "atom_const_ptr", "A const shared pointer to the AtomInstance object to which the iterator currently points.",
                std::bind( &AtomInstanceConstIterator::ptr, this )
            )
        );

        api_definition_ = api_definition;
    }
    return api_definition_;
}

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
