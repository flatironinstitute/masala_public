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

/// @file src/core/chemistry/atoms/data/AtomData.hh
/// @brief A container for additional optional data that might be
/// attached to an atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_core_chemistry_atoms_data_AtomData_hh
#define Masala_src_core_chemistry_atoms_data_AtomData_hh

// Forward declarations:
#include <core/chemistry/atoms/data/AtomData.fwd.hh>

// Core headers:

// Base headers:
#include <base/MasalaObject.hh>

// STL headers:
#include <mutex>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace data {


/// @brief A container for additional optional data that might be
/// attached to an atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class AtomData : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.  Explicit due to mutex.
	AtomData();

	/// @brief Copy constructor.  Explicit due to mutex.
	AtomData( AtomData const & src );

	/// @brief Default destructor.
	~AtomData() override = default;

	/// Assignment operator.  Explicit due to mutex.
	AtomData & operator=( AtomData const & src );

	/// @brief Clone operation: make a copy of this object and return a shared pointer
	/// to the copy.
	virtual AtomDataSP clone() const;

	/// @brief Deep clone operation: make a deep copy of this object and return a shared
	/// pointer to the deep copy.
	/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
	AtomDataSP deep_clone() const;

	/// @brief Make this object independent by making a deep copy of all of its private members.
	/// @details Be sure to update this function whenever a private member is added!
	void
	make_independent();

	/// @brief Get the name of this class ("AtomData").
	std::string class_name() const override;

	/// @brief Get the namespace of this class ("masala::core::chemistry::atoms::data").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Allow derived classes to access the mutex.
	inline std::mutex & mutex() const { return mutex_; }

	/// @brief Allow derived classes to access the API definition for this object.  Could be nullptr.
	inline masala::base::api::MasalaObjectAPIDefinitionCSP & api_definition() { return api_definition_; }

	/// @brief Allow derived classes to access the API definition for this object.  Could be nullptr.
	inline masala::base::api::MasalaObjectAPIDefinitionCSP const & api_definition() const { return api_definition_; }

	/// @brief Make this object fully indpendent.
	/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
	/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
	virtual
	void
	protected_make_independent();

	/// @brief Assign src to this.
	/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
	/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
	virtual
	void
	protected_assign(
		AtomData const & src
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

	/// @brief A mutex for this object.
	mutable std::mutex mutex_;

	/// @brief API definition for this object.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;


};

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala

#endif // Masala_src_core_chemistry_atoms_data_AtomData_hh