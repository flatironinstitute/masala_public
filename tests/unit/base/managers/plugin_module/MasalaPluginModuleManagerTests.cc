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

/// @file tests/unit/base/managers/plugin_module/MasalaPluginModuleManagerTests.cc
/// @brief Unit tests for the Masala plugin module manager singleton.
/// @author Vikram K. Mulligan (vmulligan@flatironinstitute.org).

// Unit testing library (Catch2) headers:
#include <external/catch2/single_include/catch2/catch.hpp>

// Unit headers:
#include <base/managers/plugin_module/MasalaPluginModuleManager.hh>
#include <base/managers/plugin_module/MasalaPlugin.hh>
#include <base/managers/plugin_module/MasalaPluginAPI.hh>
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

    std::string class_name() const override { return class_name_static(); }
    std::string class_namespace() const override { return class_namespace_static(); }

    std::vector< std::string > get_keywords() const override {
        return std::vector< std::string > {
            "protein", "design", "canonical"
        };
    }

    std::vector< std::vector< std::string > > get_categories() const override {
        return std::vector< std::vector< std::string > > {
            { "first_dummy_category", "first_dummy_subcategory", "first_dummy_subsubcategory" },
            { "second_dummy_category", "second_dummy_subcategory", "second_dummy_subsubcategory" },
        };
    }

    void store_word( std::string const & word_in ) { word_ = word_in; }
    std::string const & word() const { return word_; }

private:

    std::string word_;

};

/// @brief Dummy API class for testing.
class DummyPlugin1API : public ::masala::base::managers::plugin_module::MasalaPluginAPI {

public:

    DummyPlugin1API() :
        ::masala::base::managers::plugin_module::MasalaPluginAPI(),
        inner_object_( masala::make_shared< DummyPlugin1 >() )
    {}

    static std::string class_name_static() { return "DummyPlugin1API"; }
    static std::string class_namespace_static() { return "masala::tests::unit::base::managers::plugin_module"; }

    std::string class_name() const override { return class_name_static(); }
    std::string class_namespace() const override { return class_namespace_static(); }
    std::string inner_class_name() const override { return DummyPlugin1::class_name_static(); }
    std::string inner_class_namespace() const override { return DummyPlugin1::class_namespace_static(); }

    void store_word( std::string const & word_in ) {
        inner_object_->store_word(word_in);
    }

    std::string const & word() const {
        return inner_object_->word();
    }

private:

    MASALA_SHARED_POINTER< DummyPlugin1 > inner_object_;

};

/// @brief Creator class for the dummy class.
class DummyPlugin1Creator : public ::masala::base::managers::plugin_module::MasalaPluginCreator {

public:

    ::masala::base::managers::plugin_module::MasalaPluginAPISP
    create_plugin_object() const override { return masala::make_shared< DummyPlugin1API >(); }

    std::vector< std::vector< std::string > >
    get_plugin_object_categories() const override {
        static std::vector< std::vector< std::string > > const categories {
            { "first_dummy_category", "first_dummy_subcategory", "first_dummy_subsubcategory" },
            { "second_dummy_category", "second_dummy_subcategory", "second_dummy_subsubcategory" }
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

    std::string class_name() const override { return class_name_static(); }
    std::string class_namespace() const override { return class_namespace_static(); }

    std::vector< std::string > get_keywords() const override {
        return std::vector< std::string > {
            "peptide", "design", "non-canonical"
        };
    }

    std::vector< std::vector< std::string > > get_categories() const override {
        return std::vector< std::vector< std::string > > {
            { "first_dummy_category", "first_dummy_subcategory", "first_dummy_subsubcategory" },
            { "second_dummy_category", "third_dummy_subcategory", "third_dummy_subsubcategory" },
        };
    }

};

/// @brief Dummy API class 2 for testing.
class DummyPlugin2API : public ::masala::base::managers::plugin_module::MasalaPluginAPI {

public:

    DummyPlugin2API() :
        ::masala::base::managers::plugin_module::MasalaPluginAPI(),
        inner_object_( masala::make_shared< DummyPlugin2 >() )
    {}

    static std::string class_name_static() { return "DummyPlugin2API"; }
    static std::string class_namespace_static() { return "masala::tests::unit::base::managers::plugin_module"; }

    std::string class_name() const override { return class_name_static(); }
    std::string class_namespace() const override { return class_namespace_static(); }
    std::string inner_class_name() const override { return DummyPlugin2::class_name_static(); }
    std::string inner_class_namespace() const override { return DummyPlugin2::class_namespace_static(); }

private:

    MASALA_SHARED_POINTER< DummyPlugin2 > inner_object_;

};

/// @brief Creator class for the dummy class.
class DummyPlugin2Creator : public ::masala::base::managers::plugin_module::MasalaPluginCreator {

public:

    ::masala::base::managers::plugin_module::MasalaPluginAPISP
    create_plugin_object() const override { return masala::make_shared< DummyPlugin2API >(); }

    std::vector< std::vector< std::string > >
    get_plugin_object_categories() const override {
        static std::vector< std::vector< std::string > > const categories {
            { "first_dummy_category", "first_dummy_subcategory", "first_dummy_subsubcategory" },
            { "second_dummy_category", "third_dummy_subcategory", "third_dummy_subsubcategory" }
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
        pm->add_plugin( masala::make_shared< DummyPlugin1Creator >() );
        pm->add_plugin( masala::make_shared< DummyPlugin2Creator >() );
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
        // Check that the plugins are sorted into categories correctly:
        std::vector< std::string > const protein_plugins( pm->get_list_of_plugins_by_keyword( "protein", false) );
        std::vector< std::string > const peptide_plugins( pm->get_list_of_plugins_by_keyword( "peptide", false ) );
        std::vector< std::string > const design_plugins( pm->get_list_of_plugins_by_keyword( "design", true ) );
        CHECK( protein_plugins.size() == 1 );
        CHECK( masala::base::utility::container::has_value( protein_plugins, "DummyPlugin1" ));
        CHECK( peptide_plugins.size() == 1 );
        CHECK( masala::base::utility::container::has_value( peptide_plugins, "DummyPlugin2" ));
        CHECK( design_plugins.size() == 2 );
        CHECK( masala::base::utility::container::has_value( design_plugins, "masala::tests::unit::base::managers::plugin_module::DummyPlugin1" ));
        CHECK( masala::base::utility::container::has_value( design_plugins, "masala::tests::unit::base::managers::plugin_module::DummyPlugin2" ));
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
