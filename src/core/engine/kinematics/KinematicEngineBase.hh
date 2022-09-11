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

/// @file src/core/engine/kinematics/KinematicEngineBase.hh
/// @brief A base class for Masala kinematic engines, which perform kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_engine_kinematics_KinematicEngineBase_hh
#define Masala_src_core_engine_kinematics_KinematicEngineBase_hh

// Forward declarations:
#include <core/engine/kinematics/KinematicEngineBase.fwd.hh>

// Core headers:
#include <core/engine/MasalaEngineBase.hh>

namespace core {
namespace engine {
namespace kinematics {

/// @brief A base class for Masala kinematic engines, which perform kinematic
/// manipulations (forward kinematics, inverse kinematics, and derivatives).
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class KinematicEngineBase : public core::engine::MasalaEngineBase {

public:

	/// @brief Default constructor.
	KinematicEngineBase() = default;

	/// @brief Copy constructor.
	KinematicEngineBase( KinematicEngineBase const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~KinematicEngineBase() = default;

}; // class KinematicEngineBase

} //namespace kinematics
} //namespace engine
} //namespace core

#endif //Masala_src_core_engine_kinematics_KinematicEngineBase_hh