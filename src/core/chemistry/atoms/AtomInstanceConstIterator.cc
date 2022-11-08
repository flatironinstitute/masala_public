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
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/AtomInstanceConstIterator.hh>

// Core headers:

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_ZeroInput.tmpl.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorDefinition_OneInput.tmpl.hh>
#include <base/api/getter/MasalaObjectAPIGetterDefinition_ZeroInput.tmpl.hh>
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
        iterator_ != nullptr, "operator*",
        "Cannot access the AtomInstance, since the iterator was nullptr!"
    );
    return *iterator_;
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


} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala
