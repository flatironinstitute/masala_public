/*
    Masala
    Copyright (C) 2025 Vikram K. Mulligan

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

/// @file src/base/utility/time/date_and_time_util.cc
/// @brief Functions for getting times and dates.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit headers:
#include <base/utility/time/date_and_time_util.hh>

// STL headers:
#include <stdio.h>
#include <ctime>

namespace masala {
namespace base {
namespace utility {
namespace time {

/// @brief Get the current date, as a string of year, month, date (YYYYMMDD).
std::string
masala_get_date_YYYYMMDD(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	signed int const year( masala_get_year( time_in ) );
	unsigned short int const month( masala_get_month( time_in ) );
	unsigned short int const day( masala_get_day( time_in ) );

	char outstring[9];
	snprintf( outstring, 9, "%04d%02hu%02hu", year, month, day );
	return std::string( outstring );
}

/// @brief Get the current date, as a string of 24-hour hour, minute, second (HHMMSS).
std::string
masala_get_time_HHMMSS(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	unsigned short int const hour( masala_get_hour( time_in ) );
	unsigned short int const minute( masala_get_minute( time_in ) );
	unsigned short int const second( masala_get_second( time_in ) );

	char outstring[7];
	snprintf( outstring, 7, "%02hu%02hu%02hu", hour, minute, second );
	return std::string( outstring );
}

/// @brief Get the year, as a signed integer.  Negative values mean BC.
signed int
masala_get_year(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	time_t const time_in_converted( std::chrono::system_clock::to_time_t( time_in ) );
	tm date_and_time( *std::localtime( &time_in_converted ) );
	return 1900 + date_and_time.tm_year;
}

/// @brief Get the month, as an unsigned short integer (1 to 12).
unsigned short int
masala_get_month(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	time_t const time_in_converted( std::chrono::system_clock::to_time_t( time_in ) );
	tm date_and_time( *std::localtime( &time_in_converted ) );
	return static_cast< unsigned short >( 1 + date_and_time.tm_mon );
}

/// @brief Get the day (of the month), as an unsigned short integer (1 to 31).
unsigned short int
masala_get_day(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	time_t const time_in_converted( std::chrono::system_clock::to_time_t( time_in ) );
	tm date_and_time( *std::localtime( &time_in_converted ) );
	return static_cast< unsigned short >( date_and_time.tm_mday );
}

/// @brief Get the hour (on a 24-hour clock) as an unsigned short integer (0 to 23).
unsigned short int
masala_get_hour(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	time_t const time_in_converted( std::chrono::system_clock::to_time_t( time_in ) );
	tm date_and_time( *std::localtime( &time_in_converted ) );
	return static_cast< unsigned short >( date_and_time.tm_hour );
}

/// @brief Get the minute as an unsigned short integer (0 to 59).
unsigned short int
masala_get_minute(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	time_t const time_in_converted( std::chrono::system_clock::to_time_t( time_in ) );
	tm date_and_time( *std::localtime( &time_in_converted ) );
	return static_cast< unsigned short >( date_and_time.tm_min );
}

/// @brief Get the second as an unsigned short integer (0 to 59).
unsigned short int
masala_get_second(
	std::chrono::time_point< std::chrono::system_clock > const & time_in
) {
	time_t const time_in_converted( std::chrono::system_clock::to_time_t( time_in ) );
	tm date_and_time( *std::localtime( &time_in_converted ) );
	return static_cast< unsigned short >( date_and_time.tm_sec );
}

} // namespace time
} // namespace utility
} // namespace base
} // namespace masala
