

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
