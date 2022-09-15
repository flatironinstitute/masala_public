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

namespace masala {
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
} // namespace masala

/// @brief Throw an error given a source namespace and class, a function name (with no parentheses), and
/// an error message.
#define MASALA_THROW( NAMESPACE_AND_CLASS, FUNCTION_NAME, MESSAGE ) throw masala::base::error::MasalaException( std::string(NAMESPACE_AND_CLASS) + "::" + std::string(FUNCTION_NAME) + "(): " + std::string(MESSAGE) );

/// @brief A macro for checking an assertion and throwing an error.
#define CHECK_OR_THROW( ASSERTION, NAMESPACE_AND_CLASS, FUNCTION_NAME, MESSAGE ) if( !(ASSERTION) ) { throw masala::base::error::MasalaException( std::string(NAMESPACE_AND_CLASS) + "::" + std::string(FUNCTION_NAME) + "(): " + std::string(MESSAGE) ); }

/// @brief A macro for checking an assertion and throwing an error from within a class.
/// @note Do not use in constructors!
#define CHECK_OR_THROW_FOR_CLASS( ASSERTION, FUNCTION_NAME, MESSAGE ) if( !(ASSERTION) ) { throw masala::base::error::MasalaException( get_errmsg_header(FUNCTION_NAME) + std::string(MESSAGE) ); }


#ifdef NDEBUG
#define DEBUG_MODE_CHECK_OR_THROW( ASSERTION, NAMESPACE_AND_CLASS, FUNCTION_NAME, MESSAGE )
#else
/// @brief A macro for checking an assertion and throwing an error only in debug mode.
#define DEBUG_MODE_CHECK_OR_THROW( ASSERTION, NAMESPACE_AND_CLASS, FUNCTION_NAME, MESSAGE ) if( !(ASSERTION) ) { throw masala::base::error::MasalaException( std::string(NAMESPACE_AND_CLASS) + "::" + std::string(FUNCTION_NAME) + "(): " + std::string(MESSAGE) ); }
#endif

#ifdef NDEBUG
#define DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( ASSERTION, NAMESPACE_AND_CLASS, FUNCTION_NAME, MESSAGE )
#else
/// @brief A macro for checking an assertion and throwing an error only in debug mode, from within a class.
/// @note Do not use in constructors!
#define DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( ASSERTION, FUNCTION_NAME, MESSAGE ) if( !(ASSERTION) ) { throw masala::base::error::MasalaException( get_errmsg_header(FUNCTION_NAME) + std::string(MESSAGE) ); }
#endif

#endif //Masala_src_base_error_ErrorHandling_hh