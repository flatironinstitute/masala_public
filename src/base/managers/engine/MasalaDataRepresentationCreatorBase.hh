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

/// @file src/base/managers/engine/MasalaDataRepresentationCreatorBase.hh
/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationCreatorBase_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationCreatorBase_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationCreatorBase.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/MasalaDataRepresentationBase.fwd.hh>


namespace base {
namespace managers {
namespace engine {

/// @brief A pure virtual base class for creators for data representations.
/// @details Creators must be registered with the MasalaDataRepresentationManager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationCreatorBase : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationCreatorBase() = default;

    /// @brief Copy constructor.
    MasalaDataRepresentationCreatorBase( MasalaDataRepresentationCreatorBase const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationCreatorBase() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Creators must implement a create_data_representation() function.
    MasalaDataRepresentationBaseSP
    create_data_representation() const = 0;

};

} // namespace engine
} // namespace managers
} // namespace base

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationCreatorBase_hh