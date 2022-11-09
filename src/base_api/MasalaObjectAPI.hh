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

/// @file src/base_api/MasalaObjectAPI.hh
/// @brief A base class for all Masala derived API classes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_api_MasalaObjectAPI_hh
#define Masala_src_base_api_MasalaObjectAPI_hh

// Forward declarations:
#include <base_api/MasalaObjectAPI.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>

namespace masala {
namespace base_api {

/// @brief A base class for Masala API derived classes.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaObjectAPI : public base::MasalaObject {

	friend class masala::base::managers::configuration::MasalaConfigurationManager;

public:

	/// @brief Default constructor.
	MasalaObjectAPI() = default;

	/// @brief Copy constructor.
	MasalaObjectAPI( MasalaObjectAPI const & ) = default;

	/// @brief Pure virtual destructor.  This class cannot be instantiated; only its
	/// derived classes can.
	virtual ~MasalaObjectAPI() = default;

public:

	/// @brief Get the name of the class for which this class provides an API.
	/// @details Must be implemented by derived classes.
	virtual
    std::string
    inner_class_name() const = 0;

    /// @brief Get the namespace of the class for which this class provides an API.
	/// @details Must be implemented by derived classes.
	virtual
    std::string
    inner_class_namespace() const = 0;

}; // class MasalaObjectAPI

} // namespace base_api
} // namespace masala

#endif //Masala_src_base_api_MasalaObjectAPI_hh