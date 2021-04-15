# zetjsoncpp 

A library that deserializes/serializes from/to Json string or files

## Deserialization

To serialize json variable it done using zetjsoncpp::deserialize. ZetJsonCpp supports deserialization of the following types,

* Boolean
* Vector of booleans
* Map of booleans
* Number
* Vector of numbers
* Map of numbers
* String
* Vector of strings
* Map of strings
* Object
* Vector of objects
* Map of objects
 
 
### Boolean

To deserialize a json boolean, it is done through `JsonVarBoolean` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarBoolean<>>("true");
</pre>

### Vector of Booleans

A json vector of booleans it could be the following,

<pre lang="javascript">
[true,false,true]
</pre>

To deserialize a json vector of booleans, it is done through `JsonVarVectorBoolean` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorBoolean<>>(
"["
   "true"
   ",false"
   ",true"
"]");
</pre>

### Map of Booleans

A json map of booleans it could be the following,

<pre lang="javascript">
{
   "id1":true
  ,"id2":false
  ,"id3":true
}
</pre>

To deserialize a json map of booleans, it is done through `JsonVarMapBoolean` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapBoolean<>>(
"{"
   "\"id1\":true"
   ",\"id2\":false"
   ",\"id3\":true"
"}");
</pre>

### Number
A json number it could be the following,


* -1
* 2.5
* 3.7e+2

To deserialize a json number, it is done through `JsonVarNumber` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarNumber<>>("1");
</pre>

### Vector of Numbers
A json vector of numbers it could be the following,

<pre lang="javascript">
[1,3.7e+2,-3]
</pre>

To deserialize a json vector of numbers, it is done through `JsonVarVectorNumber` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorNumber<>>(
"["
   "1"
   ",3.7e+2"
   ",-3"
"]");
</pre>

### Map of numbers
A json map of numbers it could be the following,

<pre lang="javascript">
{ 
  "id1":1
 ,"id2":3.7e+2
 ,"id3":-3
}
</pre>

To deserialize a json map of numbers, it is done through `JsonVarMapNumber` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapNumber<>>(
"{"
   "\"id1\":1"
   ",\"id2\":3.7e+2"
   ",\"id3\":-3"
"}");
</pre>

### String
To deserialize a json string, it is done through `JsonVarString` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarString<>>("\"my_string\"")
</pre>

### Vector of Strings
A json vector of strings it could be the following,
<pre lang="javascript">
["string_1","string_2","string_3"]
</pre>
To deserialize a vector of strings, it is done through `JsonVarVectorString` as it shows below,

<pre lang="c++">
zetjsoncpp::deserialize<JsonVarVectorString<>>(
"["
    "\"string_1\""
    ",\"string_2\""
    ",\"string_3\""
"]");
</pre>

### Map of Strings
A json map of strings it could be the following,

<pre lang="javascript">
{ 
   "id1":"string_1"
   ,"id2":"string_2"
   ,"id3":"string_3" 
}
</pre>

To deserialize a map of strings, it is done through `JsonVarMapString` as it shows below,

<pre lang="c++">
JsonVarMapString<> *m3=zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapString<>>(
"{"
    "\"id1\":\"string_1\""
    ",\"id2\":\"string_2\""
    ",\"id3\":\"string_3\""
"}");
</pre>

### Object
Until now it has seen a way to serialize primitive and structured types easy to understant. Now we presents the method to deserialize json object that it requires a little bit of setup. A json object is like a json map with different content on its values.

A json object it could be the following 

<pre lang="javascript">
{
  "encoding":"UTF-8"
 ,"length":1000
 ,"use_space":false
}
</pre>

**List 2.1**

Taking the example of list 2.1, in zetjsoncpp it defines json object using a structure in C as it shows below,

<pre lang="c++">
typedef struct{
    zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("encoding")>    encoding;
    zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("length")>      length;     
    zetjsoncpp::JsonVarBoolean<ZJ_CONST_CHAR("use_space")>  use_space; 
}JsonSample;
</pre>

**List 2.2**
Note:

You may noticed that of ZJ_CONST_CHAR(s). This is a trick to pass literal string through variadic templates char by char, due that templates doesn't accept pass literal strings (i.e const char *) as a parameter.

An finally, to deserialize a json object, it is done through `JsonVarObject` passing the type of structure to deserialize it has seen in list 2.2,

<pre lang="c++">
auto json_object=zetjsoncpp::deserialize<zetjsoncpp::JsonVarObject<JsonSample>>(
"{"
   "\"encoding\":\"UTF-8\""
   ",\"length\":1000"
   ",\"use_space\":false"         
"}");
</pre>

If any variable has not been deserialized, because it does not exist in string/file either it doesn't match json property name json with that defined in the C++ structure, it has to use isDeserialized() to check whether the variable was deserialized or not.

For example:

<pre lang="c++">
if(json_object->encoding.isDeserialized()){

// value deserialized ok. do something... 

}
</pre>

List 3.4
By default, any no deserialized variable the strings are set empty, numbers and booleans will set as 0 and false respectively.

### Vector of Objects
A json vector of objects it could be the following,

<pre lang="javascript">
[{ 
    "encoding":"UTF-8" 
    ,"length":1000 
    ,"use_space":false 
 },{   
    "encoding":"ANSII"
   ,"length":1500   
   ,"use_space":true 
}]
</pre>

To deserialize a vector of objects, it is done through `JsonVarVectorObject` passing the type of structure to deserialize it has seen in list 2.2,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorObject<JsonSample>>(
"[{"  
   "\"encoding\":\"UTF-8\""  
   ",\"length\":1000"   
   ",\"use_space\":false" 
  "},{"  
    "\"encoding\":\"ANSII\""  
    ",\"length\":1500"  
    ",\"use_space\":true" 
"}]");
</pre>

### Map of Objects
A json map of objects it could be the following,

<pre lang="javascript">
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
</pre>

To deserialize a map of objects, it is done through `JsonVarMapObject` passing the type of structure to deserialize it has seen in list 2.2,

<pre lang="c++">
zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapObject<JsonSample>>(
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
</pre>

## Serialize
To serialize json variable it done using zetjsoncpp::serialize.

For example,

<pre lang="c++">
// parse json var number
auto json_number=zetjsoncpp::deserialize<zetjsoncpp::JsonVarNumber<>>("2");

// change it by 3.5
json_number=3.5;

std::cout << zetjsoncpp::serialize(json_var); << std::enl;

// it outputs 3.5
</pre>

## A big example

Let's suppose it has a file called sample.json with the following content,

<pre lang="javascript">
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
</pre>

**List 3.1**

To load the code saw on list 1.1 we have to declare the following C estructure,

<pre lang="c++">
#include "zetjsoncpp.h"

using zetjsoncpp::JsonVarNumber;
using zetjsoncpp::JsonVarBoolean;
using zetjsoncpp::JsonVarString;
using zetjsoncpp::JsonVarMapString;
using zetjsoncpp::JsonVarVectorNumber;
using zetjsoncpp::JsonVarVectorString;
using zetjsoncpp::JsonVarObject;
using zetjsoncpp::JsonVarVectorObject;
using zetjsoncpp::JsonVarMapObject;

typedef struct{
  // Number length
  JsonVarNumber<ZJ_CONST_CHAR("length")>  length;

  // Boolean use_space
  JsonVarBoolean<ZJ_CONST_CHAR("use_space")>use_space;
}Ident;

typedef struct{
  // String code
  JsonVarString<ZJ_CONST_CHAR("code")>  code;

  // Map of strings general_texts
  JsonVarMapString<ZJ_CONST_CHAR("general_texts")>  general_texts;
}Language;


typedef struct{
  // String type
  JsonVarString<ZJ_CONST_CHAR("type")>  type;

  // String channels
  JsonVarString<ZJ_CONST_CHAR("channels")>  channels;

  // Vector of numbers data
  JsonVarVectorNumber<ZJ_CONST_CHAR("data")>  data;
}Interpolation;

typedef struct
{
  // String encoding
  JsonVarString<ZJ_CONST_CHAR("encoding")>  encoding;

  // Number number
  JsonVarNumber<ZJ_CONST_CHAR("number")>  number;

  // Vector of strings plug-ins
  JsonVarVectorString<ZJ_CONST_CHAR("plug-ins")>  plugins;

  // Object indent
  JsonVarObject<Ident,ZJ_CONST_CHAR("indent")>  indent;

  // Object languages
  JsonVarVectorObject<Language,ZJ_CONST_CHAR("languages")>  languages;

  // Map of objects interpolations
  JsonVarMapObject<Interpolation,ZJ_CONST_CHAR("interpolations")>  interpolations;


}SampleJson;
</pre>

**List 3.2**

And then we have to write the following code to load the data seen on list 1.1 into the estructure on list 1.2,

<pre lang="c++">
try{
    auto json_object=zetjsoncpp::deserialize_file<JsonVarObject<SampleJson>>("sample.json");

    // the values before modifications.
    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << " Before modifications:"<< std::endl;
    std::cout << zetjsoncpp::serialize(json_object);

    // From here we can operate with loaded data in our program using c++ operators
    // put m_use_space to false...
    json_object->indent.use_space = false;

    // iterate of all plugins and replace with random strings...
    for(unsigned i = 0; i < json_object->plugins.size(); i++) {
      json_object->plugins[i] = "my_randomstring"+zetjsoncpp::zj_strutils::int_to_str(i+1);
    }

    // iterate of all interpolations and replace its data values...
    for(auto it_map = json_object->interpolations.begin(); it_map != json_object->interpolations.end(); it_map++) {
      for(auto it = it_map->second->data.begin(); it != it_map->second->data.end(); it++) {
        *it = rand();
      }
    }

    std::cout << "--------------------------------------------------" << std::endl;
    std::cout << " After modifications:"<< std::endl;
    std::cout << zetjsoncpp::serialize(json_object);

    // destroy json_object
    delete json_object;
  }catch(std::exception & ex){
   std::cerr << "Error:" << ex.what() << std::endl;
 }
</pre>

As an example, we present a way to operate loaded json data into C++ code,

<pre lang="c++">
int main(int argc, char *argv[]){

    try{
        auto json_object=zetjsoncpp::deserialize_file<JsonVarObject<SampleJson>>("sample.json");

        // the values before modifications.
        std::cout << "---------------------------------------------------" << std::endl;
        std::cout << " Before modifications:"<< std::endl;
        std::cout << zetjsoncpp::serialize(json_object);

        // From here we can operate with loaded data in our program using c++ operators
        // put m_use_space to false...
        json_object->indent.use_space = false;

        // iterate of all plugins and replace with random strings...
        for(unsigned i = 0; i < json_object->plugins.size(); i++) {
            json_object->plugins[i] = "my_randomstring"+zetjsoncpp::zj_strutils::int_to_str(i+1);
        }

        // iterate of all interpolations and replace its data values...
        for(auto it_map = json_object->interpolations.begin(); it_map != json_object->interpolations.end(); it_map++) {
            for(auto it = it_map->second->data.begin(); it != it_map->second->data.end(); it++) {
                *it = rand();
            }
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
</pre>

After its execution the output shows the serialized json before and after the changes,

```
---------------------------------------------------
 Before modifications:
{
    "encoding":"UTF-8",
    "number":0.000033,
    "plug-ins":
    [
        "python","c++","ruby"
    ],
    "indent":
    {
        "length":3.000000,
        "use_space":true
    },
    "languages":
    [{
        "code":"en",
        "general_texts":
        {
            "general.hello_word":"Hello world!"
            ,"general.no":"No"
            ,"general.yes":"Yes"
        }
    },{
        "code":"es",
        "general_texts":
        {
            "general.hello_word":"Hola mundo!"
            ,"general.no":"No"
            ,"general.yes":"Si"
        }
    },{
        "code":"zh-CN",
        "general_texts":
        {
 			"general.hello_word":"你好词"
            ,"general.no":"没有"
            ,"general.yes":"是"
        }
    }],
    "interpolations":
    {
        "id_1":{
            "type":"material",
            "channels":"rgb",
            "data":
            [
                0.000000,1.000000,0.000000,1000.000000,0.000000,0.000000,0.000000,0.000000
            ]
        }
        ,"id_2":{
            "type":"transform",
            "channels":"xyz",
            "data":
            [
                0.000000,1.000000,0.000000,1000.000000,0.000000,0.000000,0.000000,0.000000
            ]
        }
    }
}--------------------------------------------------
 After modifications:
{
    "encoding":"UTF-8",
    "number":0.000033,
    "plug-ins":
    [
        "my_randomstring1","my_randomstring2","my_randomstring3"
    ],
    "indent":
    {
        "length":3.000000,
        "use_space":false
    },
    "languages":
    [{
        "code":"en",
        "general_texts":
        {
            "general.hello_word":"Hello world!"
            ,"general.no":"No"
            ,"general.yes":"Yes"
        }
    },{
        "code":"es",
        "general_texts":
        {
            "general.hello_word":"Hola mundo!"
            ,"general.no":"No"
            ,"general.yes":"Si"
        }
    },{
        "code":"zh-CN",
        "general_texts":
        {
 			"general.hello_word":"你好词"
            ,"general.no":"没有"
            ,"general.yes":"是"
        }
    }],
    "interpolations":
    {
        "id_1":{
            "type":"material",
            "channels":"rgb",
            "data":
            [
                41.000000,18467.000000,6334.000000,26500.000000,19169.000000,15724.000000,11478.000000,29358.000000
            ]
        }
        ,"id_2":{
            "type":"transform",
            "channels":"xyz",
            "data":
            [
                26962.000000,24464.000000,5705.000000,28145.000000,23281.000000,16827.000000,9961.000000,491.000000
            ]
        }
    }
}

```
