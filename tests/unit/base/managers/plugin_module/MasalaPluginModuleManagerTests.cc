/*
MIT License

Copyright (c) 2022 Vikram K. Mulligan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/// @file tests/unit/base/masla/plugin_module/MasalaPluginModuleManagerTests.cc
/// @brief Unit tests for the Masala plugin module manager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>
#include <base/managers/plugin_module/MasalaPlugin.hh>
#include <base/managers/plugin_module/MasalaPluginCreator.hh>

// Base headers:
#include <base/types.hh>
#include <base/managers/tracer/MasalaTracerManager.hh>
#include <base/utility/container/container_util.tmpl.hh>

// STL headers:
#include <vector>

namespace masala {
namespace tests {
namespace unit {
namespace base {
namespace managers {
namespace plugin_module {

/// @brief Dummy class for testing.
class DummyPlugin1 : public ::masala::base::managers::plugin_module::MasalaPlugin {

public:

    static std::string class_name_static() { return "DummyPlugin1"; }
    static std::string class_namespace_static() { return "masala::tests::unit::base::managers::plugin_module"; }

    std::string class_name() const { return class_name_static(); }
    std::string class_namespace() const { return class_namespace_static(); }

};

/// @brief Creator class for the dummy class.
class DummyPlugin1Creator : public ::masala::base::managers::plugin_module::MasalaPluginCreator {

public:

    ::masala::base::managers::plugin_module::MasalaPluginSP
    create_plugin_object() const override { return std::make_shared< DummyPlugin1 >(); }

    std::vector< std::vector< std::string > >
    get_plugin_object_categories() const override {
        static std::vector< std::vector< std::string > > const categories {
            { "first_dummy_category", "first_dummy_subcategory", "first_dummy_subsubcategory" },
            { "second_dummy_category", "second_dummy_subcategory", "second_dummy_subsubcategory" },
        };
        return categories;
    }

    std::vector< std::string >
    get_plugin_object_keywords() const override {
        static std::vector< std::string > const keywords {
            "protein", "design", "canonical"
        };
        return keywords;
    }

    std::string get_plugin_object_name() const override { return DummyPlugin1::class_name_static(); }

    std::string get_plugin_object_namespace() const override { return DummyPlugin1::class_namespace_static(); }

    std::string class_name() const override { return "DummyPlugin1Creator"; }
    std::string class_namespace() const override { return "masala::tests::unit::base::managers::plugin_module"; }

};

/// @brief Another dummy class for testing.
class DummyPlugin2 : public ::masala::base::managers::plugin_module::MasalaPlugin {

public:

    static std::string class_name_static() { return "DummyPlugin2"; }
    static std::string class_namespace_static() { return "masala::tests::unit::base::managers::plugin_module"; }

    std::string class_name() const { return class_name_static(); }
    std::string class_namespace() const { return class_namespace_static(); }

};

/// @brief Creator class for the dummy class.
class DummyPlugin2Creator : public ::masala::base::managers::plugin_module::MasalaPluginCreator {

public:

    ::masala::base::managers::plugin_module::MasalaPluginSP
    create_plugin_object() const override { return std::make_shared< DummyPlugin2 >(); }

    std::vector< std::vector< std::string > >
    get_plugin_object_categories() const override {
        static std::vector< std::vector< std::string > > const categories {
            { "first_dummy_category", "first_dummy_subcategory", "first_dummy_subsubcategory" },
            { "second_dummy_category", "third_dummy_subcategory", "third_dummy_subsubcategory" },
        };
        return categories;
    }

    std::vector< std::string >
    get_plugin_object_keywords() const override {
        static std::vector< std::string > const keywords {
            "peptide", "design", "non-canonical"
        };
        return keywords;
    }

    std::string get_plugin_object_name() const override { return DummyPlugin2::class_name_static(); }

    std::string get_plugin_object_namespace() const override { return DummyPlugin2::class_namespace_static(); }

    std::string class_name() const override { return "DummyPlugin2Creator"; }
    std::string class_namespace() const override { return "masala::tests::unit::base::managers::plugin_module"; }

};

TEST_CASE( "Register and unregister two plugins", "[base::managers::plugin_manager::MasalaPluginModuleManager][plugins][registration][unregistration]" ) {

    masala::base::managers::plugin_module::MasalaPluginModuleManagerHandle pm(  masala::base::managers::plugin_module::MasalaPluginModuleManager::get_instance() );
    REQUIRE_NOTHROW([&](){
        pm->add_plugin( std::make_shared< DummyPlugin1Creator >() );
        pm->add_plugin( std::make_shared< DummyPlugin2Creator >() );
    }() );

    CHECK( pm->total_plugins() == 2 );

    std::vector< std::string > const all_keywords( pm->get_all_keywords() );
    CHECK( all_keywords.size() == 5 );
    CHECK( masala::base::utility::container::has_value( all_keywords, "protein" ) );
    CHECK( masala::base::utility::container::has_value( all_keywords, "design" ) );
    CHECK( masala::base::utility::container::has_value( all_keywords, "canonical" ) );
    CHECK( masala::base::utility::container::has_value( all_keywords, "peptide" ) );
    CHECK( masala::base::utility::container::has_value( all_keywords, "non-canonical" ) );

    {
        std::vector< std::string > const protein_plugins( pm->get_list_of_plugins_by_keyword( "protein", false) );
        std::vector< std::string > const peptide_plugins( pm->get_list_of_plugins_by_keyword( "peptide", false ) );
        std::vector< std::string > const design_plugins( pm->get_list_of_plugins_by_keyword( "design", false ) );
        CHECK( protein_plugins.size() == 1 );
        CHECK( masala::base::utility::container::has_value( protein_plugins, "DummyPlugin1" ));
        CHECK( peptide_plugins.size() == 1 );
        CHECK( masala::base::utility::container::has_value( peptide_plugins, "DummyPlugin2" ));
        CHECK( design_plugins.size() == 2 );
        CHECK( masala::base::utility::container::has_value( design_plugins, "DummyPlugin1" ));
        CHECK( masala::base::utility::container::has_value( design_plugins, "DummyPlugin2" ));
    }

    REQUIRE_NOTHROW([&](){
        pm->reset();
    }() );

}


} // namespace plugin_module
} // namespace managers
} // namespace base
} // namespace unit
} // namespace tests
} // namespace masala
