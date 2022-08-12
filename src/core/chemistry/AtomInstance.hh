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

/// @file src/core/chemistry/AtomInstance.hh
/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_AtomInstance_hh
#define Masala_src_core_chemistry_AtomInstance_hh

// Forward declarations:
#include <core/chemistry/AtomInstance.fwd.hh>

// Core headers:

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace core {
namespace chemistry {


/// @brief A class contiaining a description of the properties of
/// a particular atom.
/// @note This stores element type, formal charge, partial charge,
/// hybridization state... everything EXCEPT atomic coordinates.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomInstance : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    AtomInstance() = default;

    /// @brief Copy constructor.
    AtomInstance( AtomInstance const & ) = default;

    /// @brief Default destructor.
    ~AtomInstance() override = default;

    /// @brief Clone operation: make a copy of this object and return a shared pointer
    /// to the copy.
    virtual
    AtomInstanceSP
    clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    virtual
    AtomInstanceSP
    deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

	/// @brief Returns "AtomInstance".
	std::string class_name() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////


private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The type of element that this atom is.
    ElementTypeCSP element_type_;

    /// @brief This atom's hydbridization state.
    AtomHybridizationState hybridization_state_ = AtomHybridizationState::sp3;

};

} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_AtomInstance_hh