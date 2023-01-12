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

// External headers:
#include <external/nlohmann_json/single_include/nlohmann/json.hpp>

// STL headers:
#include <string>
#include <filesystem> //This is the only place in the Masala codebase where this header is permitted to be included.
#include <fstream> //This is the only place in the Masala codebase where this header is permitted to be included.

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
    std::lock_guard< std::mutex > lock( disk_io_mutex_);
    std::filesystem::path const abs_path( std::filesystem::absolute( std::filesystem::path( root_directory_path ) ).c_str() );
    std::vector< std::string > pathlist;
    for( auto const & it : std::filesystem::directory_iterator( abs_path ) ) {
        pathlist.push_back( std::string( it.path().c_str() ) );
    }
    return pathlist;
}

} // namespace disk
} // namespace managers
} // namespace base
} // namespace masala
