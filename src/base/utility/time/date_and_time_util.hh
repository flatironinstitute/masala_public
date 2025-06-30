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

/// @file src/base/utility/time/date_and_time_util.hh
/// @brief Functions for getting times and dates.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_utility_time_date_and_time_util_hh
#define Masala_src_base_utility_time_date_and_time_util_hh

// Base headers
#include <base/types.hh>

// STL headers
#include <string>
#include <chrono>

namespace masala {
namespace base {
namespace utility {
namespace time {

	/// @brief Get the current date, as a string of year, month, date (YYYYMMDD).
	std::string masala_get_date_YYYYMMDD( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the current date, as a string of 24-hour hour, minute, second (HHMMSS).
	std::string masala_get_time_HHMMSS( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the year, as a signed integer.  Negative values mean BC.
	signed int masala_get_year( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the month, as an unsigned short integer (1 to 12).
	unsigned short int masala_get_month( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the day (of the month), as an unsigned short integer (1 to 31).
	unsigned short int masala_get_day( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the hour (on a 24-hour clock) as an unsigned short integer (0 to 23).
	unsigned short int masala_get_hour( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the minute as an unsigned short integer (0 to 59).
	unsigned short int masala_get_minute( std::chrono::time_point< std::chrono::system_clock > const & time_in );

	/// @brief Get the second as an unsigned short integer (0 to 59).
	unsigned short int masala_get_second( std::chrono::time_point< std::chrono::system_clock > const & time_in );

} // namespace time
} // namespace utility
} // namespace base
} // namespace masala

#endif //Masala_src_base_utility_time_date_and_time_util_hh
