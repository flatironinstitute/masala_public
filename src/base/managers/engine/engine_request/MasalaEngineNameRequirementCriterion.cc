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

/// @file src/base/managers/engine/engine_request/MasalaEngineNameRequirementCriterion.cc
/// @brief A class for imposing the condition that a particular engine be in (or not in) a particular category.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Headers:
#include <base/managers/engine/engine_request/MasalaEngineNameRequirementCriterion.hh>

// Base headers:
#include <base/utility/container/container_util.tmpl.hh>
#include <base/utility/string/string_manipulation.hh>
#include <base/error/ErrorHandling.hh>
#include <base/types.hh>
#include <base/managers/engine/MasalaEngineCreator.hh>

// STL headers:
#include <vector>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace engine_request {

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Options constructor.
MasalaEngineNameRequirementCriterion::MasalaEngineNameRequirementCriterion(
	std::string const & name_in
) :
	MasalaEngineRequestCriterion()
{
	set_name( name_in );
}

/// @brief Get the name of this class.
/// @returns "MasalaEngineNameRequirementCriterion".
std::string
MasalaEngineNameRequirementCriterion::class_name() const {
    return class_name_static();
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
std::string
MasalaEngineNameRequirementCriterion::class_namespace() const {
    return class_namespace_static();
}

/// @brief Get the name of this class.
/// @returns "MasalaEngineNameRequirementCriterion".
/*static*/
std::string
MasalaEngineNameRequirementCriterion::class_name_static() {
    return "MasalaEngineNameRequirementCriterion";
}

/// @brief Get the namespace of this class.
/// @returns "masala::base::managers::engine::engine_request".
/*static*/
std::string
MasalaEngineNameRequirementCriterion::class_namespace_static() {
    return "masala::base::managers::engine::engine_request";
}

/// @brief Determine whether a particular engine is compatible with this criterion.
/// @returns True if it is compatible, false otherwise.
bool
MasalaEngineNameRequirementCriterion::engine_is_compatible_with_criterion(
    masala::base::managers::engine::MasalaEngineCreator const & creator
) const {
    CHECK_OR_THROW_FOR_CLASS( !class_name_to_match_.empty(), "engine_is_compatible_with_criterion",
		"The class name to match must be set before this function is called."
	);
	std::string other_name;
	std::vector< std::string > other_namespace;
	get_name_and_namespace( creator.get_plugin_object_namespace_and_name(), other_name, other_namespace );
	if( class_name_to_match_ != other_name ) {
		return false;
	}
	if( !class_namespace_to_match_.empty() && class_namespace_to_match_ != other_namespace ) {
		return false;
	}
	return true;
}

/// @brief Set the name that we're matching.
/// @details The name string may or may not include the namespace.  If it does not, any short
/// name that matches is a match.  If it does, then the full name including namespace must match.
void
MasalaEngineNameRequirementCriterion::set_name(
	std::string const & name_in
) {
	get_name_and_namespace( name_in, class_name_to_match_, class_namespace_to_match_ );
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Static function that splits a namespace and name string (separated by double colons)
/// into a name string and a namespace vector.
/*static*/
void
MasalaEngineNameRequirementCriterion::get_name_and_namespace(
	std::string const & namespace_and_name_in,
	std::string & name_out,
	std::vector< std::string > & namespace_out
) {
	name_out.clear();
	namespace_out.clear();
	namespace_out = masala::base::utility::string::split_by_character( namespace_and_name_in, ':' );
	std::vector< std::string >::iterator it( namespace_out.end() );
	--it;
	name_out = (*it);
	namespace_out.erase(it);
}

} // namespace engine_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
