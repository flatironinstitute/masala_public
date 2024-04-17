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

/// @file src/base/managers/engine/data_representation_request/MasalaDataRepresentationNameRequirementCriterion.hh
/// @brief Headers for a class for imposing the condition that a particular data representation
/// have a particular name.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationNameRequirementCriterion_hh
#define Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationNameRequirementCriterion_hh

// Forward declarations:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationNameRequirementCriterion.fwd.hh>

// Parent header:
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {
namespace data_representation_request {

/// @brief A class for imposing the condition that a particular data representation have a particular name.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationNameRequirementCriterion : public masala::base::managers::engine::data_representation_request::MasalaDataRepresentationRequestCriterion {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION, DESTRUCTION, AND CLONING
////////////////////////////////////////////////////////////////////////////////

    /// @brief Default constructor.
    MasalaDataRepresentationNameRequirementCriterion() = default;

    /// @brief Options constructor.
    MasalaDataRepresentationNameRequirementCriterion( std::string const & name_in );

    /// @brief Copy constructor.
    MasalaDataRepresentationNameRequirementCriterion( MasalaDataRepresentationNameRequirementCriterion const & ) = default;

    // Destructor.
    ~MasalaDataRepresentationNameRequirementCriterion() override = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationNameRequirementCriterion".
    std::string class_name() const override;

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    std::string class_namespace() const override;

    /// @brief Get the name of this class.
    /// @returns "MasalaDataRepresentationNameRequirementCriterion".
    static std::string class_name_static();

    /// @brief Get the namespace of this class.
    /// @returns "masala::base::managers::engine::data_representation_request".
    static std::string class_namespace_static();

    /// @brief Determine whether a particular data representation is compatible with this criterion.
    /// @returns True if it is compatible, false otherwise.
    bool
    data_representation_is_compatible_with_criterion(
        masala::base::managers::engine::MasalaDataRepresentationCreator const & creator
    ) const override;

	/// @brief Set the name that we're matching.
	/// @details The name string may or may not include the namespace.  If it does not, any short
	/// name that matches is a match.  If it does, then the full name including namespace must match.
	void set_name( std::string const & name_in );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

private:

	/// @brief Static function that splits a namespace and name string (separated by double colons)
	/// into a name string and a namespace vector.
	static
	void
	get_name_and_namespace(
		std::string const & namespace_and_name_in,
		std::string & name_out,
		std::vector< std::string > & namespace_out
	);

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief The class name that we are matching.
	std::string class_name_to_match_;

	/// @brief The class namespace that we are matching.
	/// @details May be empty.
	std::vector< std::string > class_namespace_to_match_;

};

} // namespace data_representation_request
} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_data_representation_request_MasalaDataRepresentationNameRequirementCriterion_hh