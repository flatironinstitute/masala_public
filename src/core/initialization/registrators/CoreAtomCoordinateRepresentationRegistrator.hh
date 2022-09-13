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

/// @file src/base/managers/tracer/CoreAtomCoordinateRepresentationRegistrator.hh
/// @brief A static singleton that registers representations for atom coordinates
/// on first initialization.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_initialization_registrators_CoreAtomCoordinateRepresentationRegistrator_hh
#define Masala_src_core_initialization_registrators_CoreAtomCoordinateRepresentationRegistrator_hh

// Parent header:
#include <base/managers/engine/MasalaDataRepresentationRegistratorBase.hh>

// Forward declarations:
#include <core/initialization/registrators/CoreAtomCoordinateRepresentationRegistrator.fwd.hh>

// Base headers:

// STL headers:
#include <map>
#include <mutex>

namespace core {
namespace initialization {
namespace registrators {


/// @brief A static singleton that registers representations for atom coordinates
/// on first initialization.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class CoreAtomCoordinateRepresentationRegistrator : public base::managers::engine::MasalaDataRepresentationRegistratorBase {

public:

    /// @brief Instantiate the static singleton, triggering registration of the
    /// atom coordinate representations.
    static void register_atom_coordinate_representations();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    CoreAtomCoordinateRepresentationRegistrator();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    CoreAtomCoordinateRepresentationRegistrator( CoreAtomCoordinateRepresentationRegistrator const & ) = delete;

    /// @brief No assignment operator.
    void operator=( CoreAtomCoordinateRepresentationRegistrator const & ) = delete;

    /// @brief Default destructor.
    ~CoreAtomCoordinateRepresentationRegistrator() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "CoreAtomCoordinateRepresentationRegistrator".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "core::initialization::registrators".
    std::string
    class_namespace() const override;

};

} // namespace registrators
} // namespace initialization
} // namespace core

#endif //Masala_src_core_initialization_registrators_CoreAtomCoordinateRepresentationRegistrator_hh
