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

    /// @brief Every class can provide its own namespace.  This returns "core::chemistry::atoms".
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