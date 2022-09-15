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

/// @file src/core/chemistry/atoms/ElementType.cc
/// @brief A class that describes a particular element.
/// @details This will be held by the ElementManager, so it can be fairly heavy-weight.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/ElementType.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

/// @brief Returns "ElementType".
std::string
ElementType::class_name() const {
    return "ElementType";
}

/// @brief Every class can provide its own namespace.  This returns "core::chemistry::atoms".
std::string
ElementType::class_namespace() const {
    return "core::chemistry::atoms";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the atomic number.
/// @details Throws if atomic number is out of range!
core::Size
ElementType::atomic_number() const {
    CHECK_OR_THROW_FOR_CLASS(
        static_cast<signed long>(element_type_) > 0 && static_cast<signed long>(element_type_) <= static_cast<signed long>(ElementTypeEnum::NUM_KNOWN_ELEMENTS),
        "atomic_number",
        "Error in masala::core::chemical::atoms::ElementType::atomic_number(): Element type is out of range!"
    );
    return static_cast< masala::core::Size >( element_type_ );
}

/// @brief Get the isotope number (the total number of nucleons in the current isotope).
/// @details Throws if atomic number is out of range!
core::Size
ElementType::isotope_number() const {
    return atomic_number() + neutron_count_current_isotope_;
}

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala