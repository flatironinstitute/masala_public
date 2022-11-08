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
    std::set< AtomInstanceSP >::const_iterator const & it
) :
    base::MasalaObject(),
    iterator_(it)
{}

/// @brief Clone operator.
AtomInstanceConstIteratorSP
AtomInstanceConstIterator::clone() const {
    return std::make_shared< AtomInstanceConstIterator >( *this );
}

/// @brief Deep clone operator.
AtomInstanceConstIteratorSP
AtomInstanceConstIterator::deep_clone() const {
    AtomInstanceConstIteratorSP new_obj( std::make_shared< AtomInstanceConstIterator >() );
    new_obj->iterator_ = iterator_;
    return new_obj;
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


/// @brief Incrementation operator.
AtomInstanceConstIterator &
AtomInstanceConstIterator::operator++() {
    ++iterator_;
    return *this;
}

/// @brief Decrementation operator.
AtomInstanceConstIterator &
AtomInstanceConstIterator::operator--() {
    --iterator_;
    return *this;
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
            std::make_shared< MasalaObjectAPIDefinition >(
                class_name(), class_namespace(),
                "A const iterator over a set of AtomInstance objects.  This custom iterator is needed to allow iteration over "
                "const AtomInstance objects from a set containing non-const shared pointers."
            )
        );

        // api_definition->add_constructor(
        //     std::make_shared< MasalaObjectAPIConstructorDefinition_ZeroInput < AtomInstanceConstIterator > >(
        //         "AtomInstanceConstIterator", "Constructs an empty iterator.  Do not use!  The pointer is nullptr!"
        //     )
        // );
        api_definition->add_constructor(
            std::make_shared< MasalaObjectAPIConstructorDefinition_OneInput < AtomInstanceConstIterator, AtomInstanceConstIterator const & > >(
                "AtomInstanceConstIterator", "Default copy constructor.",
                "src", "The AtomInstanceConstIterator from which we are copying."
            )
        );
        // api_definition->add_constructor(
        //     std::make_shared< MasalaObjectAPIConstructorDefinition_OneInput < AtomInstanceConstIterator, std::set< AtomInstanceSP >::const_iterator const & > >(
        //         "AtomInstanceConstIterator", "Construct the iterator from a std::set const iterator.",
        //         "iterator", "The source std::set< AtomInstanceSP >::const_interator, with which we will initialize this iterator."
        //     )
        // );

        // Functions:
        api_definition->add_work_function(
            std::make_shared< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< AtomInstanceConstIterator const & > >(
                "operator++", "Increment the iterator.", false, true,
                "incremented_iterator", "A reference to the incremented iterator (this object).",
                std::bind( &AtomInstanceConstIterator::operator++, this )
            )
        );
        api_definition->add_work_function(
            std::make_shared< MasalaObjectAPIWorkFunctionDefinition_ZeroInput< AtomInstanceConstIterator const & > >(
                "operator--", "Decrement the iterator.", false, true,
                "decremented_iterator", "A reference to the decremented iterator (this object).",
                std::bind( &AtomInstanceConstIterator::operator--, this )
            )
        );
        // api_definition->add_getter(
        //     std::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< AtomInstance const & > >(
        //         "operator*", "Access the AtomInstance (by const reference).",
        //         "atom_instance", "A const reference to the AtomInstance object to which the iterator currently points.",
        //         std::bind( &AtomInstanceConstIterator::operator*, this )
        //     )
        // );
        api_definition->add_work_function(
            std::make_shared< MasalaObjectAPIWorkFunctionDefinition_OneInput< bool, AtomInstanceConstIterator const & > >(
                "operator==", "Compare to another AtomInstanceConstIterator.", true, false,
                "other", "The other AtomInstanceConstIterator, to which we are comparing.",
                "is_equal", "True if the two iterators point to the same AtomInstance; false otherwise.",
                std::bind( &AtomInstanceConstIterator::operator==, this, std::placeholders::_1 )
            )
        );
        api_definition->add_work_function(
            std::make_shared< MasalaObjectAPIWorkFunctionDefinition_OneInput< bool, AtomInstanceConstIterator const & > >(
                "operator!=", "Check for inequality with another AtomInstanceConstIterator.", true, false,
                "other", "The other AtomInstanceConstIterator, to which we are comparing.",
                "is_unequal", "True if the two iterators point to different AtomInstances; false if they are the same.",
                std::bind( &AtomInstanceConstIterator::operator!=, this, std::placeholders::_1 )
            )
        );
        api_definition->add_getter(
            std::make_shared< MasalaObjectAPIGetterDefinition_ZeroInput< AtomInstanceCSP > >(
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
