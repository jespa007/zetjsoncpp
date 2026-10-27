# zetjsoncpp

**zetjsoncpp** is a C++11 library for deserializing JSON strings and files into strongly typed JSON variables and serializing those variables back to JSON.

Version **3.0.0** introduces a schema declaration API (`ZJ_DEFINE_OBJECT`) and automatic ownership of deserialized root values through `std::unique_ptr`.

## Supported JSON types

| JSON value | zetjsoncpp type |
| --- | --- |
| Boolean | `zetjsoncpp::BooleanJsonVar` |
| Number | `zetjsoncpp::NumberJsonVar` |
| String | `zetjsoncpp::StringJsonVar` |
| Array of booleans | `zetjsoncpp::ArrayBooleanJsonVar` |
| Array of numbers | `zetjsoncpp::ArrayNumberJsonVar` |
| Array of strings | `zetjsoncpp::ArrayStringJsonVar` |
| Map of booleans | `zetjsoncpp::MapBooleanJsonVar` |
| Map of numbers | `zetjsoncpp::MapNumberJsonVar` |
| Map of strings | `zetjsoncpp::MapStringJsonVar` |
| Map of arrays of strings | `zetjsoncpp::MapArrayStringJsonVar` |
| Typed object | `zetjsoncpp::ObjectJsonVar<T>` |
| Array of typed objects | `zetjsoncpp::ArrayObjectJsonVar<T>` |
| Map of typed objects | `zetjsoncpp::MapObjectJsonVar<T>` |

Arrays and maps listed here have *homogeneous* element/value types. A heterogeneous array such as `[0, true, "hello"]` is not covered by these typed containers.

## Getting started

Include the library header:

```cpp
#include "zetjsoncpp.h"
```

Deserialize a primitive JSON value:

```cpp
auto value = zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar>("3.34E-5");

double number = value->getValue();
value->setValue(2.5);

std::string json = zetjsoncpp::serialize(value);
```

`deserialize<T>()` and `deserialize_file<T>()` return `std::unique_ptr<T>`. The returned object is destroyed automatically when its owner goes out of scope. **Do not manually `delete` it.**

## Deserialization

### Primitive values

Each primitive JSON value can be deserialized directly, without wrapping it in a JSON object:

```cpp
// Boolean
auto enabled = zetjsoncpp::deserialize<zetjsoncpp::BooleanJsonVar>("true");
bool b = enabled->getValue();

// Number: NumberJsonVar stores double values in 3.0.0
// (check your installed version if numeric storage was customized).
auto length = zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar>("3.7e+2");
double n = length->getValue();

// String
// JSON strings must include their quotation marks.
auto text = zetjsoncpp::deserialize<zetjsoncpp::StringJsonVar>("\"my_string\"");
std::string s = text->getValue();
```

### Arrays

A typed JSON array can be deserialized as a root value:

```cpp
// [true, false, true]
auto flags = zetjsoncpp::deserialize<zetjsoncpp::ArrayBooleanJsonVar>(
    "[true,false,true]"
);

// [1, 3.7e+2, -3]
auto numbers = zetjsoncpp::deserialize<zetjsoncpp::ArrayNumberJsonVar>(
    "[1,3.7e+2,-3]"
);

// ["string_1", "string_2", "string_3"]
auto strings = zetjsoncpp::deserialize<zetjsoncpp::ArrayStringJsonVar>(
    "[\"string_1\",\"string_2\",\"string_3\"]"
);

strings->operator[](0).setValue("updated");

for(auto it = numbers->begin(); it != numbers->end(); ++it) {
    double value = it->getValue();
    // Use value...
}
```

### Maps

A *map* is a JSON object whose values all have a known type:

```cpp
// {"id1": true, "id2": false}
auto flags = zetjsoncpp::deserialize<zetjsoncpp::MapBooleanJsonVar>(
    "{\"id1\":true,\"id2\":false}"
);

// {"id1": 1, "id2": 3.7e+2}
auto numbers = zetjsoncpp::deserialize<zetjsoncpp::MapNumberJsonVar>(
    "{\"id1\":1,\"id2\":3.7e+2}"
);

// {"id1": "hello", "id2": "world"}
auto strings = zetjsoncpp::deserialize<zetjsoncpp::MapStringJsonVar>(
    "{\"id1\":\"hello\",\"id2\":\"world\"}"
);

strings->operator[]("id1").setValue("updated");

for(auto it = strings->begin(); it != strings->end(); ++it) {
    const std::string &key = it->first;
    const std::string &value = it->second.getValue();
    // Use key and value...
}
```

Maps of arrays of strings are supported too:

```cpp
auto groups = zetjsoncpp::deserialize<zetjsoncpp::MapArrayStringJsonVar>(
    "{\"id1\":[\"a\",\"b\"],\"id2\":[\"c\",\"d\"]}"
);

groups->operator[]("id1")[0].setValue("updated");
```

## Typed JSON objects: `ZJ_DEFINE_OBJECT`

Unlike the 2.4.4 API, zetjsoncpp 3.0.0 does not require `ZJ_CONST_CHAR` or manually laid-out fields that are discovered using pointer arithmetic.

Declare a schema with `ZJ_DEFINE_OBJECT`. Each field macro generates a typed C++ member and registers it for serialization/deserialization:

```cpp
ZJ_DEFINE_OBJECT(JsonSample,
    ZJ_STRING(encoding),
    ZJ_NUMBER(length),
    ZJ_BOOLEAN(use_space)
);
```

For this input:

```json
{
  "encoding": "UTF-8",
  "length": 1000,
  "use_space": false
}
```

Deserialize and access strongly typed fields:

```cpp
auto json_object = zetjsoncpp::deserialize<
    zetjsoncpp::ObjectJsonVar<JsonSample>
>("{\"encoding\":\"UTF-8\",\"length\":1000,\"use_space\":false}");

std::string encoding = json_object->encoding.getValue();
double length = json_object->length.getValue();
bool use_space = json_object->use_space.getValue();

json_object->use_space.setValue(true);

std::string output = zetjsoncpp::serialize(json_object);
```

### Field names and `_NAMED` fields

Normally, the JSON property name is inferred from the C++ field identifier:

```cpp
ZJ_STRING(encoding) // C++: encoding; JSON: "encoding"
```

When the JSON property name differs from the C++ member name, use the appropriate `_NAMED` field macro. For example, `ZJ_ARRAY_STRING_NAMED` is available in the 3.0 schema described here:

```cpp
ZJ_DEFINE_OBJECT(PluginSettings,
    ZJ_ARRAY_STRING_NAMED(plugins, "plug-ins")
);

// C++ member: settings->plugins
// JSON property: "plug-ins"
```

Do not replace this with `ZJ_ARRAY_STRING(plugins)` if your input uses `"plug-ins"`; those are different JSON keys. Additional `_NAMED` variants can be supported by extending `JsonSchema.h`.

### Nested objects

Schemas can contain other schemas:

```cpp
ZJ_DEFINE_OBJECT(Indent,
    ZJ_NUMBER(length),
    ZJ_BOOLEAN(use_space)
);

ZJ_DEFINE_OBJECT(Settings,
    ZJ_STRING(encoding),
    ZJ_OBJECT(Indent, indent)
);

auto settings = zetjsoncpp::deserialize<
    zetjsoncpp::ObjectJsonVar<Settings>
>("{\"encoding\":\"UTF-8\",\"indent\":{\"length\":3,\"use_space\":true}}");

settings->indent.use_space.setValue(false);
```

### Missing, unknown, and duplicate properties

Use `isDeserialized()` to check whether a registered field was present in the input:

```cpp
if(settings->encoding.isDeserialized()) {
    // The "encoding" property was read from the JSON input.
}
```

For primitive fields that have not been deserialized, the default values are an empty string, zero, and `false`, respectively. The existing parser skips unrecognized object properties and reports duplicate registered properties as errors.

## Arrays and maps of typed objects

Once a schema is declared, it can be used for an array or map of objects:

```cpp
ZJ_DEFINE_OBJECT(Language,
    ZJ_STRING(code),
    ZJ_MAP_STRING(general_texts)
);

// Array of Language objects
auto languages = zetjsoncpp::deserialize<
    zetjsoncpp::ArrayObjectJsonVar<Language>
>("[{\"code\":\"en\"},{\"code\":\"es\"}]");

std::string code = (*languages)[0]->code.getValue();

// Map of Language objects
auto language_map = zetjsoncpp::deserialize<
    zetjsoncpp::MapObjectJsonVar<Language>
>("{\"english\":{\"code\":\"en\"},\"spanish\":{\"code\":\"es\"}}");

std::string spanish_code = (*language_map)["spanish"]->code.getValue();
```

Object array and map elements are accessed through pointers in the current container API. The containers are responsible for cleaning up the elements they own; applications should not manually delete those elements.

## Serialization

Use `zetjsoncpp::serialize()` to convert a JSON variable back to text:

```cpp
auto value = zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar>("2");
value->setValue(3.5);

std::cout << zetjsoncpp::serialize(value) << std::endl;
// Output: 3.5
```

The `serialize()` overload also accepts a `std::unique_ptr` returned by deserialization. The regression-tested signature supports formatting options such as:

```cpp
std::string compact = zetjsoncpp::serialize(value, true, false);
std::string formatted = zetjsoncpp::serialize(value, false, false);
```

The first boolean selects minimized (compact) output; the second controls whether non-deserialized fields are discarded. Programmatic assignments do not necessarily change a field's `isDeserialized()` state.

## Complete example

Suppose `sample.json` contains:

```json
{
  "encoding": "UTF-8",
  "number": 3.34E-5,
  "plug-ins": ["python", "c++", "ruby"],
  "indent": { "length": 3, "use_space": true },
  "languages": [
    {"code": "en", "general_texts": {"general.hello_word": "Hello world!", "general.yes": "Yes", "general.no": "No"}},
    {"code": "es", "general_texts": {"general.hello_word": "Hola mundo!", "general.yes": "Si", "general.no": "No"}},
    {"code": "zh-CN", "general_texts": {"general.hello_word": "你好词", "general.yes": "是", "general.no": "没有"}}
  ],
  "interpolations": {
    "id_1": {"type": "material", "channels": "rgb", "data": [0.0, 1.0, 0.0, 1000, 0.0, 0.0, 0.0, 0]},
    "id_2": {"type": "transform", "channels": "xyz", "data": [0.0, 1.0, 0.0, 1000, 0.0, 0.0, 0.0, 0]}
  },
  "map_array_strings": {
    "map_array_strings_1": ["hello1", "world1", "!!"],
    "map_array_strings_2": ["hello2", "world2", "!!"]
  }
}
```

Declare the schema once:

```cpp
#include "zetjsoncpp.h"

#include <cstddef>
#include <iostream>
#include <string>

ZJ_DEFINE_OBJECT(Ident,
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
    ZJ_OBJECT(Ident, indent),
    ZJ_ARRAY_OBJECT(Language, languages),
    ZJ_MAP_OBJECT(Interpolation, interpolations),
    ZJ_MAP_ARRAY_STRING(map_array_strings)
);

int main() {
    try {
        auto json_object = zetjsoncpp::deserialize_file<
            zetjsoncpp::ObjectJsonVar<SampleJson>
        >("sample.json");

        std::cout << "Before modifications:\n";
        std::cout << zetjsoncpp::serialize(json_object) << std::endl;

        // Change a nested boolean.
        json_object->indent.use_space.setValue(false);

        // Update each plug-in through array indexing.
        for(std::size_t i = 0; i < json_object->plugins.size(); ++i) {
            json_object->plugins[i].setValue(
                "plugin_" + std::to_string(i + 1)
            );
        }

        // Iterate through a map of objects, then an array of numbers.
        for(auto it = json_object->interpolations.begin();
            it != json_object->interpolations.end(); ++it) {
            std::size_t index = 0;
            for(auto value_it = it->second->data.begin();
                value_it != it->second->data.end(); ++value_it) {
                value_it->setValue(static_cast<double>(index++));
            }
        }

        // Modify a map of arrays of strings.
        for(auto map_it = json_object->map_array_strings.begin();
            map_it != json_object->map_array_strings.end(); ++map_it) {
            for(std::size_t i = 0; i < map_it->second.size(); ++i) {
                map_it->second[i].setValue(
                    "modified_" + std::to_string(i)
                );
            }
        }

        std::cout << "After modifications:\n";
        std::cout << zetjsoncpp::serialize(json_object) << std::endl;

        // No delete: json_object is a std::unique_ptr.
    } catch(const std::exception &ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
```

The example illustrates direct member access, nested objects, array/map iterators, value mutation, and serialization. Unlike the old example, it does not require manual deletion of the deserialized root object.

## Migrating from 2.4.4 to 3.0.0

**Schemas:** Replace the old `ZJ_CONST_CHAR` template-based field declarations with `ZJ_DEFINE_OBJECT` and the corresponding field macros.

```cpp
// 2.4.4 (old API)
// struct Config {
//     zetjsoncpp::NumberJsonVar<ZJ_CONST_CHAR("length")> length;
// };

// 3.0.0
ZJ_DEFINE_OBJECT(Config,
    ZJ_NUMBER(length)
);
```

**Field names:** By default the C++ identifier becomes the JSON property name. Use a supported `_NAMED` macro when the names differ.

**Ownership:** Deserialization now returns `std::unique_ptr<T>` rather than a raw pointer:

```cpp
auto config = zetjsoncpp::deserialize<
    zetjsoncpp::ObjectJsonVar<Config>
>("{\"length\":10}");

// Access with -> as before, but do not call delete config.get().
```

**Value access:** Prefer `getValue()` and `setValue()` rather than relying on implicit conversion, comparison, or arithmetic operators that may have been removed in 3.0.

**Object traversal:** `ObjectJsonVar<T>` uses registered fields generated by the schema rather than sentinel/pointer-arithmetic traversal. User-defined schemas must use the new registration mechanism.

## Compatibility notes

- Language standard: **C++11**.
- Numeric values in the updated `NumberJsonVar` implementation use `double`.
- The library provides typed arrays and maps; mixed-type arrays and generic dynamic JSON documents are not part of the documented 3.0 typed-container API.
- `std::unique_ptr` controls root-object ownership; pointer-owning container implementations still need correct destruction, `erase()`, and copy semantics.
- For Unicode strings, validate UTF-8 encoding and JSON `\\uXXXX` escape handling on your target platform.
