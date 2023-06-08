#include "zetjsoncpp.h"

typedef struct{
	// Number length
	zetjsoncpp::NumberJsonVar<ZJ_CONST_CHAR("length")>
	length;

	// Boolean use_space
	zetjsoncpp::BooleanJsonVar<ZJ_CONST_CHAR("use_space")>
	use_space;
}Ident;

typedef struct{
	// string_utils code
	zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR("code")>
	code;

	// Map of strings general_texts
	zetjsoncpp::MapStringJsonVar<ZJ_CONST_CHAR("general_texts")>
	general_texts;
}Language;


typedef struct{
	// string_utils type
	zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR("type")>
	type;

	// string_utils channels
	zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR("channels")>
	channels;

	// Vector of numbers data
	zetjsoncpp::ArrayJsonVarNumber<ZJ_CONST_CHAR("data")>
	data;
}Interpolation;

typedef struct
{
    // string_utils encoding
	zetjsoncpp::StringJsonVar<ZJ_CONST_CHAR("encoding")>
	encoding;

    // Number number
	zetjsoncpp::NumberJsonVar<ZJ_CONST_CHAR("number")>
	number;

    // Vector of strings plug-ins
	zetjsoncpp::ArrayStringJsonVar<ZJ_CONST_CHAR("plug-ins")>
	plugins;

    // Object indent
    zetjsoncpp::ObjectJsonVar<Ident,ZJ_CONST_CHAR("indent")>
    indent;

    // Object languages
    zetjsoncpp::ArrayObjectJsonVar<Language,ZJ_CONST_CHAR("languages")>
    languages;

    // Map of objects interpolations
    zetjsoncpp::MapObjectJsonVar<Interpolation,ZJ_CONST_CHAR("interpolations")>
    interpolations;


}SampleJson;

int main(int argc, char *argv[]){

	std::cout << "zetjsoncpp ver. "<< ZETJSONCPP_VERSION_MAJOR << "." << ZETJSONCPP_VERSION_MINOR << "."<< ZETJSONCPP_VERSION_PATCH << std::endl;
	if(argc <=1){
		std::cerr << "put file to parse"<< std::endl;
		return 0;
	}

	try{
		auto json_object=zetjsoncpp::deserialize_file<zetjsoncpp::ObjectJsonVar<SampleJson>>(argv[1]);

		// the values before modifications.
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " Before modifications:"<< std::endl;
		std::cout << zetjsoncpp::serialize(json_object);

		// From here we can operate with loaded data in our program using c++ operators
		// put m_use_space to false...
		json_object->indent.use_space = false;

		// iterate of all plugins and replace with random strings...
		for(unsigned i = 0; i < json_object->plugins.size(); i++) {
			json_object->plugins[i] = "my_randomstring"+zetjsoncpp::string_utils::integerToString(i+1);
		}

		// iterate of all interpolations and replace its data values...
		for(auto it_map = json_object->interpolations.begin(); it_map != json_object->interpolations.end(); it_map++) {
			for(auto it = it_map->second->data.begin(); it != it_map->second->data.end(); it++) {
				*it = rand();
			}
		}

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;
		std::cout << zetjsoncpp::serialize(json_object);

		// destroy json_object
		delete json_object;

	}catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

    // that's all :)
    return 0;


}
