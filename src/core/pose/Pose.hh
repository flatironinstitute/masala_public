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

/// @file src/core/pose/Pose.hh
/// @brief A class representing a molecular structure.
/// @details Poses store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_pose_Pose_hh
#define Masala_src_core_pose_Pose_hh

// Forward declarations.
#include <core/pose/Pose.fwd.hh>

// Base includes.
#include <base/MasalaObject.hh>

namespace core {
namespace pose {


/// @brief A class representing a molecular structure.
/// @details Poses store atom coordinates, degree-of-freedom and kinematic relationships,
/// annotations, and computed or measured properties.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class Pose : public base::MasalaObject {

public:

    /// @brief Default constructor.
    Pose() = default;

    /// @brief Copy constructor.
    Pose( Pose const & ) = default;

    /// @brief Default destructor.
    ~Pose() override = default;

    /// @brief Clone opereration: make a copy of this object and return a shared pointer
    /// to the copy.
    PoseSP clone() const;

    /// @brief Deep clone operation: make a deep copy of this object and return a shared
    /// pointer to the deep copy.
    PoseSP deep_clone() const;

    /// @brief Make this object independent by making a deep copy of all of its private members.
    /// @details Be sure to update this function whenever a private member is added!
    void
    make_independent();

};

} // namespace pose
} // namespace core

#endif // Masala_src_core_pose_Pose_hh