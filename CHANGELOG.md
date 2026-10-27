
# Changelog

----------------------------
## [3.0.0] - 2026-10-25


Major release introducing a redesigned JSON schema system, safer memory management, and a simplified C++11 API.

### Added
- Introduced `JsonSchema.h` with the `ZJ_DEFINE_OBJECT` macro for defining JSON object schemas.
- Added schema field macros for primitive values, nested objects, arrays, and maps (`ZJ_STRING`, `ZJ_NUMBER`, `ZJ_BOOLEAN`, `ZJ_OBJECT`, etc.).
- Added support for custom JSON property names through `ZJ_ARRAY_STRING_NAMED`.
- Added `visitFields()` for automatic schema field enumeration.
- Added virtual `forEachField()` methods to `JsonVar`, supporting mutable and const field traversal.

### Changed
- **Breaking:** `deserialize<T>()` and `deserialize_file<T>()` now return `std::unique_ptr<T>` instead of raw pointers.
- Updated `serialize()` to accept `std::unique_ptr<T>` directly while retaining support for raw `JsonVar` pointers.
- Replaced the old object-property discovery mechanism with explicit schema-based field visitation.
- Simplified the `JsonVar` inheritance hierarchy by removing `NamedJsonVar`.
- Replaced the compile-time property-name generation mechanism (`ZJ_CONST_CHAR`) with string-literal property names.
- Removed the previous fixed-length JSON property-name limitation.
- Simplified string value access and assignment through `getValue()` and `setValue()`.
- Improved const-correctness in object field traversal.
- Modernized file reading using `std::string` instead of manually managed character buffers.
- Changed float to double value in NumberJsonVar to improve number arithmetic precision 

### Fixed
- Removed unsafe pointer arithmetic used to discover object properties.
- Eliminated reliance on object memory layout, padding, and alignment when enumerating JSON fields.
- Reduced the risk of memory leaks by introducing automatic ownership of deserialized objects.
- Improved compatibility with modern C++ compilers by removing deprecated implicit-copy behavior in `StringJsonVar`.

### Removed
- **Breaking:** Removed the `ZJ_CONST_CHAR` macro and compile-time character-pack property names.
- **Breaking:** Removed the `NamedJsonVar` class.
- **Breaking:** Removed sentinel-based object field traversal (`_zj_var_start`, `_zj_var_end`).
- Removed obsolete object-layout metadata used for property enumeration.
- Removed selected implicit primitive conversion and comparison operators in favor of explicit value access.

### Migration Guide (2.4.4 → 3.0.0)

**1. Replace manually declared JSON structures with `ZJ_DEFINE_OBJECT`.**

Before:

```cpp
typedef struct {
    zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR("encoding")>		encoding;
    zetjsoncpp::NumberJsonVar<ZJ_CONST_CHAR("length")>      	length;
    zetjsoncpp::ArrayStringJsonVar<ZJ_CONST_CHAR("plug-ins")>  	plugins;
} Config;
```

Now:

```cpp
ZJ_DEFINE_OBJECT(
	Config
    	,ZJ_STRING(encoding) // both cpp/json field are named "encoding"
    	,ZJ_NUMBER(length)	// both cpp/json field are named "length"
    	,ZJ_ARRAY_STRING_NAMED(plugins,"plug-ins") // cpp field is called "plugins" meanwhile json field is named ""plug-ins" 
);


```

**2. Update deserialization to use automatic memory management.**

Before:

```cpp
auto *config = zetjsoncpp::deserialize<
    zetjsoncpp::ObjectJsonVar<Config>
>(json_text);

// Use config...

delete config;
```

Now:

```cpp
auto config = zetjsoncpp::deserialize<
    zetjsoncpp::ObjectJsonVar<Config>
>(json_text);

// No manual delete required (in case of use of delete by mistake from deserialized object it will throw an error at compile time)
```

**3. Arithmetic operators has been removed. It has to use operations from its primitive values **

Before:

```cpp
config->name = "example";

if(config->name == "example") {
    // ...
}
```

Now:

```cpp
config->name.setValue("example");

if(config->name.getValue() == "example") {
    // ...
}
```

**4. Existing array and map container types remain available.**

The existing typed containers, including `ArrayStringJsonVar`, `ArrayNumberJsonVar`, `ArrayObjectJsonVar<T>`, `MapStringJsonVar`, and `MapObjectJsonVar<T>`, can be declared through the new schema macros.


----------------------------
Date: 2024-02-08
Version: 2.4.4

- [x] Change StringJsonVar::c_str -> StringJsonVar::toConstChar

----------------------------
Date: 2023-11-03
Version: 2.4.3

- [x] Fix compile on MAC

----------------------------
Date: 2023-11-01
Version: 2.4.2

- [x] Fix issue cmake on MAC

----------------------------
Date: 2023-10-23
Version: 2.4.1

- [x] Fix warning MapArrayStrings and put working example

----------------------------
Date: 2023-10-23
Version: 2.4.0

- [x] Implement MapArrayStrings

----------------------------
Date: 2023-08-02
Version: 2.3.3

- [x] deserialize_exception : Save line and description

----------------------------
Date: 2023-08-02
Version: 2.3.2

- [x] Change ArrayJsonVarNumber to ArrayNumberJsonVar

----------------------------
Date: 2023-07-06
Version: 2.3.1

- [x] Fix include directory for linux

----------------------------
Date: 2023-06-08
Version: 2.3.0

- [x] Refactory utils

----------------------------
Date: 2023-05-13
Version: 2.2.0

- [x] Change name JsonVarXXXX -> XXXXJsonVar

----------------------------
Date: 2022-12-21
Version: 2.1.0

- [x] Do not serialize unserialized fields in objects
- [x] use -WSanitizer=Address in linux if memmgr directory not found

----------------------------
Date: 2022-07-01
Version: 2.0.4

- [x] Compile with pedantic
- [x] Adapt changes memmgr
- [x] JsonVar::__zs_variable__: change std::string type to char[ZJ_MAX_CONST_CHAR]
- [x] reorder dirs

----------------------------
Date: 2021-07-10
Version: 2.0.3

- [x] Organize files
- [x] Move src dir

----------------------------
Date: 2021-04-15
Version: 2.0.2

- [x] Fix bug write exception message when filename is null (whn loads in mmeory)
- [x] Improve error exception

----------------------------
Date: 2021-04-07
Version: 2.0.1

- [x] Fix bug crash when cannot parse json value

----------------------------
Date: 2021-02-14
Version: 2.0.0

Main features

- [x] Added support for map/dictionary of elements
- [x] Massive code organization and clean up
- [x] Support uft-8 files with bom
- [x] Support for deserialize any json type (i.e number/string/boolean/object, vector or map of elements) 

Detail

#19 Support unicode files/strings
#20 throw error instead of if(error)
#21 Removed CBuffer
#22 Changed var/C* to var/JZ_*
#23 organize zetjsoncpp_utils to string and io files 
#4 changed CParserVarXXXXArray by CParserVarArrayXXXX 
#5 ZJ_Number: Only works with floats 
#6 Migrate new c++ style 
#10 Change ParseJson name by ZetJsonCpp
#11 Test operator functions for number/string/boolean 
#12 Change Json Object names starting by JsonVarXXXXX
#13 Implement JsonVarMap
#14 Specify starting type JsonVar (i.e JsonVarNumber,JsonVarObject, JsonVarArrayObject, ...) instead of fixed JsonVarArrayObject<_T>
#16 create tests test
#17 Support UTF-8 with/out BOM mark Feature 
#18 Pre/Post name all variables associated with JsonVar 

----------------------------
Date: 2018-05-15
Version: 1.3.0

- [x] Review version history to new format (MAJOR.MINOR.PATCH)
- [x] Behaviour on error/warning is done through a callback setFunctionOnError, setFunctionOnWarning. If these functions are not set, then the message is printed with fprintf (stderr)
- [x] Added memory leak detection (only for GNU toolchain).  It needs memmanager https://github.org/jespa007/memmanager and pass -DMEMMANAGER parameter on cmake 
- [x] Fixed compile test_json shared library on MSVC plataform 
- [x] improve cmake message prints 

----------------------------
Date: 2018-05-10
Version: 1.2.0

- [x] MSVC Support (v141 Tools or MSVC++ 2015)
- [x] restruct files/dirs new set.
- [x] Added zetjsoncpp namespace
- [x] Renamed fastjsoncpp to zetjsoncpp
- [x] Added feature detect array types
- [x] Changed GPL3 license to MIT

----------------------------
Date: 2015-08-29
Version: 1.1.0

- [x] Added feature support numbor as cientific notation (i.e 2.1E-10).
- [x] Added feature on detecting property group or property group arrays.
- [x] Fixed carry return line feeds compatible for Windows

----------------------------
Date: 2014-08-08
Version: 1.0.0

- [x] First version
