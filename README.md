# zetjsoncpp 

ZetJsonCpp it allows load data form json format into C estructures. 

As an example, let's supose we want to load the following json data that is saved in sample.json file,

```
{
    "encoding" : "UTF-8",
    "number": 3.34E-5
     "plug-ins" : [
        "python",
        "c++",
        "ruby"
        ],
    "indent" : { "length" : 3, "use_space": true }
}
```

List 1.1

To load the code saw on list 1.1 we have to declare the following C estructure,

```
typedef struct{
	// Number length
	zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("length")>
	length;

	// Boolean use_space
	zetjsoncpp::JsonVarBoolean<ZJ_CONST_CHAR("use_space")>
	use_space;
}Ident;

typedef struct
{
	// String encoding
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("encoding")>
	encoding;
	
	// Number number
	zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("number")>
	number;

	// Vector of strings plug-ins
	zetjsoncpp::JsonVarVectorString<ZJ_CONST_CHAR("plug-ins")>
	plugins;
	
	// Object indent
	zetjsoncpp::JsonVarObject<Ident,ZJ_CONST_CHAR("indent")>
	indent;

}SampleJson;
```

List 1.2

And then we have to write the following code to load the data seen on list 1.1 into the estructure on list 1.2,

```
#include "zetjsoncpp.h"

int main(int argc, char *argv[]){

	try{
		zetjsoncpp::JsonVarObject<SampleJson> *json_object=zetjsoncpp::parse_file<zetjsoncpp::JsonVarObject<SampleJson>>("sample.json");
		// .... operate data with loaded json_object

		// destroy json_object
		delete json_object;
	}catch(std::exception & ex){
		fprintf(stderr, "%s\n",ex.what());
	}
    
	return 0;
}
```

As an example, we present a way to operate loaded json data into C++ code,

```
#include "zetjsoncpp.h"

int main(int argc, char *argv[]){

	try{
		zetjsoncpp::JsonVarObject<SampleJson> *json_object=zetjsoncpp::parse_file<zetjsoncpp::JsonVarObject<SampleJson>>("sample.json");
		
		// the values before modifications.
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " Before modifications:"<< std::endl;
		std::cout << json_object->toString();

		// From here we can operate with loaded data in our program using c++ operators
		json_object->indent.use_space = false;

		for(unsigned i = 0; i < json_object->plugins.size(); i++) {
			json_object->plugins[i] = "my_randomstring"+zetjsoncpp::zj_strutils::int_to_str(i+1);
		}

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;
		std::cout << json_object->toString();

		// destroy json_object
		delete json_object;

	}catch(std::exception & ex){
		fprintf(stderr, "%s\n",ex.what());
	}

	return 0;
}
```


