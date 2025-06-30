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

/// @file src/base/managers/file_interpreter/MasalaFileInterpreterManager.hh
/// @brief Header for a static singleton for managing modules responsible for reading and writing particular
/// file formats, and converting these to and from particular data representations.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_file_interpreter_MasalaFileInterpreterManager_hh
#define Masala_src_base_managers_file_interpreter_MasalaFileInterpreterManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/file_interpreter/MasalaFileInterpreterManager.fwd.hh>
#include <base/managers/file_interpreter/MasalaFileInterpreterCreator.fwd.hh>

// Base headers:
#include <base/types.hh>
#include <base/api/names_from_types.tmpl.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace base {
namespace managers {
namespace file_interpreter {

/// @brief A static singleton for managing modules responsible for reading and writing particular
/// file formats, and converting these to and from particular data representations.
class MasalaFileInterpreterManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaFileInterpreterManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaFileInterpreterManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaFileInterpreterManager( MasalaFileInterpreterManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaFileInterpreterManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaFileInterpreterManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaFileInterpreterManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::file_interpreter".
    std::string
    class_namespace() const override;

    /// @brief Completely reset the manager.
    /// @details Unregisters all file interpreters.
    void reset();

    /// @brief Get the number of registered file interpreters.
    masala::base::Size total_file_interpreters() const;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS FOR REGISTERING AND UNREGISTERING FILE INTERPRETERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Add a file interpreter to the ones registered with this manager.
	/// @details Throws if the file interpreter has already been added.
	/// @param creator_in The creator for the new file interpreter plugin type.
	void
	register_file_interpreter(
		MasalaFileInterpreterCreatorCSP const & creator_in
	);

	/// @brief Add some new file interpreters to the ones registered with this manager.
	/// @details Throws if any of the file interpreters has already been added.
	/// @param creators_in A vector of creators for the new file interpreter plugin types.
	void
	register_file_interpreters(
		std::vector< MasalaFileInterpreterCreatorCSP > const & creators_in
	);

	/// @brief Remove a file interpreter from the ones registered with this manager.
	/// @details Throws if the file interpreter has not already been added.
	/// @param creator_to_remove A creator for the file interpreter plugin type
	/// to remove.
	void
	unregister_file_interpreter(
		MasalaFileInterpreterCreatorCSP const & creator_to_remove
	);

	/// @brief Remove some file interpreters from the ones registered with this manager.
	/// @details Throws if any of the file interpreters have not already been added.
	/// @param creators_to_remove A vector of creators for the file interpreter plugin types
	/// to remove.
	void
	unregister_file_interpreters(
		std::vector< MasalaFileInterpreterCreatorCSP > const & creators_to_remove
	);

public:

////////////////////////////////////////////////////////////////////////////////
// FUNCTIONS FOR RETRIEVING FILE INTERPRETER CREATORS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get a file interpreter creator, by the full name (including namespace)
	/// of the file interpreter that it creates.
	/// @returns A shared pointer to the creator, or nullptr if the name can't be matched.
	MasalaFileInterpreterCreatorCSP
	get_file_interpreter_by_full_name(
		std::string const & name_in
	) const;

	/// @brief Get a vector of file interpreter creators, by the short name (excluding namespace)
	/// of the file interpreter that the creator should create.
	/// @returns A vector of shared pointers to the creator(s) that match the short name.  Could
	/// be an empty vector if nothing matches.
	std::vector< MasalaFileInterpreterCreatorCSP >
	get_file_interpreters_by_short_name(
		std::string const & name_in
	) const;

	/// @brief Get a vector of file interpreter creators, by file type descriptor.
	/// @details File type descriptor is something like "protein_data_bank_file".  More than one file
	/// interpreter could handle the same file type descriptor.
	/// @returns A vector of shared pointers to the creator(s) that match the file type descriptor.  Could
	/// be an empty vector if nothing matches.
	std::vector< MasalaFileInterpreterCreatorCSP >
	get_file_interpreters_by_file_type_descriptor(
		std::string const & descriptor_in
	) const;

	/// @brief Get a vector of file interpreter creators, by file type extension.
	/// @details File type extension is something like "pdb" (in lowercase).  More than one file
	/// interpreter could handle the same file type extension.
	/// @returns A vector of shared pointers to the creator(s) that match the file type extension.  Could
	/// be an empty vector if nothing matches.
	std::vector< MasalaFileInterpreterCreatorCSP >
	get_file_interpreters_by_file_type_extension(
		std::string const & file_type_extension
	) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Register a file interpreter creator.
	/// @details To be called from a mutex-locked context (i.e. does not lock the mutex itself).
	/// Throws if the file interpreter has already been added.
	void
	private_register_file_interpreter(
		MasalaFileInterpreterCreatorCSP const & creator_in
	);

	/// @brief Unregister a file interpreter creator.
	/// @details To be called from a mutex-locked context (i.e. does not lock the mutex itself).
	/// Throws if the file interpreter has not been added.
	void
	private_unregister_file_interpreter(
		MasalaFileInterpreterCreatorCSP const & creator_to_remove
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for locking this singleton.
	mutable std::mutex file_interpreter_manager_mutex_;

	/// @brief A map of file interpreters, by (full) name.
	std::map< std::string, MasalaFileInterpreterCreatorCSP > file_interpreters_by_name_;

	/// @brief A map of file interpreters, by file type descriptor.
	/// @details File type descriptor is something like "protein_data_bank_file".  More than one file
	/// interpreter could handle the same file type descriptor.
	std::map< std::string, std::vector< MasalaFileInterpreterCreatorCSP > > file_interpreters_by_file_type_descriptor_;

	/// @brief A map of file interpreters, by file type extension.
	/// @details File type extension is something like "pdb" (in lowercase).  More than one file
	/// interpreter could handle the same file type extension.
	std::map< std::string, std::vector< MasalaFileInterpreterCreatorCSP > > file_interpreters_by_file_type_extension_;

};

} // namespace file_interpreter
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_file_interpreter_MasalaFileInterpreterManager_hh