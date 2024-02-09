# zetjsoncpp 

A library that deserializes/serializes from/to Json string or files

## Deserialization

To serialize json variable it done using zetjsoncpp::deserialize. ZetJsonCpp supports deserialization of the following types,

* Boolean
* Array of booleans
* Map of booleans
* Number
* Array of numbers
* Map of numbers
* String
* Array of strings
* Map of strings
* Map of array of strings
* Object
* Array of objects
* Map of objects
 
 
### Boolean

To deserialize a json boolean, it is done through `BooleanJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::BooleanJsonVar<>>("true");
```

### Array of Booleans

A json array of booleans it could be the following,

```javscript
[true,false,true]
```

To deserialize a json array of booleans, it is done through `ArrayBooleanJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::ArrayBooleanJsonVar<>>(
"["
   "true"
   ",false"
   ",true"
"]");
```

### Map of Booleans

A json map of booleans it could be the following,

```javascript
{
   "id1":true
  ,"id2":false
  ,"id3":true
}
```

To deserialize a json map of booleans, it is done through `MapBooleanJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::MapBooleanJsonVar<>>(
"{"
   "\"id1\":true"
   ",\"id2\":false"
   ",\"id3\":true"
"}");
```

### Number
A json number it could be the following,


* -1
* 2.5
* 3.7e+2

To deserialize a json number, it is done through `NumberJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar<>>("1");
```

### Array of Numbers
A json array of numbers it could be the following,

```javscript
[1,3.7e+2,-3]
```

To deserialize a json array of numbers, it is done through `ArrayNumberJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::ArrayNumberJsonVar<>>(
"["
   "1"
   ",3.7e+2"
   ",-3"
"]");
```

### Map of numbers
A json map of numbers it could be the following,

```javscript
{ 
  "id1":1
 ,"id2":3.7e+2
 ,"id3":-3
}
```

To deserialize a json map of numbers, it is done through `MapNumberJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::MapNumberJsonVar<>>(
"{"
   "\"id1\":1"
   ",\"id2\":3.7e+2"
   ",\"id3\":-3"
"}");
```

### String
To deserialize a json string, it is done through `StringJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::StringJsonVar<>>("\"my_string\"")
```

### Array of Strings
A json array of strings it could be the following,
```javscript
["string_1","string_2","string_3"]
```
To deserialize a array of strings, it is done through `ArrayStringJsonVar` as it shows below,

```cpp
zetjsoncpp::deserialize<ArrayStringJsonVar<>>(
"["
    "\"string_1\""
    ",\"string_2\""
    ",\"string_3\""
"]");
```

### Map of Strings
A json map of strings it could be the following,

```javscript
{ 
   "id1":"string_1"
   ,"id2":"string_2"
   ,"id3":"string_3" 
}
```

To deserialize a map of strings, it is done through `MapStringJsonVar` as it shows below,

```cpp
MapStringJsonVar<> *m3=zetjsoncpp::deserialize<zetjsoncpp::MapStringJsonVar<>>(
"{"
    "\"id1\":\"string_1\""
    ",\"id2\":\"string_2\""
    ",\"id3\":\"string_3\""
"}");
```

### Map of Array of Strings
A json map of strings it could be the following,

```javscript
{ 
   "id1":["string_1","string_2","string_3"]
   ,"id2":["string_4","string_5","string_6"]
   ,"id3":["string_7","string_8","string_9"]
}
```

To deserialize a map of array of strings, it is done through `MapArrayStringJsonVar` as it shows below,

```cpp
MapArrayStringJsonVar<> *m3=zetjsoncpp::deserialize<zetjsoncpp::MapArrayStringJsonVar<>>(
"{"
   "\"id1\":[\"string_1\",\"string_2\",\"string_3\"]"
   ",\"id2\":[\"string_4\",\"string_5\",\"string_6\"]"
   ",\"id3\":[\"string_7\",\"string_8\",\"string_9\"]"
"}");
```

### Object
Until now it has seen a way to serialize primitive and structured types easy to understant. Now we presents the method to deserialize json object that it requires a little bit of setup. A json object is like a json map with different content on its values.

A json object it could be the following 

```javscript
{
  "encoding":"UTF-8"
 ,"length":1000
 ,"use_space":false
}
```

**List 1.1 **

Taking the example of list 1.1, in zetjsoncpp it defines json object using a structure in C as it shows below,

```cpp
typedef struct{
    zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR("encoding")>    encoding;
    zetjsoncpp::NumberJsonVar<ZJ_CONST_CHAR("length")>      length;     
    zetjsoncpp::BooleanJsonVar<ZJ_CONST_CHAR("use_space")>  use_space; 
}JsonSample;
```

**List 1.2**
Note:

You may noticed that of ZJ_CONST_CHAR(s). This is a trick to pass literal string through variadic templates char by char, due that templates doesn't accept pass literal strings (i.e const char *) as a parameter.

An finally, to deserialize a json object, it is done through `ObjectJsonVar` passing the type of structure to deserialize it has seen in list 1.2,

```cpp
auto json_object=zetjsoncpp::deserialize<zetjsoncpp::ObjectJsonVar<JsonSample>>(
"{"
   "\"encoding\":\"UTF-8\""
   ",\"length\":1000"
   ",\"use_space\":false"         
"}");
```

If any variable has not been deserialized, because it does not exist in string/file either it doesn't match json property name json with that defined in the C++ structure, it has to use isDeserialized() to check whether the variable was deserialized or not.

For example:

```cpp
if(json_object->encoding.isDeserialized()){

// value deserialized ok. do something... 

}
```

**List 1.3**

By default, any no deserialized variable the strings are set empty, numbers and booleans will set as 0 and false respectively.

### Array of Objects
A json array of objects it could be the following,

```javscript
[{ 
    "encoding":"UTF-8" 
    ,"length":1000 
    ,"use_space":false 
 },{   
    "encoding":"ANSII"
   ,"length":1500   
   ,"use_space":true 
}]
```

To deserialize a array of objects, it is done through `ArrayObjectJsonVar` passing the type of structure to deserialize it has seen in list 1.3,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::ArrayObjectJsonVar<JsonSample>>(
"[{"  
   "\"encoding\":\"UTF-8\""  
   ",\"length\":1000"   
   ",\"use_space\":false" 
  "},{"  
    "\"encoding\":\"ANSII\""  
    ",\"length\":1500"  
    ",\"use_space\":true" 
"}]");
```

### Map of Objects
A json map of objects it could be the following,

```javscript
{
  "id1":{ 
     "encoding":"UTF-8" 
    ,"length":1000 
    ,"use_space":false
  }
  ,"id2":{
     "encoding":"ANSII"
     ,"length":1500
     ,"use_space":true
  }
}
```

To deserialize a map of objects, it is done through `MapObjectJsonVar` passing the type of structure to deserialize it has seen in list 2.2,

```cpp
zetjsoncpp::deserialize<zetjsoncpp::MapObjectJsonVar<JsonSample>>(
"{"
  "\"id1\":{"
     "\"encoding\":\"UTF-8\""  
     ",\"length\":1000"    
     ",\"use_space\":false" 
  "}"
  ",\"id2\":{"
      "\"encoding\":\"ANSII\""
      ",\"length\":1500"  
      ",\"use_space\":true" 
  "}"
"}");
```

## Serialize
To serialize json variable it done using zetjsoncpp::serialize.

For example,

```cpp
// parse json var number
auto json_number=zetjsoncpp::deserialize<zetjsoncpp::NumberJsonVar<>>("2");

// change it by 3.5
json_number=3.5;

std::cout << zetjsoncpp::serialize(json_var); << std::enl;

// it outputs 3.5
```

## A big example

Let's suppose it has a file called `sample.json` with the following content,

```javscript
// Configuration options
{
    // Default encoding for text
    "encoding" : "UTF-8",
    "number": 3.34E-5,
    // Plug-ins loaded at start-up
    "plug-ins" : [
        "python",
        "c++",
        "ruby"
      ],
        
    // Tab indent size
    "indent" : { "length" : 3, "use_space": true },
    
    // set of languages
    "languages":[{
    
	    "code" : "en",
	    "general_texts": {
            "general.hello_word":"Hello world!"
            ,"general.yes":"Yes"
            ,"general.no":"No"
        }
        
	},{
	    "code" : "es",
	    "general_texts": {
            "general.hello_word":"Hola mundo!"
            ,"general.yes":"Si"
            ,"general.no":"No"
        }
	},{
	    "code" : "zh-CN",
	    "general_texts": {
            "general.hello_word":"???"
            ,"general.yes":"?"
            ,"general.no":"??"
        }
	}]
	// set of interpolators
	,"interpolations":{
		"id_1":{
			 "type":"material"
			,"channels":"rgb"
			,"data":[
			 // r    g   b   t
			 //---- --- --- ----
				0.0,1.0,0.0,1000
				,0.0,0.0,0.0,0
			]
		},"id_2":{
			 "type":"transform"
			,"channels":"xyz"
			,"data":[
			 // x    y   z   t
			 //---- --- --- ----
				0.0,1.0,0.0,1000
				,0.0,0.0,0.0,0
			]
		}
	}
}
```

**List 1.4**

To load the code saw on list 1.4 we have to declare the following C estructure,

```cpp
#include "zetjsoncpp.h"

using zetjsoncpp::NumberJsonVar;
using zetjsoncpp::BooleanJsonVar;
using zetjsoncpp::StringJsonVar;
using zetjsoncpp::MapStringJsonVar;
using zetjsoncpp::ArrayNumberJsonVar;
using zetjsoncpp::ArrayStringJsonVar;
using zetjsoncpp::ObjectJsonVar;
using zetjsoncpp::ArrayObjectJsonVar;
using zetjsoncpp::MapObjectJsonVar;

typedef struct{
  // Number length
  NumberJsonVar<ZJ_CONST_CHAR("length")>  length;

  // Boolean use_space
  BooleanJsonVar<ZJ_CONST_CHAR("use_space")>use_space;
}Ident;

typedef struct{
  // String code
  StringJsonVar<ZJ_CONST_CHAR("code")>  code;

  // Map of strings general_texts
  MapStringJsonVar<ZJ_CONST_CHAR("general_texts")>  general_texts;
}Language;


typedef struct{
  // String type
  StringJsonVar<ZJ_CONST_CHAR("type")>  type;

  // String channels
  StringJsonVar<ZJ_CONST_CHAR("channels")>  channels;

  // Array of numbers data
  ArrayNumberJsonVar<ZJ_CONST_CHAR("data")>  data;
}Interpolation;

typedef struct
{
  // String encoding
  StringJsonVar<ZJ_CONST_CHAR("encoding")>  encoding;

  // Number number
  NumberJsonVar<ZJ_CONST_CHAR("number")>  number;

  // Array of strings plug-ins
  ArrayStringJsonVar<ZJ_CONST_CHAR("plug-ins")>  plugins;

  // Object indent
  ObjectJsonVar<Ident,ZJ_CONST_CHAR("indent")>  indent;

  // Object languages
  ArrayObjectJsonVar<Language,ZJ_CONST_CHAR("languages")>  languages;

  // Map of objects interpolations
  MapObjectJsonVar<Interpolation,ZJ_CONST_CHAR("interpolations")>  interpolations;


   // Map of array of strings
   zetjsoncpp::MapArrayStringJsonVar<ZJ_CONST_CHAR("map_array_strings")>
   map_array_strings;

}SampleJson;
```

**List 1.5**

The following code it shows and example of loading and operating the data that has seen on list 1.4 into the structure of the list 1.5,

```cpp
int main(int argc, char *argv[]){

	try{
		auto json_object=zetjsoncpp::deserialize_file<ObjectJsonVar<SampleJson>>("sample.json");
		
		// the values before modifications.
		std::cout << "---------------------------------------------------" << std::endl;
		std::cout << " Before modifications:"<< std::endl;
		std::cout << zetjsoncpp::serialize(json_object);
		
		// From here we can operate with loaded data in our program using c++ operators
		// put m_use_space to false...
		json_object->indent.use_space = false;
		
		// iterate of all plugins and replace with random strings...
		for(unsigned i = 0; i < json_object->plugins.size(); i++) {
			json_object->plugins[i] = "my_randomstring"+zetjsoncpp::String::integerToString(i+1);
		}

		// iterate of all interpolations and replace its data values...
		for(auto it_map = json_object->interpolations.begin(); it_map != json_object->interpolations.end(); it_map++) {
			for(auto it = it_map->second->data.begin(); it != it_map->second->data.end(); it++) {
			    *it = rand();
			}
		}
        
		// Modification of a map of array of strings...
		int k=0;
		for(auto it_map_array_strings : json_object->map_array_strings) {
			int j=0;
			
			for(size_t i=0; i < json_object->map_array_strings[it_map_array_strings.first].size(); i++) {
				json_object->map_array_strings[it_map_array_strings.first][i]="modified_string_"+std::to_string(k)+"_"+std::to_string(j);
				j++;
			}
			k++;
		}        

		std::cout << "--------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;
		std::cout << zetjsoncpp::serialize(json_object);
	
	    // destroy json_object
	    delete json_object;
	}catch(std::exception & ex){
    	std::cerr << "Error:" << ex.what() << std::endl;
	}
}
```

After its execution the output shows the serialized json before and after the changes,

```
---------------------------------------------------
 Before modifications:
{
	"encoding":"UTF-8"
	,"number":0.000033
	,"plug-ins":
	[
		"python","c++","ruby"
	]
	,"indent":
	{
		"length":3.000000
		,"use_space":true
	}
	,"languages":
	[{
		"code":"en"
		,"general_texts":
		{
			"general.hello_word":"Hello world!"
			,"general.no":"No"
			,"general.yes":"Yes"
		}
	},{
		"code":"es"
		,"general_texts":
		{
			"general.hello_word":"Hola mundo!"
			,"general.no":"No"
			,"general.yes":"Si"
		}
	},{
		"code":"zh-CN"
		,"general_texts":
		{
			"general.hello_word":"你好�?"
			,"general.no":"没有"
			,"general.yes":"是"
		}
	}]
	,"interpolations":
	{
		"id_1":{
			"type":"material"
			,"channels":"rgb"
			,"data":
			[
				0.000000,1.000000,0.000000,1000.000000,0.000000,0.000000,0.000000,0.000000
			]
		}
		,"id_2":{
			"type":"transform"
			,"channels":"xyz"
			,"data":
			[
				0.000000,1.000000,0.000000,1000.000000,0.000000,0.000000,0.000000,0.000000
			]
		}
	}
	,"map_array_strings":
	{
		"map_array_strings_1":[
			"hello1","world1","!!"
		]
		,"map_array_strings_2":[
			"hello2","world2","!!"
		]
	}
}
------------------------------------------------------------------------------
 After modifications:
{
	"encoding":"UTF-8"
	,"number":0.000033
	,"plug-ins":
	[
		"my_randomstring1","my_randomstring2","my_randomstring3"
	]
	,"indent":
	{
		"length":3.000000
		,"use_space":false
	}
	,"languages":
	[{
		"code":"en"
		,"general_texts":
		{
			"general.hello_word":"Hello world!"
			,"general.no":"No"
			,"general.yes":"Yes"
		}
	},{
		"code":"es"
		,"general_texts":
		{
			"general.hello_word":"Hola mundo!"
			,"general.no":"No"
			,"general.yes":"Si"
		}
	},{
		"code":"zh-CN"
		,"general_texts":
		{
			"general.hello_word":"你好�?"
			,"general.no":"没有"
			,"general.yes":"是"
		}
	}]
	,"interpolations":
	{
		"id_1":{
			"type":"material"
			,"channels":"rgb"
			,"data":
			[
				18538.000000,12292.000000,6038.000000,24179.000000,18190.000000,29657.000000,7958.000000,6191.000000
			]
		}
		,"id_2":{
			"type":"transform"
			,"channels":"xyz"
			,"data":
			[
				19815.000000,22888.000000,19156.000000,11511.000000,16202.000000,2634.000000,24272.000000,20055.000000
			]
		}
	}
	,"map_array_strings":
	{
		"map_array_strings_1":[
			"modified_string_0_0","modified_string_0_1","modified_string_0_2"
		]
		,"map_array_strings_2":[
			"modified_string_1_0","modified_string_1_1","modified_string_1_2"
		]
	}
}

```
