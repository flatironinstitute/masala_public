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

/// @file src/core/chemistry/AtomData.hh
/// @brief A container data for additional optional data that might be
/// attached to an atom.
/// @details Note that this is a pure virtual base class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_data_AtomData_hh
#define Masala_src_core_chemistry_data_AtomData_hh

// Forward declarations:
#include <core/chemistry/data/AtomData.fwd.hh>

// Core headers:

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:

namespace core {
namespace chemistry {
namespace data {


/// @brief A container data for additional optional data that might be
/// attached to an atom.
/// @details Note that this is a pure virtual base class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomData : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    AtomData() = default;

    /// @brief Copy constructor.
    /// @details Must be explicitly declared due to mutex.
    AtomData( AtomData const & src ) = default;

    /// @brief Default destructor.
    ~AtomData() override = default;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    virtual
    void
    make_independent();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

};

} // namespace data
} // namespace chemistry
} // namespace core

#endif // Masala_src_core_chemistry_data_AtomData_hh