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

/// @file src/base/managers/engine/MasalaDataRepresentationManager.cc
/// @brief A static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Project header:
#include <base/managers/engine/MasalaDataRepresentationManager.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationAPI.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.hh>
#include <base/managers/engine/MasalaDataRepresentationRequest.hh>
#include <base/managers/engine/MasalaEngine.hh>
#include <base/error/ErrorHandling.hh>
#include <base/utility/string/string_comparison.hh>
#include <base/utility/string/string_manipulation.hh>
#include <base/utility/container/container_util.tmpl.hh>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief Instantiate the static singleton and get a handle to it.
MasalaDataRepresentationManagerHandle
MasalaDataRepresentationManager::get_instance() {
    static MasalaDataRepresentationManager config_manager;
    return &config_manager;
}

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Get the name of this object.
/// @details Returns "MasalaDataRepresentationManager".
std::string
MasalaDataRepresentationManager::class_name() const {
    return "MasalaDataRepresentationManager";
}

/// @brief Get the namespace of this object.
/// @details Returns "masala::base::managers::engine".
std::string
MasalaDataRepresentationManager::class_namespace() const {
    return "masala::base::managers::engine";
}

/// @brief Create a data representation, by name.
/// @details If throw_if_missing is true, this function will throw an exception if it can't
/// find an data representation creator for the specified data representation type.  Otherwise,
/// it will return nullptr.
MasalaDataRepresentationAPISP
MasalaDataRepresentationManager::create_data_representation(
	std::string const & data_representation_type,
	bool const throw_if_missing /*= true*/
) const {
	std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
	std::map< std::string, MasalaDataRepresentationCreatorCSP >::const_iterator it( data_representation_creators_.find(data_representation_type) );
	if( it == data_representation_creators_.end() ) {
		if( throw_if_missing ) {
			MASALA_THROW( class_namespace_and_name(), "create_data_representation", "Could not find data representation \"" + data_representation_type + "\".  Has it been registered?" );
		} else {
			return nullptr;
		}
	}
	return it->second->create_data_representation();
}

/// @brief Create a data representation, by short name.
/// @details If throw_if_missing is true, this function will throw an exception if it can't
/// find a data representation creator for the specified data representation type.  Otherwise, it will return nullptr.
MasalaDataRepresentationAPISP
MasalaDataRepresentationManager::create_data_representation_by_short_name(
	std::string const & data_representation_type_by_short_name,
	bool const throw_if_missing /*= true*/
) const {
	std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
	std::map< std::string, MasalaDataRepresentationCreatorCSP >::const_iterator it( data_representation_creators_.begin() );
	for( ; it != data_representation_creators_.end(); ++it ) {
		std::string const shortname( masala::base::utility::string::short_masala_class_name_from_full_name( it->first ) );
		if( shortname == data_representation_type_by_short_name ) { break; }
	}
	if( it == data_representation_creators_.end() ) {
		if( throw_if_missing ) {
			MASALA_THROW( class_namespace_and_name(), "create_data_representation_by_short_name", "Could not find data representation \"" + data_representation_type_by_short_name + "\".  Has it been registered?" );
		} else {
			return nullptr;
		}
	}
	return it->second->create_data_representation();
}

/// @brief Register a data representation.
/// @details An exception is thrown if the data representation name is already registered.
void
MasalaDataRepresentationManager::register_data_representation(
    MasalaDataRepresentationCreatorCSP const & data_representation_creator
) {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    register_data_representation_mutex_locked( data_representation_creator );
}

/// @brief Unregister a data representation.
/// @details Throws if the data representation has not been registered.
void
MasalaDataRepresentationManager::unregister_data_representation(
    MasalaDataRepresentationCreatorCSP const & data_representation_creator
) {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    unregister_data_representation_mutex_locked( data_representation_creator );
}

/// @brief Register a set of data representations.
/// @details An exception is thrown if a data representation name is already registered.
void
MasalaDataRepresentationManager::register_data_representations(
    std::vector< MasalaDataRepresentationCreatorCSP > const & data_representation_creators
) {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    for( auto const & creator : data_representation_creators ) {
        register_data_representation_mutex_locked( creator );
    }
}

/// @brief Unregister a set of data representations.
/// @details Throws if a data representation has not been registered.
void
MasalaDataRepresentationManager::unregister_data_representations(
    std::vector< MasalaDataRepresentationCreatorCSP > const & data_representation_creators
) {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    for( auto const & creator : data_representation_creators ) {
        unregister_data_representation_mutex_locked( creator );
    }
}

/// @brief Remove all data representations from the manager.
void
MasalaDataRepresentationManager::reset() {
    {
        std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
        data_representation_creators_.clear();
    }
    write_to_tracer( "Reset the MasalaDataRepresentationManager.  No data representations are registered." );
}

/// @brief Get the data representations compatible with a set of criteria encoded in a request object.
std::vector< MasalaDataRepresentationCreatorCSP >
MasalaDataRepresentationManager::get_compatible_data_representation_creators(
    MasalaDataRepresentationRequest const & request
) const {
    std::lock_guard< std::mutex > lock( masala_data_representation_manager_mutex_ );
    std::vector< MasalaDataRepresentationCreatorCSP > outvec;
    for( auto const & creator : data_representation_creators_ ) {
        if( request.data_representation_is_compatible_with_criteria( *(creator.second) ) ) {
            outvec.push_back( creator.second );
        }
    }
    outvec.shrink_to_fit();
    return outvec;
}

/// @brief Convenience function to get data representations from a given category or set of categories that:
/// (a) are explicitly compatible with a given engine.
/// (b) are not explicitly incompatible with a given engine if (a) is not satisfied.
/// @details Under the hood, this is handled by series of requests.
/// @param[in] categories The categories from which our data representations will be drawn.  Data representations must be from at least one
/// of the listed categories.
/// @param[in] allow_subcategories If true, then data representations must be from at least one subcategory of at least one listed category.
/// @param[in] engine The engine with which we expect our data representations to be compatible, or, failing that, not incompatible.
/// @param[out] result_type The type of result.  For instance, did successfully match a preferred type?  Did we explicitly match the engine?
std::vector< MasalaDataRepresentationCreatorCSP >
MasalaDataRepresentationManager::get_data_representation_creators_for_engine(
    std::vector< std::vector< std::string > > const & categories,
    bool const allow_subcategories,
    MasalaEngine const & engine,
    MasalaDataRepresentationRequestResult & result_type
) const {
    {
        MasalaDataRepresentationRequest request1;
        request1.add_engine_compatibility_requirement( engine.class_namespace_and_name() );
        request1.add_data_representation_category_requirement( categories, allow_subcategories );
        std::vector< MasalaDataRepresentationCreatorCSP > const creatorlist( get_compatible_data_representation_creators( request1 ) );
        if( !creatorlist.empty() ) {
            result_type = MasalaDataRepresentationRequestResult::REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE;
            return creatorlist;
        }
    }
    {
        MasalaDataRepresentationRequest request2;
        request2.add_data_representation_category_requirement( categories, allow_subcategories );
        std::vector< MasalaDataRepresentationCreatorCSP > creatorlist( get_compatible_data_representation_creators( request2 ) );

        // Erase data representations explicitly incompatible with engine:
        for(
			std::vector< MasalaDataRepresentationCreatorCSP >::iterator it( creatorlist.begin() );
			it != creatorlist.end();
			/*No increment*/
		) {
			if( engine.data_representation_is_incompatible_with_engine( **it ) ) {
                //write_to_tracer( "ERASING " + (**it).class_namespace_and_name() ); // DELETE ME
                it = creatorlist.erase( it );
			} else {
                //write_to_tracer( "KEEPING " + (**it).class_namespace_and_name() ); // DELETE ME
                ++it;
			}
		}

        if( !creatorlist.empty() ) {
            result_type = MasalaDataRepresentationRequestResult::REQUEST_RETURNED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE;
        } else {
            result_type = MasalaDataRepresentationRequestResult::REQUEST_RETURNED_NO_RESULTS;
        }
        return creatorlist;
    }
}

/// @brief Convenience function to get data representations from a given category or set of categories that:
/// (a) are preferably from a list of preferred representations (with the first in the list most preferred).
/// (b) are explicitly compatible with a given engine.
/// (c) are not explicitly incompatible with a given engine if (b) is not satisfied.
/// @details Under the hood, this is handled by series of requests.
/// @param[in] categories The categories from which our data representations will be drawn.
/// @param[in] allow_subcategories If true, then data representations must be from at least one subcategory of at least one listed category.
/// @param[in] engine The engine with which we expect our data representations to be compatible, or, failing that, not incompatible.
/// @param[in] preferred_representations The representations that we would prefer.
/// @param[out] result_type The type of result.  For instance, did successfully match a preferred type?  Did we explicitly match the engine?
std::vector< MasalaDataRepresentationCreatorCSP >
MasalaDataRepresentationManager::get_data_representation_creators_for_engine_with_preferred(
    std::vector< std::vector< std::string > > const & categories,
    bool const allow_subcategories,
    MasalaEngine const & engine,
    std::vector< std::string > const & preferred_representations,
    MasalaDataRepresentationRequestResult & result_type
) const {
    MasalaDataRepresentationRequestResult first_result_type( MasalaDataRepresentationRequestResult::UNKNOWN_RESULT_TYPE );
    std::vector< MasalaDataRepresentationCreatorCSP > creatorlist(
        get_data_representation_creators_for_engine( categories, allow_subcategories, engine, first_result_type )
    );
    CHECK_OR_THROW_FOR_CLASS( first_result_type != MasalaDataRepresentationRequestResult::UNKNOWN_RESULT_TYPE,
        "get_data_representation_creators_for_engine_with_preferred",
        "Initial attempt to get compatible data representations failed in an unexpected manner.  This is a program error.  Please consult a developer."
    );
    if( creatorlist.empty() || first_result_type == MasalaDataRepresentationRequestResult::REQUEST_RETURNED_NO_RESULTS ) {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( creatorlist.empty() && first_result_type == MasalaDataRepresentationRequestResult::REQUEST_RETURNED_NO_RESULTS,
            "get_data_representation_creators_for_engine_with_preferred",
            "Expected a 1:1 correspondence between creator list being empty and return type being REQUEST_RETURNED_NO_RESULTS, but this "
            "was not found to be the case!  Program error.  Please consult a developer."
        );
        result_type = MasalaDataRepresentationRequestResult::REQUEST_RETURNED_NO_RESULTS;
        return creatorlist;
    }

    // Get the subset of outputs that match the preferred list, if any:
    std::vector< MasalaDataRepresentationCreatorCSP > outlist;
    outlist.reserve( creatorlist.size() );
    //write_to_tracer( "Considering " + std::to_string( preferred_representations.size() ) + " preferred data representations." ); // DELETE ME
    for( auto const & preferred_representation : preferred_representations ) {
        //write_to_tracer( "Trying " + preferred_representation + "." ); // DELETE ME
        for( auto const & creator : creatorlist ) {
            //write_to_tracer( "\tComparing " + preferred_representation + "to" + creator->get_plugin_object_namespace_and_name() + "." ); // DELETE ME
            if( base::utility::string::masala_class_names_match( creator->get_plugin_object_namespace_and_name(), preferred_representation ) ) {
                //write_to_tracer( "\t\tNames match!" ); // DELETE ME
                if( !base::utility::container::has_value( outlist, creator ) ) {
                    //write_to_tracer( "\t\tAdding!" ); // DELETE ME
                    outlist.push_back( creator );
                }
            }
        }
    }

    DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS(
        first_result_type == MasalaDataRepresentationRequestResult::REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE ||
        first_result_type == MasalaDataRepresentationRequestResult::REQUEST_RETURNED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE,
        "get_data_representation_creators_for_engine_with_preferred",
        "Expected return type of REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE or REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE, but "
        "got something else!  This is a program error.  Please cosult a developer."
    )
    if( outlist.empty() ) {
        result_type = first_result_type;
        return creatorlist;
    }

    // If we get here, we had some outputs that matched the preferred list.
    if( first_result_type == MasalaDataRepresentationRequestResult::REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE ) {
        result_type = MasalaDataRepresentationRequestResult::REQUEST_RETURNED_PREFERRED_TYPES_COMPATIBLE_WITH_ENGINE;
    } else {
        DEBUG_MODE_CHECK_OR_THROW_FOR_CLASS( first_result_type == MasalaDataRepresentationRequestResult::REQUEST_RETURNED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE,
            "get_data_representation_creators_for_engine_with_preferred",
            "Something went wrong.  Expected REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE, but got something else!  This is a "
            "program error.  Please cosult a developer."
        );
        result_type = MasalaDataRepresentationRequestResult::REQUEST_RETURNED_PREFERRED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE;
    }
    return outlist;
}

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

/// @brief Register a data representation.  Must be called from a mutex-locked context.
/// @details An exception is thrown if the data representation name is already registered.
void
MasalaDataRepresentationManager::register_data_representation_mutex_locked(
    MasalaDataRepresentationCreatorCSP const & data_representation_creator
) {
    std::string const data_representation_name( data_representation_creator->get_plugin_object_namespace_and_name() );
    if( data_representation_creators_.find(data_representation_name) != data_representation_creators_.end() ) {
        MASALA_THROW( class_namespace_and_name(), "register_data_representation_mutex_locked",
            "MasalaDataRepresentation \"" + data_representation_name + "\" has already been registered!"
        );
    }
    write_to_tracer( "Registering " + data_representation_name + " with the MasalaDataRepresentationManager." );
    data_representation_creators_[data_representation_name] = data_representation_creator;
}

/// @brief Unegister a data representation.  Must be called from a mutex-locked context.
/// @details Throws if the data representation has not been registered.
void
MasalaDataRepresentationManager::unregister_data_representation_mutex_locked(
    MasalaDataRepresentationCreatorCSP const & data_representation_creator
) {
    std::string const data_representation_name( data_representation_creator->get_plugin_object_namespace_and_name() );
    std::map< std::string, MasalaDataRepresentationCreatorCSP >::const_iterator it( data_representation_creators_.find(data_representation_name) );
    if( it == data_representation_creators_.end() ) {
        MASALA_THROW( class_namespace_and_name(), "unregister_data_representation_mutex_locked",
            "No data representation was registered with name \"" + data_representation_name + "\"."
        );
    }
    write_to_tracer( "Unregistering " + data_representation_name + " from the MasalaDataRepresentationManager." );
    data_representation_creators_.erase(it);
}

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala
