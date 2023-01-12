/*
    Masala
    Copyright (C) 2022 Vikram K. Mulligan

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
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
#include <atomic>

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

	/// @brief Copy constructor.
	MasalaException( MasalaException const & src );

	/// @brief Assignment operator.
	MasalaException & operator=( MasalaException const & src );

	/// @brief Destructor.
	/// @details Ensures that message is printed if exception is unhandled.
	~MasalaException();

public:

	////////////////////////////////////////////////////////////////////////////////
	// PUBLIC ACCESSORS
	////////////////////////////////////////////////////////////////////////////////

	/// @brief Access the error message.
	std::string const & message() const;

	/// @brief Access the error message in standard exception handling.
	char const* what() const noexcept override;

private:

	/// @brief The error message, set by the constructor.
	std::string message_;

	/// @brief Has the message been printed?
	mutable std::atomic_bool message_was_printed_;
		
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
#define DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( ASSERTION, FUNCTION_NAME, MESSAGE )
#else
/// @brief A macro for checking an assertion and throwing an error only in debug mode, from within a class.
/// @note Do not use in constructors!
#define DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( ASSERTION, FUNCTION_NAME, MESSAGE ) if( !(ASSERTION) ) { throw masala::base::error::MasalaException( get_errmsg_header(FUNCTION_NAME) + std::string(MESSAGE) ); }
#endif

#endif //Masala_src_base_error_ErrorHandling_hh