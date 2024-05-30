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

/// @file src/base/managers/plugin_module/MasalaEngineRequest.hh
/// @brief Headers for a class used to request engines.
/// @details This class stores a list of criteria that an engine must satisfy.
/// @note This class is not threadsafe.  It is expected to be created, used, and destroyed
/// by a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaEngineRequest_hh
#define Masala_src_base_managers_engine_MasalaEngineRequest_hh

// Forward declarations:
#include <base/managers/engine/MasalaEngineRequest.fwd.hh>

// Base headers:
#include <base/MasalaObject.hh>
#include <base/managers/engine/engine_request/MasalaEngineRequestCriterion.fwd.hh>
#include <base/managers/engine/MasalaEngineCreator.fwd.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief A class used to request engines.
/// @details This class stores a list of criteria that an engine must satisfy.
/// @note This class is not threadsafe.  It is expected to be created, used, and destroyed
/// by a single thread.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaEngineRequest : public masala::base::MasalaObject {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor.
	MasalaEngineRequest() = default;

	/// @brief Copy constructor.
	MasalaEngineRequest( MasalaEngineRequest const & ) = default;

	/// @brief Destructor.
	virtual ~MasalaEngineRequest() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Every class can name itself.
    /// @returns "MasalaEngineRequest".
	std::string class_name() const override;

	/// @brief Every class can provide its own namespace.
    /// @returns "masala::base::managers::engine".
	std::string class_namespace() const override;

    /// @brief Every class can name itself.  Static version.
    /// @returns "MasalaEngineRequest".
	static std::string class_name_static();

	/// @brief Every class can provide its own namespace.  Static version.
    /// @returns "masala::base::managers::engine".
	static std::string class_namespace_static();

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Add a requirement that engines have a particular name.
	/// @details The input name may or may not include namespace.  If it DOES, then the full
	/// name must match.  If it does NOT, then the short name must match.
	void
	add_engine_name_requirement(
		std::string const & name_in
	);

    /// @brief Add a requirement that engines be in one of a set of
    /// engine categories.
    /// @details Categories are provided as a vector of vectors of strings.  For instance, if
    /// we want to indicate that an engine may be in Fruits->Apples->MacIntoshApples
    /// or in Vegetables->RootVegetables->Carrots, we provide {
    ///     { "Fruits", "Apples", "MacIntoshApples" },
    ///     { "Vegetables", "RootVegetables", "Carrots" }, 
    /// }.
    /// @note If allow_subcategories is true, then engines may be in subcategories
    /// of these categories.  An engine matches if it is in ANY category listed.
    void
    add_engine_category_requirement(
        std::vector< std::vector< std::string > > const & categories,
        bool const allow_subcategories
    );

    /// @brief Add a requirement that engines NOT be in ANY of a set of
    /// engine categories.
    /// @details Categories are provided as a vector of vectors of strings.  For instance, if
    /// we want to indicate that an engine may not be in Fruits->Apples->MacIntoshApples
    /// or in Vegetables->RootVegetables->Carrots, we provide {
    ///     { "Fruits", "Apples", "MacIntoshApples" },
    ///     { "Vegetables", "RootVegetables", "Carrots" }, 
    /// }.
    /// @note If allow_subcategories is true, then engines that are in subcategories
    /// of these categories are also excluded.  An engine is excluded if it is in ANY
    /// category listed.
    void
    add_engine_category_exclusion(
        std::vector< std::vector< std::string > > const & categories,
        bool const allow_subcategories
    );

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Check whether a particular creator is compatible with the criteria listed.
    /// @returns True for compatibility, false for incompatibility.
    bool
    engine_is_compatible_with_criteria(
        MasalaEngineCreator const & creator
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER DATA
////////////////////////////////////////////////////////////////////////////////

    /// @brief The criteria that must be satisfied by this request.
    std::vector< engine_request::MasalaEngineRequestCriterionSP > request_criteria_;

}; // class MasalaEngineRequest

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif //Masala_src_base_managers_engine_MasalaEngineRequest_hh