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

/// @file src/base/managers/engine/MasalaDataRepresentationManager.hh
/// @brief A static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

#ifndef Masala_src_base_managers_engine_MasalaDataRepresentationManager_hh
#define Masala_src_base_managers_engine_MasalaDataRepresentationManager_hh

// Parent header:
#include <base/MasalaObject.hh>

// Forward declarations:
#include <base/managers/engine/MasalaDataRepresentationManager.fwd.hh>

// Base headers:
#include <base/managers/engine/MasalaDataRepresentationAPI.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationCreator.fwd.hh>
#include <base/managers/engine/MasalaDataRepresentationRequest.fwd.hh>
#include <base/managers/engine/MasalaEngine.fwd.hh>

// STL headers:
#include <map>
#include <mutex>
#include <string>

namespace masala {
namespace base {
namespace managers {
namespace engine {

/// @brief The ways in which a request for a data representation might be satisfied.
enum class MasalaDataRepresentationRequestResult {
    UNKNOWN_RESULT_TYPE = 0, // Keep first
    REQUEST_RETURNED_NO_RESULTS = 1, // Keep second
    REQUEST_RETURNED_PREFERRED_TYPES_COMPATIBLE_WITH_ENGINE,
    REQUEST_RETURNED_PREFERRED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE,
    REQUEST_RETURNED_TYPES_COMPATIBLE_WITH_ENGINE,
    REQUEST_RETURNED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE, // Keep second-to-last
    N_RETURN_POSSIBILITIES = REQUEST_RETURNED_TYPES_NOT_INCOMPATIBLE_WITH_ENGINE
};

/// @brief A static singleton for managing available data representaitons.
/// @details Modules may register and retrieve data representations by unique keystring.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).
class MasalaDataRepresentationManager : public masala::base::MasalaObject {

public:

    /// @brief Instantiate the static singleton and get a handle to it.
    static MasalaDataRepresentationManagerHandle get_instance();

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE CONSTRUCTOR
////////////////////////////////////////////////////////////////////////////////

    /// @brief Private constructor: object can only be instantiated with getInstance().
    MasalaDataRepresentationManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC CONSTRUCTORS AND DESTRUCTORS
////////////////////////////////////////////////////////////////////////////////

    /// @brief No copy constructor.
    MasalaDataRepresentationManager( MasalaDataRepresentationManager const & ) = delete;

    /// @brief No assignment operator.
    void operator=( MasalaDataRepresentationManager const & ) = delete;

    /// @brief Default destructor.
    ~MasalaDataRepresentationManager() = default;

public:

////////////////////////////////////////////////////////////////////////////////
// PUBLIC MEMBER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Get the name of this object.
    /// @details Returns "MasalaDataRepresentationManager".
    std::string
    class_name() const override;

    /// @brief Get the namespace of this object.
    /// @details Returns "masala::base::managers::engine".
    std::string
    class_namespace() const override;

    /// @brief Create a data representation, by name.
    /// @details If throw_if_missing is true, this function will throw an exception if it can't
    /// find a data representation creator for the specified data representation type.  Otherwise, it will return nullptr.
    MasalaDataRepresentationAPISP
    create_data_representation(
        std::string const & data_representation_type,
        bool const throw_if_missing = true
    ) const;

    /// @brief Register a data representation.
    /// @details An exception is thrown if the data representation name is already registered.
    void
    register_data_representation(
        MasalaDataRepresentationCreatorCSP const & data_representation_creator
    );

    /// @brief Unregister a data representation.
    /// @details Throws if the data representation has not been registered.
    void
    unregister_data_representation(
        MasalaDataRepresentationCreatorCSP const & data_representation_creator
    );

    /// @brief Register a set of data representations.
    /// @details An exception is thrown if a data representation name is already registered.
    void
    register_data_representations(
        std::vector< MasalaDataRepresentationCreatorCSP > const & data_representation_creators
    );

    /// @brief Unregister a set of data representations.
    /// @details Throws if a data representation has not been registered.
    void
    unregister_data_representations(
        std::vector< MasalaDataRepresentationCreatorCSP > const & data_representation_creators
    );

    /// @brief Get the data representations compatible with a set of criteria encoded in a request object.
    std::vector< MasalaDataRepresentationCreatorCSP >
    get_compatible_data_representation_creators(
        MasalaDataRepresentationRequest const & request
    ) const;

    /// @brief Convenience function to get data representations from a given category or set of categories that:
    /// (a) are explicitly compatible with a given engine.
    /// (b) are not explicitly incompatible with a given engine if (a) is not satisfied.
    /// @details Under the hood, this is handled by series of requests.
    /// @param[in] categories The categories from which our data representations will be drawn.
    /// @param[in] allow_subcategories If true, then data representations must be from at least one subcategory of at least one listed category.
    /// @param[in] engine The engine with which we expect our data representations to be compatible, or, failing that, not incompatible.
    /// @param[out] result_type The type of result.  For instance, did successfully match a preferred type?  Did we explicitly match the engine?
    std::vector< MasalaDataRepresentationCreatorCSP >
    get_data_representation_creators_for_engine(
        std::vector< std::vector< std::string > > const & categories,
        bool const allow_subcategories,
        MasalaEngine const & engine,
        MasalaDataRepresentationRequestResult & result_type
    ) const;

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
    get_data_representation_creators_for_engine_with_preferred(
        std::vector< std::vector< std::string > > const & categories,
        bool const allow_subcategories,
        MasalaEngine const & engine,
        std::vector< std::string > const & preferred_representations,
        MasalaDataRepresentationRequestResult & result_type
    ) const;

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////

    /// @brief Register a data representation.  Must be called from a mutex-locked context.
    /// @details An exception is thrown if the data representation name is already registered.
    void
    register_data_representation_mutex_locked(
        MasalaDataRepresentationCreatorCSP const & data_representation_creator
    );

    /// @brief Unegister a data representation.  Must be called from a mutex-locked context.
    /// @details Throws if the data representation has not been registered.
    void
    unregister_data_representation_mutex_locked(
        MasalaDataRepresentationCreatorCSP const & data_representation_creator
    );

private:

////////////////////////////////////////////////////////////////////////////////
// PRIVATE MEMBER VARIABLES
////////////////////////////////////////////////////////////////////////////////

    /// @brief A mutex to lock this object.
    mutable std::mutex masala_data_representation_manager_mutex_;

    /// @brief A map of string to data representation creator.
    std::map< std::string, MasalaDataRepresentationCreatorCSP > data_representation_creators_;

};

} // namespace engine
} // namespace managers
} // namespace base
} // namespace masala

#endif // Masala_src_base_managers_engine_MasalaDataRepresentationManager_hh