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

// STL headers
#include <functional>
#include <vector>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief An enum specifying how we'll request threads.
enum class MasalaThreadedWorkRequestMode {
	INVALID_REQUEST_MODE = 0, // Keep first
	REQUEST_ALL_THREADS,
	REQUEST_SPECIFIED_NUMBER_OF_THREADS, // Keep second-to-last
	NUM_REQUEST_MODES = REQUEST_SPECIFIED_NUMBER_OF_THREADS // Keep last
}; // enum class MasalaThreadedWorkRequestMode

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

	/// @brief Is the vector of work to do empty?
	/// @returns True if there's no work in the work vector, false otherwise.
	bool empty() const;

	/// @brief Are we requesting all threads?
	bool all_threads_requested() const;

	/// @brief How many threads have been requested?
	/// @details Throws unless mode is REQUEST_SPECIFIED_NUMBER_OF_THREADS.
	base::Size n_threads_requested() const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The vector of work to do in threads.
	/// @details This work might be done in any order.
	std::vector< std::function< void () > > work_vector_;

	/// @brief The mode for requesting threads.
	MasalaThreadedWorkRequestMode request_mode_ = MasalaThreadedWorkRequestMode::REQUEST_ALL_THREADS;

	/// @brief The number of threads requested.
	base::Size n_threads_requested_ = 1;

}; // class MasalaThreadedWorkRequest

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadedWorkRequest_hh