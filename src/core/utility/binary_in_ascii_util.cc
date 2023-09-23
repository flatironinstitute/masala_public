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

/// @file src/core/utility/binary_in_ascii_util.cc
/// @brief Implementations of utility functions for storing binary information safely in
/// ASCII files.  This uses the trick of using four bytes of ASCII information to store
/// three bytes of binary information, using only the 64 bitstrings corresponding to the
/// characters A-Z, a-z, 0-9, +, and /.  Note that this avoids whitespace and EOF characters.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit header:
#include <core/utility/binary_in_ascii_util.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>

// STL headers:
#include <sstream>

namespace masala {
namespace core {
namespace utility {

/// @brief Convert the characters A-Z,a-z,0-9,+ to integers from 0 to 63.
/// @returns An integer, from 0 to 63.
masala::base::Size
decode_size_from_char(
	unsigned char const character
) {
	using masala::base::Size;

	Size const character_as_size( static_cast<Size>(character) );

    if ( character_as_size >= static_cast<Size>('A') && character_as_size <= static_cast<Size>('Z') ) {
        return character_as_size - static_cast<Size>('A');
	} else if( character_as_size >= static_cast<Size>('a') && character_as_size <= static_cast<Size>('z') ) {
        return character_as_size - static_cast<Size>('a') + 26;
	} else if( character_as_size >= static_cast<Size>('0') && character_as_size <= static_cast<Size>('9') ) {
        return character_as_size - static_cast<Size>('0') + 52;
	} else if( character == '+' ) {
		return 62;
	} else if( character == '/' ) {
		return 63;
	} else {
		std::stringstream errmsg;
		errmsg << "Character '" << character << "' is not in the range 'A'-'Z', 'a'-'z', '0'-'9', '+' or '/'.";
		MASALA_THROW( "masala::core::utility", "decode_size_from_char", errmsg.str() );
	}
	return 0;
}

/// @brief Convert the characters A-Z,a-z,0-9,+ to chars corresponding to
/// integers from 00000000 (i.e. 0) to 00111111 (i.e. 63).
/// @returns An integer, from 0 to 63.
unsigned char
decode_char_from_char(
	unsigned char const character
) {
    if ( character >= 'A' && character <= 'Z' ) {
        return character - 'A';
	} else if( character >= 'a' && character <= 'z' ) {
        return character - 'a' + static_cast<unsigned char>(26);
	} else if( character >= '0' && character <= '9' ) {
        return character - '0' + static_cast<unsigned char>(52);
	} else if( character == '+' ) {
		return static_cast<unsigned char>(62);
	} else if( character == '/' ) {
		return static_cast<unsigned char>(63);
	} else {
		std::stringstream errmsg;
		errmsg << "Character '" << character << "' is not in the range 'A'-'Z', 'a'-'z', '0'-'9', '+' or '/'.";
		MASALA_THROW( "masala::core::utility", "decode_char_from_char", errmsg.str() );
	}
	return 0;
}

/// @brief Given a pointer to the first byte of a block of memory and a string, interpret every
/// four bytes of the string as three bytes of data and start filling the block of memory.
/// @details Fills up to max_bytes bytes, or until the string is exhausted, whichever comes first.
/// @returns The number of bytes filled.
masala::base::Size
decode_data_from_string(
	unsigned char * data,
	std::string const & datastring,
	masala::base::Size const max_bytes
) {
	using masala::base::Size;
	
	Size idata(0);
	Size bytes_processed(0);
	
	// Process up to four bytes of string at a time.
	for( Size istring(0), istringmax(datastring.size()); istring<istringmax; istring += 4 ) {
		Size const bytes_to_read( std::min( static_cast<Size>(4), istringmax - istring ) );
		Size const bytes_to_write( std::min( static_cast<Size>(3), max_bytes - idata ) );

		unsigned char c1( decode_char_from_char( datastring[istring] ) ),
			c2( bytes_to_read > 1 ? decode_char_from_char( datastring[istring + 1] ) : static_cast< unsigned char >(0) ),
			c3( bytes_to_read > 2 ? decode_char_from_char( datastring[istring + 2] ) : static_cast< unsigned char >(0) ),
			c4( bytes_to_read > 3 ? decode_char_from_char( datastring[istring + 3] ) : static_cast< unsigned char >(0) );

		data[idata] = (c1 << 2) & (c2 >> 4);
		if( bytes_to_write > 1 ) {
			data[idata+1] = (c2 << 4) & (c3 >> 2);
			if( bytes_to_write > 2 ) {
				data[idata+2] = (c3 << 6) & c4;
			}
		} 

		bytes_processed += bytes_to_write;
		idata +=3;
		if( idata > max_bytes ) {
			break;
		} 
	}

	return bytes_processed;
}

} // namespace utility
} // namespace core
} // namespace masala
