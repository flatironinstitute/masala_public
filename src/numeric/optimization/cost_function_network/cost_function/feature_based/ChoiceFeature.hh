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

/// @file src/numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.hh
/// @brief Headers for a class for ChoiceFeatures.
/// @details ChoiceFeatures are objects attached to node choices, which can form connections across
/// choices at different nodes.  Each feature has a minimum and maximum number of connections that
/// it must make to be satisfied.
/// @note This class is a lightweight class that offers thread safety for the API definition only.  There
/// are no setters, so everything is set in the constructor, and it's read-only after that.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_hh
#define Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_hh

// Forward declarations:
#include <numeric/optimization/cost_function_network/cost_function/feature_based/ChoiceFeature.fwd.hh>

// Parent header:
#include <base/managers/plugin_module/MasalaPlugin.hh>

// Numeric headers:

// Base headers:
#include <base/types.hh>

// STL headers:
#include <atomic>
#include <mutex>

namespace masala {
namespace numeric {
namespace optimization {
namespace cost_function_network {
namespace cost_function {
namespace feature_based {

/// @brief A pure virtual base class for ChoiceFeatures.
/// @brief A class for ChoiceFeatures.
/// @details ChoiceFeatures are objects attached to node choices, which can form connections across
/// choices at different nodes.  Each feature has a minimum and maximum number of connections that
/// it must make to be satisfied.
/// @note This class is a lightweight class that offers thread safety for the API definition only.  There
/// are no setters, so everything is set in the constructor, and it's read-only after that.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class ChoiceFeature : public masala::base::managers::plugin_module::MasalaPlugin {

public:

////////////////////////////////////////////////////////////////////////////////
// CONSTRUCTION AND DESTRUCTION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Default constructor, deleted.
	ChoiceFeature() = delete;

	/// @brief Constructor with min and max connections for satisfaction, and
	/// the offset (number of connections from internal satisfaction or background).
	ChoiceFeature(
		masala::base::Size min_connections,
		masala::base::Size max_connections,
		masala::base::Size offset = 0
	);

	/// @brief Copy constructor.
	ChoiceFeature(
		ChoiceFeature const &
	);

	// @brief Assignment operator.
	ChoiceFeature &
	operator=( ChoiceFeature const & );

	/// @brief Destructor.
	~ChoiceFeature() override = default;

	/// @brief Copy this object and return a shared pointer to the copy.
	ChoiceFeatureSP clone() const override;

	/// @brief Ensure that this object is fully independent.
	void make_independent() override;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the category or categories for this plugin class.  Default for all
	/// cost functions; may be overridden by derived classes.
	/// @returns { { "ChoiceFeature" } }
	/// @note Categories are hierarchical (e.g. Selector->AtomSelector->AnnotatedRegionSelector,
	/// stored as { {"Selector", "AtomSelector", "AnnotatedRegionSelector"} }). A plugin can be
	/// in more than one hierarchical category (in which case there would be more than one
	/// entry in the outer vector), but must be in at least one.  The first one is used as
	/// the primary key.
	std::vector< std::vector< std::string > >
	get_categories() const override;

	/// @brief Get the keywords for this plugin class.
	/// @returns { "optimization_problem", "cost_function", "numeric", "choice_feature" }
	std::vector< std::string >
	get_keywords() const override;

	/// @brief This returns the class name ("ChoiceFeature").
	std::string class_name() const override;

	/// @brief This returns the class namespace ("masala::numeric::optimization::cost_function_network::cost_function::feature_based").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// WORK FUNCTIONS
////////////////////////////////////////////////////////////////////////////////


public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC INTERFACE DEFINITION
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get an object describing the API for this object.
	/// @details Default implementation returns nullptr.  May be overridden by
	/// derived objects.
	/// @note This is a weak pointer rather than a shared pointer since the
	/// original object is expected to hold on to its API definition (which includes
	/// funciton pointers to the functions of the instance).  Querying whether the
	/// weak pointer can be converted to a shared pointer serves on a check as to
	/// whether it is safe to use the function pointers.  Not ideal, but better than
	/// nothing.
	masala::base::api::MasalaObjectAPIDefinitionCWP
	get_api_definition() override;

protected:

////////////////////////////////////////////////////////////////////////////////
// PROTECTED FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Assign this object based on src.  Assumes that both locks have been set.
	void
	protected_assign(
		ChoiceFeature const & src
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The mutex for this object.
	std::mutex mutex_;

	/// @brief The API definition for this object.  Nullptr if not yet accessed.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief The minimum number of connections.
	masala::base::Size const min_connections_ = 0;

	/// @brief The maximum number of connections.
	masala::base::Size const max_connections_ = 0;

	/// @brief The offset.  (e.g. The number of hydrogen bonds satisfied to background or
	/// by internal connections.)
	masala::base::Size const offset_ = 0;

}; // class ChoiceFeature

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_hh