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

/// @file src/base/managers/plugin_module/MasalaDataRepresentationRequest.hh
/// @brief Headers for a class used to request data representations.
/// @details This class stores a list of criteria that a data representation must satisfy.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationRequest_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationRequest_hh

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationRequest.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/data_representation_request/MasalaDataRepresentationRequestCriterion.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A class used to request data representations.
/// @details This class stores a list of criteria that a data representation must satisfy.
/// @note This class is not threadsafe.  It is expected to be created, used, and destroyed
/// by a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationRequest : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaDataRepresentationRequest() = default;

	/// @brief Copy constructor.
	MasalaDataRepresentationRequest( MasalaDataRepresentationRequest const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaDataRepresentationRequest() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Every class can name itself.
    /// @returns "MasalaDataRepresentationRequest".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
    /// @returns "masala::base::managers::engine".
	std::string class_namespace() const override;

    /// @brief Every class can name itself.  Static version.
    /// @returns "MasalaDataRepresentationRequest".
	static std::string class_name_static();

	/// @brief Every class can provide its own namespace.  Static version.
    /// @returns "masala::base::managers::engine".
	static std::string class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Add a requirement that data representations have a particular name.
	/// @details The input name may or may not include namespace.  If it DOES, then the full
	/// name must match.  If it does NOT, then the short name must match.
	void
	add_data_representation_name_requirement(
		std::string const & name_in
	);

    /// @brief Add a requirement that data representations are explicitly marked as compatible
    /// with a particular MasalaEngine.
    /// @note The engine must be provided as a full name (namespace + name).
    void
    add_engine_compatibility_requirement(
        std::string const & engine_namespace_and_name
    );

    /// @brief Add a requirement that data representations are explicitly marked as compatible
    /// with one of a set of MasalaEngines.
    /// @details If match_any is true (the default), then the Masala data representation must be compatible
    /// with at least one engine from the list.  Otherwise, it must be compatible with all of them.
    /// @note The engines must be provided as a full name (namespace + name).
    void
    add_engines_compatibility_requirement(
        std::vector< std::string > const & engine_namespaces_and_names,
        bool const match_any = true
    );

    /// @brief Add a requirement that data representations are explicitly marked as incompatible
    /// with a particular MasalaEngine.
    /// @note The engine must be provided as a full name (namespace + name).
    void
    add_engine_incompatibility_requirement(
        std::string const & engine_namespace_and_name
    );

    /// @brief Add a requirement that data representations are explicitly marked as incompatible
    /// with one of a set of MasalaEngines.
    /// @details If match_any is true (the default), then the Masala data representation must be incompatible
    /// with at least one engine from the list.  Otherwise, it must be incompatible with all of them.
    /// @note The engines must be provided as a full name (namespace + name).
    void
    add_engines_incompatibility_requirement(
        std::vector< std::string > const & engine_namespaces_and_names,
        bool const match_any = true
    );

    /// @brief Add a requirement that data representations be in one of a set of
    /// data representation categories.
    /// @details Categories are provided as a vector of vectors of strings.  For instance, if
    /// we want to indicate that a data representation may be in Fruits->Apples->MacIntoshApples
    /// or in Vegetables->RootVegetables->Carrots, we provide {
    ///     { "Fruits", "Apples", "MacIntoshApples" },
    ///     { "Vegetables", "RootVegetables", "Carrots" }, 
    /// }.
    /// @note If allow_subcategories is true, then representations may be in subcategories
    /// of these categories.  A data representation matches if it is in ANY category listed.
    void
    add_data_representation_category_requirement(
        std::vector< std::vector< std::string > > const & categories,
        bool const allow_subcategories
    );

    /// @brief Add a requirement that data representations NOT be in ANY of a set of
    /// data representation categories.
    /// @details Categories are provided as a vector of vectors of strings.  For instance, if
    /// we want to indicate that a data representation may not be in Fruits->Apples->MacIntoshApples
    /// or in Vegetables->RootVegetables->Carrots, we provide {
    ///     { "Fruits", "Apples", "MacIntoshApples" },
    ///     { "Vegetables", "RootVegetables", "Carrots" }, 
    /// }.
    /// @note If allow_subcategories is true, then representations that are in subcategories
    /// of these categories are also excluded.  A data representation is excluded if it is in ANY
    /// category listed.
    void
    add_data_representation_category_exclusion(
        std::vector< std::vector< std::string > > const & categories,
        bool const allow_subcategories
    );

	/// @brief Add an arbitrary criterion to the list of criteria that must be true.
	/// @note Input is used directly, not cloned.
	void
	add_criterion(
		data_representation_request::MasalaDataRepresentationRequestCriterionCSP const & criterion_in
	);

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Check whether a particular creator is compatible with the criteria listed.
    /// @returns True for compatibility, false for incompatibility.
    bool
    data_representation_is_compatible_with_criteria(
        MasalaDataRepresentationCreator const & creator
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The criteria that must be satisfied by this request.
    std::vector< data_representation_request::MasalaDataRepresentationRequestCriterionCSP > request_criteria_;

}; // class MasalaDataRepresentationRequest

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaDataRepresentationRequest_hh