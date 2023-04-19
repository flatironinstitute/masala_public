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

/// @file src/base/managers/database/elements/ElementType.hh
/// @brief A class that describes a particular element.
/// @details This will be held by the ElementManager, so it can be fairly heavy-weight.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_database_elements_ElementType_hh
#define Masala_src_base_managers_database_elements_ElementType_hh

// Forward declarations:
#include <base/managers/database/elements/ElementType.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/MasalaObject.hh>

// External headers:
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers:
#include <array>

namespace masala {
namespace base {
namespace managers {
namespace database {
namespace elements {

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
// PUBLIC INITIALIZATION FUNCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Initialize the element type from a JSON description.
    /// @param[in] element_type The atomic number enum for this element.
    /// @param[in] abbreviation The normally-cased abbreviaton for this element
    /// type (e.g. "Mg", "Na", "K" ).
    /// @param[in] json A JSON description of this element type.
    void
    initialize_from_json(
        ElementTypeEnum const element_type,
        std::string const & abbreviation,
        nlohmann::json const & json
    );

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the atomic number.
    /// @details Throws if atomic number is out of range!
    masala::base::Size atomic_number() const;

    /// @brief Get the isotope number (the total number of nucleons in the isotope) for the
    /// most common isotope.
    /// @details Throws if atomic number is out of range!
    base::Size isotope_number_most_common_isotope() const;

    /// @brief Get the number of neturons in the most common isotope.
    inline masala::base::Size neutron_count_most_common_isotope() const { return neutron_count_most_common_isotope_; }

    /// @brief Get the average atomic mass, across all isotopes weighted by abundance.
    /// @details In Daltons.
    inline masala::base::Real average_atomic_mass() const { return average_atomic_mass_; }

    /// @brief Get the average atomic mass uncertainty, across all isotopes weighted by abundance.
    /// @details In Daltons.
    inline masala::base::Real average_atomic_mass_uncertainty() const { return average_atomic_mass_uncertainty_; }

    /// @brief Get the atomic mass of the most common isotope.
    /// @details In Daltons.
    inline masala::base::Real atomic_mass_most_common_isotope() const { return atomic_mass_most_common_isotope_; }

    /// @brief Get the element type, by enum.
    inline ElementTypeEnum element_type() const{ return element_type_; }

    /// @brief Get the van der Waals radius.
    inline masala::base::Real van_der_waals_radius() const { return van_der_waals_radius_; }

    /// @brief Get the default colour of the element, for GUIs.
    /// @details Colours are red, green, blue values ranging from 0 to 1.
    inline std::array< masala::base::Real, 3 > const & default_rgb_colour() const { return default_rgb_colour_; }

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Initialize a particular datum from JSON.
    template < class T >
    void initialize_datum_from_json(
        T & datum,
        std::string const & key,
        std::string const & abbreviation,
        nlohmann::json const & json,
        T const & default_value
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The element type, as an enum.
    ElementTypeEnum element_type_ = ElementTypeEnum::UNKNOWN_ELEMENT_TYPE;

    /// @brief The abbreviation of this element.
    /// @details This is the standard abbreviation, with normal casing (e.g. "Cu").
    std::string element_abbreviation_ = "Unk";

    /// @brief The full name of this element, in lowercase (e.g. "copper").
    /// @details We will use IUPAC spellings ("sulfur", "aluminium", and
    /// "caesium" instead of "sulphur", "aluminum", and "cesium").
    std::string element_fullname_ = "unknown";

    /// @brief The number of neutrons in the most common isotope.
    masala::base::Size neutron_count_most_common_isotope_ = 0;

    /// @brief The average atomic mass, across all isotopes weighted by abundance.
    /// @details In Daltons.
    masala::base::Real average_atomic_mass_ = 0.0;

    /// @brief The average atomic mass uncertainty, across all isotopes weighted by abundance.
    /// @details In Daltons.
    masala::base::Real average_atomic_mass_uncertainty_ = 0.0;

    /// @brief The atomic mass of the most common isotope.
    /// @details In Daltons.
    masala::base::Real atomic_mass_most_common_isotope_ = 0.0;

    /// @brief The van der Waals radius of the (neutral) element.
    /// @brief In Angstroms.
    masala::base::Real van_der_waals_radius_ = 2.0;

    /// @brief The default colour of the element, for GUIs.
    /// @details Colours are red, green, blue values ranging from 0 to 1.
    std::array< masala::base::Real, 3 > default_rgb_colour_ = std::array< masala::base::Real, 3 >{0.5, 0.5, 0.5};

};

} // namespace elements
} // namespace database
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_database_elements_ElementType_hh