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

////////////////////////////////////////////////////////////////////////////////
// ELEMENT FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Given an element enum, get the element name.
/// @returns "UNKNOWN" for out-of-range values.
std::string
element_name_from_enum(
    ElementTypeEnum const element_type
) {
    if( static_cast<signed long>(element_type) < 0 || element_type > ElementTypeEnum::NUM_KNOWN_ELEMENTS ) {
        return "UNKNOWN";
    }
    static std::vector< std::string > const element_names{
        "UNKNOWN",
         "H", "He",
        "Li", "Be",  "B",  "C",  "N",  "O",  "F", "Ne",
        "Na", "Mg", "Al", "Si",  "P",  "S", "Cl", "Ar",
         "K", "Ca", "Sc", "Ti",  "V", "Cr", "Mn", "Fe", "Co", "Ni", "Cu", "Zn", "Ga", "Ge", "As", "Se", "Br", "Kr",
        "Rb", "Sr",  "Y", "Zr", "Nb", "Mo", "Tc", "Ru", "Rh", "Pd", "Ag", "Cd", "In", "Sn", "Sb", "Te",  "I", "Xe",
        "Cs", "Ba", "La", "Ce", "Pr", "Nd", "Pm", "Sm", "Eu", "Gd", "Tb", "Dy", "Ho", "Er", "Tm", "Yb", "Lu", "Hf", "Ta",  "W", "Re", "Os", "Ir", "Pt", "Au", "Hg", "Tl", "Pb", "Bi", "Po", "At", "Rn",
        "Fr", "Ra", "Ac", "Th", "Pa",  "U", "Np", "Pu", "Am", "Cm", "Bk", "Cf", "Es", "Fm", "Md", "No", "Lr", "Rf", "Db", "Sg", "Bh", "Hs", "Mt", "Ds", "Rg", "Cn", "Nh", "Fl", "Mc", "Lv", "Ts", "Og"
    };
    return element_names[static_cast< unsigned long >(element_type)];
}

/// @brief Given an element name, get the element enum.
/// @returns INVALID_ELEMENT_TYPE for names that can't be parsed.
ElementTypeEnum
element_enum_from_name(
    std::string const & element_name
) {
    for( core::Size i(1); i<=static_cast<core::Size>(ElementTypeEnum::NUM_KNOWN_ELEMENTS); ++i ) {
        if( element_name == element_name_from_enum( static_cast<ElementTypeEnum>(i) ) ) {
            return static_cast<ElementTypeEnum>(i);
        }
    }
    return ElementTypeEnum::INVALID_ELEMENT_TYPE;
}

////////////////////////////////////////////////////////////////////////////////
// ElementType class:
////////////////////////////////////////////////////////////////////////////////

/// @brief Returns "ElementType".
std::string
ElementType::class_name() const {
    return "ElementType";
}

/// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
std::string
ElementType::class_namespace() const {
    return "masala::core::chemistry::atoms";
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