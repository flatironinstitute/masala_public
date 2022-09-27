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

/// @file src/base/managers/threads/MasalaThreadedWorkRequest.hh
/// @brief A class that stores a vector of work to do in threads plus configuration
/// options describing how the work is to be done.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh
#define Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh

// Forward declarations:
#include <base/managers/threads/MasalaThreadedWorkRequest.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/types.hh>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief A class that stores a vector of work to do in threads plus configuration
/// options describing how the work is to be done.
class MasalaThreadedWorkRequest : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaThreadedWorkRequest() = default;

	/// @brief Copy constructor.
	MasalaThreadedWorkRequest( MasalaThreadedWorkRequest const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaThreadedWorkRequest() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadedWorkRequest".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads".
	std::string class_namespace() const override;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

}; // class MasalaThreadedWorkRequest

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh