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
/// @note This class is a lightweight class.  It offers thread safety during setup only.  After finalization,
/// it is read-only.
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
#include <base/hash_types.hh>

// STL headers:
#include <atomic>
#include <mutex>
#include <set>
#include <unordered_map>

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
/// @note This class is a lightweight class.  It offers thread safety during setup only.  After finalization,
/// it is read-only.
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
	virtual ChoiceFeatureSP clone() const;

	/// @brief Copy this object and return a fully independent shared pointer to the copy.
	ChoiceFeatureSP deep_clone() const;

	/// @brief Ensure that this object is fully independent.
	virtual void make_independent();

	/// @brief Finalize this object.
	/// @param[in] variable_node_indices_by_absolute_node_index A map of all of the variable node indices
	/// for nodes that have more than one choice, indexed by absolute node index.
	void finalize(
		std::unordered_map< masala::base::Size, masala::base::Size > const & variable_node_indices_by_absolute_node_index
	);

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

	/// @brief This returns the class name ("ChoiceFeature").  Static version.
	static
	std::string class_name_static();

	/// @brief This returns the class namespace ("masala::numeric::optimization::cost_function_network::cost_function::feature_based").
	/// Static version.
	static
	std::string class_namespace_static();

	/// @brief This returns the class name ("ChoiceFeature").
	std::string class_name() const override;

	/// @brief This returns the class namespace ("masala::numeric::optimization::cost_function_network::cost_function::feature_based").
	std::string class_namespace() const override;

public:

////////////////////////////////////////////////////////////////////////////////
// GETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Get the minimum number of connections that this feature must have to be satisfied.
	/// @note Assumes finalized.  Throws in debug mode if not finalized.
	masala::base::Size min_connections() const;

	/// @brief Get the maximum number of connections that this feature must have to be satisfied.
	/// @note Assumes finalized.  Throws in debug mode if not finalized.
	masala::base::Size max_connections() const;

	/// @brief Get the offset in the number of connections (the number of connections that are
	/// @note Assumes finalized.  Throws in debug mode if not finalized.
	/// always satisfied).
	masala::base::Size offset() const;

public:

////////////////////////////////////////////////////////////////////////////////
// SETTERS
////////////////////////////////////////////////////////////////////////////////

	/// @brief Indicate that a particular choice at another node satisfies this feature.
	/// @details This feature must not be finalized yet.  Threadsafe.
	/// @param other_node_absolute_index The other node index (absolute index, not variable index).
	/// @param other_choice_index The other choice index.
	/// @param n_connections The number of connections that are made from the features of the
	/// other node choice to this feature.
	void
	add_other_node_and_choice_that_satisfies_this(
		masala::base::Size const other_node_absolute_index,
		masala::base::Size const other_choice_index,
    	masala::base::Size const n_connections
	);

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

	/// @brief Assign this object based on src.  Assumes that both mutexes have been locked.
	virtual
	void
	protected_assign(
		ChoiceFeature const & src
	);

	/// @brief Finalize this object.  Assumes that mutex has been locked.
	/// @param[in] variable_node_indices_by_absolute_node_index A map of all of the variable node indices
	/// for nodes that have more than one choice, indexed by absolute node index.
	virtual
	void
	protected_finalize(
		std::unordered_map< masala::base::Size, masala::base::Size > const & variable_node_indices_by_absolute_node_index
	);

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE VARIABLES
////////////////////////////////////////////////////////////////////////////////

	/// @brief The mutex for this object.
	mutable std::mutex mutex_;

	/// @brief Has this object been finalized?
	std::atomic_bool finalized_;

	/// @brief The API definition for this object.  Nullptr if not yet accessed.
	masala::base::api::MasalaObjectAPIDefinitionCSP api_definition_;

	/// @brief The minimum number of connections.
	masala::base::Size min_connections_ = 0;

	/// @brief The maximum number of connections.
	masala::base::Size max_connections_ = 0;

	/// @brief The offset.  (e.g. The number of hydrogen bonds satisfied to background or
	/// by internal connections.)
	masala::base::Size offset_ = 0;

	/// @brief Choices at other nodes that satisfy this feature, indexed
	/// by absolute node index, mapped to the number of connections that they
	/// make to this feature.
	/// @details Used during setup, then deleted at finalization time.
	std::unordered_map< std::pair< masala::base::Size, masala::base::Size >, masala::base::Size, masala::base::size_pair_hash > other_absolute_node_choices_that_satisfy_this_;

	/// @brief Choices at other nodes that satisfy this feature, indexed
	/// by variable node index, mapped to the number of connections that they
	/// make to this feature.
	/// @details Used run, after being produced by finalization step.
	std::unordered_map< std::pair< masala::base::Size, masala::base::Size >, masala::base::Size, masala::base::size_pair_hash > other_variable_node_choices_that_satisfy_this_;

}; // class ChoiceFeature

} // namespace feature_based
} // namespace cost_function
} // namespace cost_function_network
} // namespace optimization
} // namespace numeric
} // namespace masala

#endif // Masala_src_numeric_optimization_cost_function_network_cost_function_feature_based_ChoiceFeature_hh