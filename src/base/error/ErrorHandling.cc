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

/// @file src/base/ErrorHandling.cc
/// @brief Macros for throwing errors, and a class for exceptions derived from
/// the std::exception class.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header.
#include <base/error/ErrorHandling.hh>

// Base headers.
#include <base/managers/tracer/MasalaTracerManager.hh>

namespace masala {
namespace base {
namespace error {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

/// @brief Message constructor.
MasalaException::MasalaException(
	std::string const & message
) :
	std::exception(),
	message_(message),
	message_was_printed_(false)
{}

/// @brief Copy constructor.
MasalaException::MasalaException(
	MasalaException const & src
) :
	std::exception(src)
{
	message_was_printed_.store( src.message_was_printed_.load() );
	message_ = src.message_;
}

/// @brief Assignment operator.
MasalaException &
MasalaException::operator=(
	MasalaException const & src
) {
	std::exception::operator=(src);
	message_was_printed_.store( src.message_was_printed_.load() );
	message_ = src.message_;
	return *this;
}

/// @brief Destructor.
/// @details Ensures that message is printed if exception is unhandled.
MasalaException::~MasalaException() {
	if( !message_was_printed_ ) {
		base::managers::tracer::MasalaTracerManager::get_instance()->write_to_tracer( "MasalaException", "UNHANDLED EXCEPTION: " + message_ );
	}
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC ACCESSORS
////////////////////////////////////////////////////////////////////////////////

/// @brief Access the error message.
std::string const &
MasalaException::message() const {
	message_was_printed_ = true;
	return message_;
}

} // namespace error
} // namespace base
} // namespace masala
