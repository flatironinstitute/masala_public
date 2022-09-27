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

/// @file src/base/managers/threads/MasalaThreadedWorkExecutionSummary.hh
/// @brief A class that will store a summary of what work was done in threads,
/// how long it took, and how many threads were actually assigned to the work.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh
#define Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh

// Forward declarations:
#include <base/managers/threads/MasalaThreadedWorkExecutionSummary.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/types.hh>

namespace masala {
namespace base {
namespace managers {
namespace threads {

/// @brief An enum for the exit status following a threaded work request.
enum class MasalaThreadedWorkStatus {
	INVALID_STATUS = 0, // Keep first
	NO_WORK_DONE,
	WORK_THREW_EXCEPTION,
	WORK_SUCCESSFUL, // Keep second-to-last
	NUM_STATUS_TYPES = WORK_SUCCESSFUL // Keep last
}; // enum class MasalaThreadedWorkStatus

/// @brief A base class for all Masala derived classes.  This allows the possibility of having a
/// generic MasalaThreadedWorkExecutionSummary pointer or shared pointer.
/// @note The MasalaConfigurationManager can access the private member functions (and data) of MasalaThreadedWorkExecutionSummarys.
/// This allows it to call load_configuration() when first needed.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaThreadedWorkExecutionSummary : public base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor, deleted.
	MasalaThreadedWorkExecutionSummary() = delete;

	/// @brief Options constructor.
	/// @param[in] status The status for the work done.
	/// @param[in] nthreads_actual The number of threads that were
	/// actually used for carrying out the work.
	/// @param[in] execution_time The time, in microseconds, that
	/// execution took.
	MasalaThreadedWorkExecutionSummary(
		MasalaThreadedWorkStatus const status,
		base::Size const nthreads_actual,
		base::Real const execution_time_microseconds
	);

	/// @brief Copy constructor.
	MasalaThreadedWorkExecutionSummary( MasalaThreadedWorkExecutionSummary const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	~MasalaThreadedWorkExecutionSummary() override = default;

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS:
////////////////////////////////////////////////////////////////////////////////

	/// @brief Returns "MasalaThreadedWorkExecutionSummary".
	std::string class_name() const override;

	/// @brief Returns "masala::base::managers::threads".
	std::string class_namespace() const override;

	/// @brief Get the status of the work.
	inline MasalaThreadedWorkStatus work_status() const { return work_status_; }

	/// @brief Get the number of threads that were actually used for the work (which can
	/// be less than the number requested).
	inline base::Size nthreads_actual() const { return nthreads_actual_; }

	/// @brief Get the wall-time, in microseconds that the work took.
	inline base::Real execution_time_microseconds() const { return execution_time_microseconds_; }

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE DATA:
////////////////////////////////////////////////////////////////////////////////

	/// @brief The status of the work.  Must be set on construction.
	MasalaThreadedWorkStatus const work_status_ = MasalaThreadedWorkStatus::INVALID_STATUS;

	/// @brief The number of threads that were actually used for the work (which can
	/// be less than the number requested).  Must be set on construction.
	base::Size const nthreads_actual_ = 0;

	/// @brief The wall-time, in microseconds that the work took.  Must be set
	/// on construction.
	base::Real execution_time_microseconds_ = 0.0;

}; // class MasalaThreadedWorkExecutionSummary

} // namespace threads
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_threads_MasalaThreadedWorkExecutionSummary_hh