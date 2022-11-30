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

/// @file src/core/chemistry/atoms/ElementType.hh
/// @brief A class that describes a particular element.
/// @details This will be held by the ElementManager, so it can be fairly heavy-weight.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_ElementType_hh
#define Masala_src_core_chemistry_atoms_ElementType_hh

// Forward declarations:
#include <core/chemistry/atoms/ElementType.fwd.hh>

// Core headers:
#include <core/types.hh>

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {

/// @brief A class that describes a particular element.
/// @details This will be held by the ElementManager, so it can be fairly heavy-weight.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ElementType : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    ElementType() = default;

    /// @brief Copy constructor.
    ElementType( ElementType const & ) = default;

    /// @brief Default destructor.
    ~ElementType() override = default;

	/// @brief Returns "ElementType".
	std::string class_name() const override;

    /// @brief Every class can provide its own namespace.  This returns "masala::core::chemistry::atoms".
    std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the atomic number.
    /// @details Throws if atomic number is out of range!
    masala::core::Size atomic_number() const;

    /// @brief Get the isotope number (the total number of nucleons in the current isotope).
    /// @details Throws if atomic number is out of range!
    masala::core::Size isotope_number() const;

    /// @brief Get the number of neturons in the current isotope.
    inline masala::core::Size neutron_count_current_isotope() const { return neutron_count_current_isotope_; }

    /// @brief Get the average atomic mass, across all isotopes weighted by abundance.
    /// @details In Daltons.
    inline masala::core::Real average_atomic_mass() const { return average_atomic_mass_; }

    /// @brief Get the atomic mass of the current isotope.
    /// @details In Daltons.
    inline masala::core::Real atomic_mass_current_isotope() const { return atomic_mass_current_isotope_; }

    /// @brief Get the element type, by enum.
    inline ElementTypeEnum element_type() const{ return element_type_; }

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The element type, as an enum.
    ElementTypeEnum element_type_ = ElementTypeEnum::C;

    /// @brief The number of neutrons in the current isotope.
    masala::core::Size neutron_count_current_isotope_ = 6;

    /// @brief The average atomic mass, across all isotopes weighted by abundance.
    /// @details In Daltons.
    masala::core::Real average_atomic_mass_ = 12.011;

    /// @brief The atomic mass of the current isotope.
    /// @details In Daltons.
    masala::core::Real atomic_mass_current_isotope_ = 12.0;

};

} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_ElementType_hh