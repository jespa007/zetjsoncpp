// zetjsoncpp 3.0 regression test (C++11)
// Usage: test_jsonvar_v3 [optional-path-to-sample.json]
//
// This test targets the NEW ZJ_DEFINE_OBJECT schema syntax discussed for 3.0.
// The extensions below require the 2A JsonSchema.h macros ZJ_DECL_FIELD_I,
// ZJ_VISIT_FIELD_I, and ZJ_FOR_EACH to be available via zetjsoncpp.h.
// If JsonSchema.h is not included by zetjsoncpp.h yet, include it below.

#include "zetjsoncpp.h"

#include <cassert>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

// ---------------------------------------------------------------------------
// Schemas. Exactly seven fields in SampleJson (fits the initial 8-field
// ZJ_FOR_EACH implementation).
// ---------------------------------------------------------------------------
ZJ_DEFINE_OBJECT(Indent,
    ZJ_NUMBER(length),
    ZJ_BOOLEAN(use_space)
);

ZJ_DEFINE_OBJECT(Language,
    ZJ_STRING(code),
    ZJ_MAP_STRING(general_texts)
);

ZJ_DEFINE_OBJECT(Interpolation,
    ZJ_STRING(type),
    ZJ_STRING(channels),
    ZJ_ARRAY_NUMBER(data)
);

ZJ_DEFINE_OBJECT(SampleJson,
    ZJ_STRING(encoding),
    ZJ_NUMBER(number),
    ZJ_ARRAY_STRING_NAMED(plugins, "plug-ins"),
    ZJ_OBJECT(Indent, indent),
    ZJ_ARRAY_OBJECT(Language, languages),
    ZJ_MAP_OBJECT(Interpolation, interpolations),
    ZJ_MAP_ARRAY_STRING(map_array_strings)
);

ZJ_DEFINE_OBJECT(PrimitiveContainers,
    ZJ_ARRAY_BOOLEAN(flags),
    ZJ_ARRAY_NUMBER(numbers),
    ZJ_MAP_BOOLEAN(enabled),
    ZJ_MAP_NUMBER(counters)
);

// The main fixture retains the "plug-ins" key (hyphen cannot appear in a
// C++ identifier), and includes UTF-8 and dotted map keys.
static const char *sample_json = u8R"JSON(
{
  "encoding":"UTF-8",
  "number":3.34E-5,
  "plug-ins":["python","c++","ruby"],
  "indent":{"length":3,"use_space":true},
  "languages":[
    {"code":"en","general_texts":{"general.hello_word":"Hello world!","general.yes":"Yes","general.no":"No"}},
    {"code":"es","general_texts":{"general.hello_word":"Hola mundo!","general.yes":"Si","general.no":"No"}},
    {"code":"zh-CN","general_texts":{"general.hello_word":"你好词","general.yes":"是","general.no":"没有"}}
  ],
  "interpolations":{
    "id_1":{"type":"material","channels":"rgb","data":[0.0,1.0,0.0,1000,0.0,0.0,0.0,0]},
    "id_2":{"type":"transform","channels":"xyz","data":[0.0,1.0,0.0,1000,0.0,0.0,0.0,0]}
  },
  "map_array_strings":{
    "map_array_strings_1":["hello1","world1","!!"],
    "map_array_strings_2":["hello2","world2","!!"]
  }
}
)JSON";

#define CHECK(expr) do { \
    if(!(expr)) { \
        throw std::runtime_error(std::string("CHECK failed: ") + #expr \
            + " at line " + std::to_string(__LINE__)); \
    } \
} while(false)

static bool closeEnough(double a, double b, double eps = 1e-7) {
    return std::fabs(a-b) < eps;
}

template<typename T>
static void checkInitialData(const T &doc) {
    CHECK(doc.encoding.getValue() == "UTF-8");
    CHECK(closeEnough(doc.number.getValue(), 3.34e-5));
    CHECK(doc.plugins.size() == 3);
    CHECK(doc.plugins[0].getValue() == "python");
    CHECK(doc.plugins[1].getValue() == "c++");
    CHECK(doc.plugins[2].getValue() == "ruby");
    CHECK(closeEnough(doc.indent.length.getValue(), 3.0));
    CHECK(doc.indent.use_space.getValue());
    CHECK(doc.languages.size() == 3);
    CHECK(doc.languages[0]->code.getValue() == "en");
    CHECK(doc.languages[1]->code.getValue() == "es");
    CHECK(doc.languages[2]->code.getValue() == "zh-CN");
    CHECK(doc.languages[2]->general_texts["general.hello_word"].getValue() == u8"你好词");
    CHECK(doc.languages[2]->general_texts["general.yes"].getValue() == u8"是");
    CHECK(doc.interpolations.size() == 2);
    CHECK(doc.interpolations["id_1"]->type.getValue() == "material");
    CHECK(doc.interpolations["id_2"]->channels.getValue() == "xyz");
    CHECK(doc.interpolations["id_1"]->data.size() == 8);
    CHECK(closeEnough(doc.interpolations["id_1"]->data[3].getValue(), 1000.0));
    CHECK(doc.map_array_strings.size() == 2);
    CHECK(doc.map_array_strings["map_array_strings_1"].size() == 3);
    CHECK(doc.map_array_strings["map_array_strings_2"][1].getValue() == "world2");
    CHECK(doc.encoding.isDeserialized());
    CHECK(doc.indent.isDeserialized());
    CHECK(doc.languages.isDeserialized());
}

static void testReadAndRoundTrip() {
    std::cout << "[1] read and round trip\n";
    auto doc = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(sample_json);
    checkInitialData(*doc);

    const std::string compact = zetjsoncpp::serialize(doc, true, false);
    auto again = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(compact);
    checkInitialData(*again);

    const std::string formatted = zetjsoncpp::serialize(doc, false, false);
    auto pretty_again = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(formatted);
    checkInitialData(*pretty_again);
    CHECK(compact.find("\"plug-ins\"") != std::string::npos);
}

static void testIteratorsAndMutations() {
    std::cout << "[2] iterators and mutations\n";
    auto doc = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(sample_json);

    // std::vector-like array traversal; iterators expose StringJsonVar objects.
    std::size_t plugin_count = 0;
    for(auto it = doc->plugins.begin(); it != doc->plugins.end(); ++it) {
        CHECK(!it->getValue().empty());
        it->setValue("plugin_" + std::to_string(++plugin_count));
    }
    CHECK(plugin_count == 3);
    CHECK(doc->plugins[0].getValue() == "plugin_1");
    doc->plugins.newJsonVar();
    doc->plugins[doc->plugins.size()-1].setValue("plugin_4");
    CHECK(doc->plugins.size() == 4);
    doc->plugins.erase(1);
    CHECK(doc->plugins.size() == 3);
    CHECK(doc->plugins[1].getValue() == "plugin_3");

    // Array of objects: *iterator is an ObjectJsonVar<Language>* in 2.x.
    std::size_t language_count = 0;
    for(auto it = doc->languages.begin(); it != doc->languages.end(); ++it) {
        CHECK(*it != nullptr);
        CHECK(!(*it)->code.getValue().empty());
        ++language_count;
    }
    CHECK(language_count == 3);
    CHECK(doc->languages[1]->general_texts.count("general.yes") == 1);

    // Map of strings: key and JSON-wrapped value.
    std::size_t text_count = 0;
    for(auto it = doc->languages[0]->general_texts.begin();
        it != doc->languages[0]->general_texts.end(); ++it) {
        CHECK(!it->first.empty());
        CHECK(!it->second.getValue().empty());
        ++text_count;
    }
    CHECK(text_count == 3);
    doc->languages[0]->general_texts["general.yes"].setValue("Absolutely");
    CHECK(doc->languages[0]->general_texts["general.yes"].getValue() == "Absolutely");

    // Map of objects: mapped values are pointers in the older container API.
    std::size_t interpolation_count = 0;
    for(auto it = doc->interpolations.begin(); it != doc->interpolations.end(); ++it) {
        CHECK(it->second != nullptr);
        CHECK(it->second->data.size() == 8);
        std::size_t n = 0;
        for(auto n_it = it->second->data.begin(); n_it != it->second->data.end(); ++n_it) {
            n_it->setValue(static_cast<double>(n++));
        }
        ++interpolation_count;
    }
    CHECK(interpolation_count == 2);
    CHECK(closeEnough(doc->interpolations["id_2"]->data[7].getValue(), 7.0));

    // Map of arrays: mapped values are ArrayStringJsonVar objects.
    std::size_t map_array_count = 0;
    for(auto it = doc->map_array_strings.begin(); it != doc->map_array_strings.end(); ++it) {
        CHECK(it->second.size() == 3);
        for(auto str_it = it->second.begin(); str_it != it->second.end(); ++str_it) {
            str_it->setValue("changed_" + std::to_string(map_array_count));
        }
        ++map_array_count;
    }
    CHECK(map_array_count == 2);
    CHECK(doc->map_array_strings["map_array_strings_1"][0].getValue() == "changed_0");

    // Mutated object still serializes and deserializes correctly.
    doc->indent.use_space.setValue(false);
    auto again = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(
        zetjsoncpp::serialize(doc, true, false));
    CHECK(!again->indent.use_space.getValue());
    CHECK(again->plugins.size() == 3);
    CHECK(again->languages[0]->general_texts["general.yes"].getValue() == "Absolutely");
}

static void testContainerOperations() {
    std::cout << "[3] container operations\n";
    auto doc = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(sample_json);

    // Remove one object and one map entry: important ownership/destructor paths.
    doc->languages.erase(1);
    CHECK(doc->languages.size() == 2);
    CHECK(doc->languages[1]->code.getValue() == "zh-CN");
    doc->interpolations.erase("id_1");
    CHECK(doc->interpolations.size() == 1);
    CHECK(doc->interpolations.count("id_1") == 0);

    // Clear pointer-owning containers as well as nested map/array containers.
    doc->languages.clear();
    doc->interpolations.clear();
    doc->plugins.clear();
    doc->map_array_strings.clear();
    CHECK(doc->languages.size() == 0);
    CHECK(doc->interpolations.size() == 0);
    CHECK(doc->plugins.size() == 0);
    CHECK(doc->map_array_strings.size() == 0);

    auto roundtrip = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<SampleJson>>(
        zetjsoncpp::serialize(doc, true, false));
    CHECK(roundtrip->languages.size() == 0);
    CHECK(roundtrip->interpolations.size() == 0);
}

static void testOtherPrimitiveContainers() {
    std::cout << "[4] boolean/number array and map\n";
    const char *json = "{\"flags\":[true,false,true],\"numbers\":[1,2,-3.5],"
                       "\"enabled\":{\"a\":true,\"b\":false},"
                       "\"counters\":{\"x\":10,\"y\":20}}";
    auto doc = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<PrimitiveContainers>>(json);
    CHECK(doc->flags.size() == 3);
    CHECK(doc->numbers.size() == 3);
    CHECK(doc->enabled.size() == 2);
    CHECK(doc->counters.size() == 2);
    CHECK(doc->flags[0].getValue());
    CHECK(!doc->flags[1].getValue());
    CHECK(closeEnough(doc->numbers[2].getValue(), -3.5));
    CHECK(doc->enabled["a"].getValue());
    CHECK(closeEnough(doc->counters["y"].getValue(), 20));

    std::size_t count = 0;
    for(auto it = doc->flags.begin(); it != doc->flags.end(); ++it) {
        it->setValue(true);
        ++count;
    }
    CHECK(count == 3);
    for(auto it = doc->counters.begin(); it != doc->counters.end(); ++it) {
        it->second.setValue(it->second.getValue() + 1);
    }
    doc->numbers.newJsonVar();
    doc->numbers[doc->numbers.size()-1].setValue(0.0f);
    CHECK(doc->numbers.size() == 4);

    auto again = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<PrimitiveContainers>>(
        zetjsoncpp::serialize(doc, true, false));
    CHECK(again->flags[1].getValue());
    CHECK(closeEnough(again->counters["x"].getValue(), 11));
}

static void testErrors() {
    std::cout << "[5] duplicate/unknown/invalid properties\n";
    bool duplicate_threw = false;
    try {
        zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<Indent>>(
            "{\"length\":1,\"length\":2}");
    } catch(const std::exception &) {
        duplicate_threw = true;
    }
    CHECK(duplicate_threw);

    auto with_unknown = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<Indent>>(
        "{\"length\":3,\"unknown\":9,\"use_space\":true}");
    CHECK(closeEnough(with_unknown->length.getValue(), 3));
    CHECK(with_unknown->use_space.getValue());

    bool invalid_threw = false;
    try {
        zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<Indent>>(
            "{\"length\":}");
    } catch(const std::exception &) {
        invalid_threw = true;
    }
    CHECK(invalid_threw);
}

// ---------------------------------------------------------------------------
// Standalone/root JSON values: no enclosing ZJ_DEFINE_OBJECT schema.
// These tests intentionally exercise deserialize<T>() for each concrete type.
// If a root type is currently unsupported, its test identifies the gap.
// ---------------------------------------------------------------------------
static void testRootPrimitives() {
    std::cout << "[7] root primitive values\n";

    auto text = zetjsoncpp::deserialize<zetjsoncpp::StringJsonVar>(
        "\"Hello \\u4e16\\u754c\"");
    CHECK(text->getValue() == u8"Hello 世界");

    auto number = zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar>("3.34E-5");
    CHECK(closeEnough(number->getValue(), 3.34e-5, 1e-14));

    auto negative = zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar>("-125.75");
    CHECK(closeEnough(negative->getValue(), -125.75));

    auto boolean_true = zetjsoncpp::deserialize<zetjsoncpp::BooleanJsonVar>("true");
    auto boolean_false = zetjsoncpp::deserialize<zetjsoncpp::BooleanJsonVar>("false");
    CHECK(boolean_true->getValue());
    CHECK(!boolean_false->getValue());

    auto text_again = zetjsoncpp::deserialize<zetjsoncpp::StringJsonVar>(
        zetjsoncpp::serialize(text, true, false));
    CHECK(text_again->getValue() == text->getValue());

    auto number_again = zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar>(
        zetjsoncpp::serialize(number, true, false));
    CHECK(closeEnough(number_again->getValue(), number->getValue(), 1e-14));
}

static void testRootArrays() {
    std::cout << "[8] root arrays\n";

    auto strings = zetjsoncpp::deserialize<zetjsoncpp::ArrayStringJsonVar>(
        "[\"alpha\",\"beta\",\"gamma\"]");
    CHECK(strings->size() == 3);
    CHECK((*strings)[1].getValue() == "beta");
    std::size_t n = 0;
    for(auto it = strings->begin(); it != strings->end(); ++it) {
        CHECK(!it->getValue().empty());
        ++n;
    }
    CHECK(n == 3);

    auto numbers = zetjsoncpp::deserialize<zetjsoncpp::ArrayNumberJsonVar>(
        "[0,-2.5,3.34E-5,1000]");
    CHECK(numbers->size() == 4);
    CHECK(closeEnough((*numbers)[1].getValue(), -2.5));
    CHECK(closeEnough((*numbers)[2].getValue(), 3.34e-5, 1e-14));

    auto booleans = zetjsoncpp::deserialize<zetjsoncpp::ArrayBooleanJsonVar>(
        "[true,false,true]");
    CHECK(booleans->size() == 3);
    CHECK((*booleans)[0].getValue());
    CHECK(!(*booleans)[1].getValue());

    auto empty = zetjsoncpp::deserialize<zetjsoncpp::ArrayStringJsonVar>("[]");
    CHECK(empty->size() == 0);

    auto strings_again = zetjsoncpp::deserialize<zetjsoncpp::ArrayStringJsonVar>(
        zetjsoncpp::serialize(strings, true, false));
    CHECK(strings_again->size() == 3);
    CHECK((*strings_again)[2].getValue() == "gamma");
}

static void testRootMaps() {
    std::cout << "[9] root maps\n";

    auto strings = zetjsoncpp::deserialize<zetjsoncpp::MapStringJsonVar>(
        "{\"hello\":\"world\",\"lang\":\"en\"}");
    CHECK(strings->size() == 2);
    CHECK((*strings)["hello"].getValue() == "world");

    auto numbers = zetjsoncpp::deserialize<zetjsoncpp::MapNumberJsonVar>(
        "{\"min\":-3.5,\"max\":9.25}");
    CHECK(numbers->size() == 2);
    CHECK(closeEnough((*numbers)["max"].getValue(), 9.25));

    auto booleans = zetjsoncpp::deserialize<zetjsoncpp::MapBooleanJsonVar>(
        "{\"enabled\":true,\"hidden\":false}");
    CHECK(booleans->size() == 2);
    CHECK((*booleans)["enabled"].getValue());
    CHECK(!(*booleans)["hidden"].getValue());

    auto empty = zetjsoncpp::deserialize<zetjsoncpp::MapStringJsonVar>("{}");
    CHECK(empty->size() == 0);

    auto strings_again = zetjsoncpp::deserialize<zetjsoncpp::MapStringJsonVar>(
        zetjsoncpp::serialize(strings, true, false));
    CHECK(strings_again->size() == 2);
    CHECK((*strings_again)["lang"].getValue() == "en");
}

static void testRootObjectContainers() {
    std::cout << "[10] root object containers\n";

    auto object = zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<Indent>>(
        "{\"length\":3,\"use_space\":true}");
    CHECK(closeEnough(object->length.getValue(), 3.0));
    CHECK(object->use_space.getValue());

    auto objects = zetjsoncpp::deserialize<zetjsoncpp::ArrayObjectJsonVar<Language>>(
        "[{\"code\":\"en\",\"general_texts\":{\"yes\":\"Yes\"}},"
        "{\"code\":\"es\",\"general_texts\":{\"yes\":\"Si\"}}]");
    CHECK(objects->size() == 2);
    CHECK((*objects)[0]->code.getValue() == "en");
    CHECK((*objects)[1]->general_texts["yes"].getValue() == "Si");

    auto object_map = zetjsoncpp::deserialize<zetjsoncpp::MapObjectJsonVar<Indent>>(
        "{\"first\":{\"length\":1,\"use_space\":true},"
        "\"second\":{\"length\":2,\"use_space\":false}}");
    CHECK(object_map->size() == 2);
    CHECK(closeEnough((*object_map)["first"]->length.getValue(), 1.0));
    CHECK(!(*object_map)["second"]->use_space.getValue());

    auto arrays_map = zetjsoncpp::deserialize<zetjsoncpp::MapArrayStringJsonVar>(
        "{\"one\":[\"a\",\"b\"],\"two\":[\"c\"]}");
    CHECK(arrays_map->size() == 2);
    CHECK((*arrays_map)["one"].size() == 2);
    CHECK((*arrays_map)["two"][0].getValue() == "c");

    auto objects_again = zetjsoncpp::deserialize<zetjsoncpp::ArrayObjectJsonVar<Language>>(
        zetjsoncpp::serialize(objects, true, false));
    CHECK(objects_again->size() == 2);
    CHECK((*objects_again)[1]->code.getValue() == "es");

    auto object_map_again = zetjsoncpp::deserialize<zetjsoncpp::MapObjectJsonVar<Indent>>(
        zetjsoncpp::serialize(object_map, true, false));
    CHECK(object_map_again->size() == 2);
    CHECK(!(*object_map_again)["second"]->use_space.getValue());

    auto arrays_map_again = zetjsoncpp::deserialize<zetjsoncpp::MapArrayStringJsonVar>(
        zetjsoncpp::serialize(arrays_map, true, false));
    CHECK((*arrays_map_again)["one"][1].getValue() == "b");
}

int main(int argc, char **argv) {
    try {
        std::cout << "zetjsoncpp 3.0 regression suite\n";
        testReadAndRoundTrip();
        testIteratorsAndMutations();
        testContainerOperations();
        testOtherPrimitiveContainers();
        testErrors();
        testRootPrimitives();
        testRootArrays();
        testRootMaps();
        testRootObjectContainers();
        if(argc > 1) {
            std::cout << "[11] external JSON file\n";
            auto doc = zetjsoncpp::deserialize_file<zetjsoncpp::ObjectJsonVar<SampleJson>>(argv[1]);
            checkInitialData(*doc);
        }
        std::cout << "ALL TESTS PASSED\n";
        return 0;
    } catch(const std::exception &ex) {
        std::cerr << "TEST FAILURE: " << ex.what() << '\n';
        return 1;
    }
}
