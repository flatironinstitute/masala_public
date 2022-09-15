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

/// @file src/base/managers/engine/MasalaDataRepresentationRegistratorBase.hh
/// @brief A base class for data representation registrators.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationRegistratorBase_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationRegistratorBase_hh

// Parent headers:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationRegistratorBase.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A base class for data representation registrators.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationRegistratorBase : public masala::base::MasalaObject {

public:

	/// @brief Default constructor.
	MasalaDataRepresentationRegistratorBase() = default;

	/// @brief Copy constructor.
	MasalaDataRepresentationRegistratorBase( MasalaDataRepresentationRegistratorBase const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~MasalaDataRepresentationRegistratorBase() = default;

}; // class MasalaDataRepresentationRegistratorBase

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaDataRepresentationRegistratorBase_hh