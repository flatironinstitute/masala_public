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

/// @file src/base/managers/disk/MasalaDiskManager.cc
/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/disk/MasalaDiskManager.hh>

// Base headers:
#include <base/error/ErrorHandling.hh>
#include <base/managers/threads/MasalaThreadManager.hh>
#include <base/utility/time/date_and_time_util.hh>

// External headers:
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers:
#include <string>
#include <filesystem> //This is the only place in the Masala codebase where this header is permitted to be included.
#include <fstream> //This is the only place in the Masala codebase where this header is permitted to be included.
#include <regex>
#include <sstream>
#include <chrono>
#include <format>

namespace masala {
namespace base {
namespace managers {
namespace disk {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Instantiate the static singleton and get a handle to it.
MasalaDiskManagerHandle
MasalaDiskManager::get_instance() {
	static const MasalaDiskManager disk_manager;
	return &disk_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaDiskManager".
std::string
MasalaDiskManager::class_name() const {
	return "MasalaDiskManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::disk".
std::string
MasalaDiskManager::class_namespace() const {
	return "masala::base::managers::disk";
}

/// @brief Write a string to an ASCII file.
/// @details TRIGGERS WRITE TO DISK!  Threadsafe (locks mutex).
void
MasalaDiskManager::write_ascii_file(
	std::string const & file_name,
	std::string const & file_contents
) const {
	std::lock_guard< std::mutex > lock( disk_io_mutex_);
	std::ofstream filehandle( file_name );
	CHECK_OR_THROW_FOR_CLASS( filehandle.good(), "write_ascii_file", "Could not open \"" + file_name + "\" for write." );
	filehandle << file_contents;
	filehandle.close();
}

/// @brief Read the contents of an ASCII file to a vector of strings.
/// @details Threadsafe (locks mutex).
std::vector< std::string >
MasalaDiskManager::read_ascii_file_to_string_vector(
	std::string const & file_name
) const {
	std::vector< std::string > outvec;
	{
		std::lock_guard< std::mutex > lock( disk_io_mutex_);
		std::ifstream filehandle( file_name );
		CHECK_OR_THROW_FOR_CLASS( filehandle.good(), "read_ascii_file_to_string_vector", "Could not open \"" + file_name + "\" for read." );
		while( !filehandle.eof() ) {
			outvec.push_back( std::string() );
			std::getline( filehandle, outvec[outvec.size() - 1] );
		}
		filehandle.close();
	}
	write_to_tracer( "Read \"" + file_name + "\"." );
	return outvec;
}

/// @brief Read the contents of an ASCII file to a string.
/// @details Threadsafe (locks mutex).
std::string
MasalaDiskManager::read_ascii_file_to_string(
	std::string const & file_name
) const {
	std::string outstring;
	{
		std::lock_guard< std::mutex > lock( disk_io_mutex_);
		std::ifstream filehandle( file_name );
		CHECK_OR_THROW_FOR_CLASS( filehandle.good(), "read_ascii_file_to_string", "Could not open \"" + file_name + "\" for read." );
		std::string stringbuf;
		bool first(true);
		while( !filehandle.eof() ) {
			if( first ){
				first = false;
			} else {
				outstring += "\n";
			}
			std::getline( filehandle, stringbuf );
			outstring += stringbuf;
		}
		filehandle.close();
	}
	write_to_tracer( "Read \"" + file_name + "\"." );
	return outstring;
}

/// @brief Read the contents of an pickled Python dictionary to a string.
/// @details Threadsafe (locks mutex).
std::string
MasalaDiskManager::read_pickled_python_dictionary_to_string(
	std::string const & file_name
) const {
	std::lock_guard< std::mutex > lock( disk_io_mutex_);
	std::ifstream filehandle( file_name, std::ios::binary | std::ios::ate );
	CHECK_OR_THROW_FOR_CLASS( filehandle.good(), "read_pickled_python_dictionary_to_string", "Could not open \"" + file_name + "\" for read." );

	// Get the size of the file.
	std::streamsize size = filehandle.tellg();
	filehandle.seekg(0, std::ios::beg);

	// Read the content into a vector of bytes.
	std::vector< char > buffer( size );
	filehandle.read( buffer.data(), size );

	// Close the file.
	filehandle.close();

	// Convert the bytes to a string that resembles a Python dictionary (excluding non-printable characters).
	std::stringstream dict;
	dict << "{";
	for (const char& c : buffer) {
		if (c >= 32 && c < 127) { 
			dict << c;
		} else {
			dict << "\\x" << std::hex << (int)c;
		}
	}
	dict << "}";
	write_to_tracer( "Read \"" + file_name + "\"." );
	return dict.str();
}

/// @brief Read the contents of a JSON file and produce an nlohmann json object.
/// @details Does not lock mutex directly, but calls read_ascii_file_to_string(), which
/// locks mutex.  (So this is threadsafe.)
nlohmann::json
MasalaDiskManager::read_json_file(
	std::string const & file_name
) const {
	std::string const json_file_contents( read_ascii_file_to_string( file_name ) );
	write_to_tracer( "Parsing JSON file \"" + file_name + "\"." );
	return nlohmann::json::parse( json_file_contents );
}

/// @brief Given a path, get the absolute path.
/// @details Threadsafe (locks mutex).
std::string
MasalaDiskManager::get_absolute_path(
	std::string const & path_in
) const {
	std::lock_guard< std::mutex > lock( disk_io_mutex_);
	std::filesystem::path curpath( path_in );
	return std::filesystem::absolute( curpath ).c_str();
}

/// @brief Given a path (absolute or relative to working directory), get
/// a vector of absolute paths to subdirectories.
/// @details Threadsafe (locks mutex).
std::vector< std::string >
MasalaDiskManager::get_subdirectories(
	std::string const & root_directory_path
) const {
	std::vector< std::string > pathlist;
	std::lock_guard< std::mutex > lock( disk_io_mutex_);
	std::filesystem::path const abs_path( std::filesystem::absolute( std::filesystem::path( root_directory_path ) ) );
	for( auto const & it : std::filesystem::directory_iterator( abs_path ) ) {
		if( it.is_directory() ) {
			pathlist.push_back( std::string( it.path().c_str() ) );
		}
	}
	return pathlist;
}

/// @brief Given a path to a directory, get the path and filename of each
/// file in that directory.
std::vector< std::string >
MasalaDiskManager::get_files(
	std::string const & directory_path
) const {
	std::vector< std::string > filelist;
	std::lock_guard< std::mutex > lock( disk_io_mutex_ );
	std::filesystem::path const abs_path( std::filesystem::absolute( std::filesystem::path( directory_path ) ) );
	for( auto const & it : std::filesystem::directory_iterator( abs_path ) ) {
		if( it.is_regular_file() ) {
			filelist.push_back( std::string( it.path().c_str() ) );
		}
	}
	return filelist;
}

/// @brief Given a path to a directory, get the path and filename of each
/// file in that directory.
std::vector< std::string >
MasalaDiskManager::get_files_regex(
	std::string const & directory_path,
	std::regex const & filename_pattern
) const {
	std::vector< std::string > filelist;
	std::lock_guard< std::mutex > lock( disk_io_mutex_ );
	std::filesystem::path const abs_path( std::filesystem::absolute( std::filesystem::path( directory_path ) ) );
	for( auto const & it : std::filesystem::directory_iterator( abs_path ) ) {
		if( it.is_regular_file() ) {
			std::string filename = it.path().filename().string();
			if( std::regex_match( filename, filename_pattern ) ) {
				filelist.push_back( filename );
			}
		}
	}
	return filelist;
}

/// @brief A utility function to get a filename given a path and a filename.
/// @details Requires no disk access.  Threadsafe, since no locking.
/*static*/
std::string
MasalaDiskManager::filename_from_path_and_filename(
	std::string const & path_and_filename
) {
	using namespace std::filesystem;
	return std::string( path( path_and_filename ).filename().c_str() );
}

/// @brief A utility function to get a unique, date- and thread-stamped version of a filename.
/// @details Requires no disk access.  Threadsafe, since no locking.
/// @returns prefix + "_thread_" + thread ID + "_" + YYYYMMDD + "_" + HHMMSS + suffix.
/// @note This will be updated to include MPI process in the future.
/*static*/
std::string
MasalaDiskManager::datestamped_filename(
	std::string const & prefix,
	std::string const & suffix,
	bool include_date /*= true*/,
	bool include_time /*= true*/,
	bool include_thread /*= true*/
) {
	using namespace masala::base::managers::threads;
	using namespace masala::base::utility::time;

#ifdef MASALA_MPI
	TODO TODO TODO; // Will trigger compilation error if support for stamping files by MPI process is not implemented.
#endif

	if( !( include_date || include_time || include_thread ) ) {
		return prefix + suffix;
	}

	std::ostringstream ss;
	bool add_underscore(false);

	if( !prefix.empty() ) {
		ss << prefix;
		if( prefix[prefix.size()-1] != '.' ) {
			add_underscore = true;
		}
	}

	// Adding thread:
	if( include_thread ) {
		MasalaThreadManagerHandle tm( MasalaThreadManager::get_instance() );
		if( add_underscore ) {
			ss << "_";
		} else {
			add_underscore = true;
		}
		if( tm->this_thread_is_a_masala_thread() ) {
			ss << "thread_" << tm->get_thread_manager_thread_id();
		} else {
			ss << "thread_UNKNOWN";
		}
	}

	// Get the current time:
	std::chrono::time_point< std::chrono::system_clock > const current_time( std::chrono::system_clock::now() );

	// Adding date stamp:
	if( include_date ) {
		if( add_underscore ) {
			ss << "_";
		} else {
			add_underscore = true;
		}
		ss << "date_" << masala_get_date_YYYYMMDD( current_time );
	}

	// Adding time stamp:
	if( include_time ) {
		if( add_underscore ) {
			ss << "_";
		} else {
			add_underscore = true;
		}
		ss << "time_" << masala_get_time_HHMMSS( current_time );
	}

	// Adding suffix:
	if( !suffix.empty()) {
		if( add_underscore && suffix[0] != '.' ) {
			ss << "_";
		}
		ss << suffix;
	}

	return ss.str();
}

/// @brief Delete a file.
/// @details Threadsafe (locks mutex). Optionally throws if the file is missing (true by default).
void
MasalaDiskManager::delete_file(
	std::string const & file_to_delete,
	bool const throw_if_missing /*= true*/
) const {
	std::lock_guard< std::mutex > lock( disk_io_mutex_ );
	bool const success( std::filesystem::remove( file_to_delete ) );
	if( throw_if_missing ) {
		CHECK_OR_THROW_FOR_CLASS( success, "delete_file", "Could not delete file " + file_to_delete + ".  This file was not found." );
	}
	if( success ) {
		write_to_tracer( "Deleted " + file_to_delete + "." );
	}
	else {
		write_to_tracer( "Could not delete " + file_to_delete + ".  File does not exist." );
	}
}

/// @brief Delete a bunch of files in a list.
/// @details Threadsafe (locks mutex).  More efficient than one-by-one deletion, since
/// the mutex is locked once for all of the deletions.  Optionally throws if any file
/// is missing (true by default).
void
MasalaDiskManager::delete_files(
	std::vector< std::string > const & files_to_delete,
	bool const throw_if_missing /*= true*/
) const {
	std::lock_guard< std::mutex > lock( disk_io_mutex_ );
	for( std::string const & file_to_delete : files_to_delete ) {
		bool const success( std::filesystem::remove( file_to_delete ) );
		if( throw_if_missing ) {
			CHECK_OR_THROW_FOR_CLASS( success, "delete_file", "Could not delete file " + file_to_delete + ".  This file was not found." );
		}
		if( success ) {
			write_to_tracer( "Deleted " + file_to_delete + "." );
		}
		else {
			write_to_tracer( "Could not delete " + file_to_delete + ".  File does not exist." );
		}
	}
}

} // namespace disk
} // namespace managers
} // namespace base
} // namespace masala
