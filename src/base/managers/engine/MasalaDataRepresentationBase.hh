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

/// @file src/base/managers/engine/MasalaDataRepresentationBase.hh
/// @brief A pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of
/// those data.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationBase_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationBase_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationBase.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/MasalaDataRepresentationCreatorBase.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A pure virtual base class class for particular representations
/// of data that can be requested by engines for efficient manipulation of
/// those data.
/// @note Only a MasalaDataRepresentationCreator can create a MasalaDataRepresentation.
/// Only a MasalaDataRepresentationRegistrator can create a MasalaDataRepresentationCreator.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationBase : public masala::base::MasalaObject {

    friend class MasalaDataRepresentationCreatorBase;

protected:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTOR -- PROTECTED
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationBase() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Copy constructor.
    MasalaDataRepresentationBase( MasalaDataRepresentationBase const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationBase() override = default;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationBase_hh