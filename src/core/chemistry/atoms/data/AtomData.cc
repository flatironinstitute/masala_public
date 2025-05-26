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

/// @file src/core/chemistry/atoms/data/AtomData.cc
/// @brief A container data for additional optional data that might be
/// attached to an atom.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Class header:
#include <core/chemistry/atoms/data/AtomData.hh>

// Base headers:
#include <base/api/MasalaObjectAPIDefinition.hh>
#include <base/api/constructor/MasalaObjectAPIConstructorMacros.hh>

// STL headers:
#include <string>

namespace masala {
namespace core {
namespace chemistry {
namespace atoms {
namespace data {

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

/// @brief Default constructor.  Explicit due to mutex.
AtomData::AtomData() :
	masala::base::MasalaObject()
{}

/// @brief Copy constructor.  Explicit due to mutex.
AtomData::AtomData(
	AtomData const & src
) :
	masala::base::MasalaObject(src)
{
	std::lock( src.mutex_, mutex_ );
	std::lock_guard< std::mutex > lockthat( src.mutex_, std::adopt_lock );
	std::lock_guard< std::mutex > lockthis( mutex_, std::adopt_lock );
	protected_assign( src );
}

/// @brief Make this object independent by making a deep copy of all of its private members.
/// @details Threadsafe.  Be sure to update this function whenever a private member is added!
void
AtomData::make_independent() {
	std::lock_guard< std::mutex > lock(mutex_);
	protected_make_independent();
}

/// @brief Get the name of this class ("AtomData").
std::string
AtomData::class_name() const {
	return "AtomData";
}

/// @brief Get the namespace of this class ("masala::core::chemistry::atoms::data").
std::string
AtomData::class_namespace() const {
	return "masala::core::chemistry::atoms::data";
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the API definition for this object.
masala::base::api::MasalaObjectAPIDefinitionCWP
AtomData::get_api_definition() {
	using namespace masala::base::api;
	using namespace masala::base::api::constructor;
	
	std::lock_guard< std::mutex > lock( mutex_ );

	if( api_definition_ == nullptr ) {
		MasalaObjectAPIDefinitionSP apidef(
			masala::make_shared< MasalaObjectAPIDefinition >(
				*this, "A base class for additional data that can be attached to an atom.  This "
				"class is not intended to be instantiated, but only to serve as a base class.",
				false, true
			)
		);

		ADD_PROTECTED_CONSTRUCTOR_DEFINITIONS( AtomData, apidef );

		api_definition_ = apidef;
	}

	return api_definition_;
}

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Make this object fully indpendent.
/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
void
AtomData::protected_make_independent() {
	//GNDN.
}

/// @brief Assign src to this.
/// @details Must be implemented by derived classes.  Should call parent class protected_make_independent().
/// @note This is called from a mutex-locked context.  Should do no mutex-locking.
void
AtomData::protected_assign(
	AtomData const & //src
) {
	//GNDN.
}

} // namespace data
} // namespace atoms
} // namespace chemistry
} // namespace core
} // namespace masala