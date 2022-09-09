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

/// @file src/base/ErrorHandling.hh
/// @brief Macros for throwing errors, and a class for exceptions derived from
/// the std::exception class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_error_ErrorHandling_hh
#define Masala_src_base_error_ErrorHandling_hh

/// Forward declarations
#include <base/error/ErrorHandling.fwd.hh>

// STL headers
#include <exception>
#include <string>

namespace base {
namespace error {

class MasalaException : public std::exception {

public:

	////////////////////////////////////////////////////////////////////////////////
	// CONSTRUCTION AND DESTRUCTION
	////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor is explicitly deleted.
	MasalaException() = delete;

	/// @brief Message constructor.
	MasalaException( std::string const & message );

	/// @brief Default constructor.
	~MasalaException() = default;

public:

	////////////////////////////////////////////////////////////////////////////////
	// PUBLIC ACCESSORS
	////////////////////////////////////////////////////////////////////////////////

	/// @brief Access the error message.
	std::string const & message() const;

private:

	/// @brief The error message, set by the constructor.
	std::string const message_;
		
};

} // namespace error
} // namespace base

/// @brief Throw an error given a source namespace and class, a function name (with no parentheses), and
/// an error message.
#define MASALA_THROW( namespace_and_class, function_name, message ) throw base::error::MasalaException( namespace_and_class + "::" + function_name + "(): " + message );

/// @brief A macro for checking an assertion and throwing an error.
#define CHECK_OR_THROW( assertion, message ) if( !(assertion) ) { throw base::error::MasalaException( message ); }

#ifdef NDEBUG
#define DEBUG_MODE_CHECK_OR_THROW( assertion, message )
#else
/// @brief A macro for checking an assertion and throwing an error only in debug mode.
#define DEBUG_MODE_CHECK_OR_THROW( assertion, message ) if( !(assertion) ) { throw base::error::MasalaException( message ); }
#endif

#endif //Masala_src_base_error_ErrorHandling_hh