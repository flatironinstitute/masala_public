<__COMMENTED_LICENCE__>

<__DOXYGEN_FILE_PATH_AND_CC_FILE_NAME__>
<__DOXYGEN_BRIEF_DESCRIPTION__>
<__DOXYGEN_AUTHOR_AND_EMAIL__>
/// @note This file is an auto-generated API file.  Do not edit it.  Changes will
/// be lost on next build from source.

// Unit header:
<__REGISTER_PLUGINS_HH_FILE_INCLUDE_>

// Base headers:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>

// Plugin creator headers:
<__PLUGIN_CREATOR_HH_FILES_INCLUDES__>

// STL headers:
#include <vector>

<__CPP_NAMESPACE__>

/// @brief Register all of the plugins in the <__LIBNAME__> library.
void
register_<__LIBNAME__>() {
    using namespace masala::base::managers::plugin_module;
    MasalaPluginModuleManagerHandle pm( MasalaPluginModuleManager::get_instance() );

    pm->add_plugins(
        std::vector< MasalaPluginCreatorCSP >{
            <__PLUGIN_CREATORS_FOR_REGISTRATION__>
        }
    );
}

/// @brief Unregister all of the plugins in the <__LIBNAME__> library.
void
unregister_<__LIBNAME__>() {
    using namespace masala::base::managers::plugin_module;
    MasalaPluginModuleManagerHandle pm( MasalaPluginModuleManager::get_instance() );

    pm->remove_plugins(
        std::vector< MasalaPluginCreatorCSP >{
            <__PLUGIN_CREATORS_FOR_REGISTRATION__>
        }
    );
}

<__CPP_END_NAMESPACE__>
