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

/// @file src/base/managers/disk/MasalaDiskManager.hh
/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_disk_MasalaDiskManager_hh
#define Masala_src_base_managers_disk_MasalaDiskManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/disk/MasalaDiskManager.fwd.hh>

// External headers:
#include <external/nlohmann_json/single_include/nlohmann/json_fwd.hpp>

// STL headers:
#include <mutex>
#include <regex>

namespace masala {
namespace base {
namespace managers {
namespace disk {

/// @brief A static singleton for managing disk access.
/// @details All disk i/o must go through this manager.
class MasalaDiskManager : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC STATIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaDiskManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaDiskManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaDiskManager( MasalaDiskManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaDiskManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaDiskManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaDiskManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::disk".
    std::string
    class_namespace() const override;

    /// @brief Write a string to an ASCII file.
    /// @details TRIGGERS WRITE TO DISK!  Threadsafe (locks mutex).
    void
    write_ascii_file(
        std::string const & file_name,
        std::string const & file_contents
    ) const;

    /// @brief Read the contents of an ASCII file to a vector of strings.
    /// @details Threadsafe (locks mutex).
    std::vector< std::string >
    read_ascii_file_to_string_vector(
        std::string const & file_name
    ) const;

    /// @brief Read the contents of an ASCII file to a string.
    /// @details Threadsafe (locks mutex).
    std::string
    read_ascii_file_to_string(
        std::string const & file_name
    ) const;

    /// @brief Read the contents of a JSON file and produce an nlohmann json object.
    /// @details Does not lock mutex directly, but calls read_ascii_file_to_string(), which
    /// locks mutex.  (So this is threadsafe.)
    nlohmann::json
    read_json_file(
        std::string const & file_name
    ) const;

    /// @brief Read the contents of an pickled Python dictionary to a string.
    /// @details Threadsafe (locks mutex).
    std::string
    read_pickled_python_dictionary_to_string(
        std::string const & file_name
    ) const;

    /// @brief Given a path, get the absolute path.
    /// @details Threadsafe (locks mutex).
    std::string
    get_absolute_path(
        std::string const & path_in
    ) const;

    /// @brief Given a path (absolute or relative to working directory), get
    /// a vector of absolute paths to subdirectories.
    /// @details Threadsafe (locks mutex).
    std::vector< std::string >
    get_subdirectories(
        std::string const & root_directory_path
    ) const;

    /// @brief Given a path to a directory, get the path and filename of each
    /// file in that directory.
    /// @details Threadsafe (locks mutex).
    std::vector< std::string >
    get_files(
        std::string const & directory_path
    ) const;


    /// @brief Given a path to a directory and a regex expression, get the path and filename of each
    /// file matching the regex expression in that directory.
    /// @details Threadsafe (locks mutex).
    std::vector< std::string >
    get_files_regex(
        std::string const & directory_path,
        std::regex const & filename_pattern
    ) const;

    /// @brief A utility function to get a filename given a path and a filename.
    /// @details Requires no disk access.  Threadsafe, since no locking.
    static
    std::string
    filename_from_path_and_filename(
        std::string const & path_and_filename
    );

private: // Data

    /// @brief A mutex to ensure that one thread at a time does disk i/o.
    mutable std::mutex disk_io_mutex_;

};

} // namespace disk
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_disk_MasalaDiskManager_hh