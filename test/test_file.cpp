#include "../zetjsoncpp.h"

// json data to c-structure

typedef struct{
	// Number length
	zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("length")>
	length;

	// Boolean use_space
	zetjsoncpp::JsonVarBoolean<ZJ_CONST_CHAR("use_space")>
	use_space;
}Ident;

typedef struct{
	// String code
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("code")>
	code;

	// Map of strings general_texts
	zetjsoncpp::JsonVarMapString<ZJ_CONST_CHAR("general_texts")>
	general_texts;
}Language;


typedef struct{
	// String type
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("type")>
	type;

	// String channels
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("channels")>
	channels;

	// Vector of numbers data
	zetjsoncpp::JsonVarVectorNumber<ZJ_CONST_CHAR("data")>
	data;
}Interpolation;

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

    // Object languages
    zetjsoncpp::JsonVarVectorObject<Language,ZJ_CONST_CHAR("languages")>
    languages;

    // Map of objects interpolations
    zetjsoncpp::JsonVarMapObject<Interpolation,ZJ_CONST_CHAR("interpolations")>
    interpolations;


}SampleJson;

int main(int argc, char *argv[]){

	std::cout << "zetjsoncpp ver. "<< ZETJSONCPP_MAJOR_VERSION << "." << ZETJSONCPP_MINOR_VERSION << "."<< ZETJSONCPP_PATCH_VERSION << std::endl;
	if(argc <=1){
		std::cerr << "put file to parse"<< std::endl;
		return 0;
	}

	try{
		auto json_object=zetjsoncpp::parse_file<zetjsoncpp::JsonVarObject<SampleJson>>(argv[1]);

		// the values before modifications.
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " Before modifications:"<< std::endl;
		std::cout << json_object->toString();

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

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;
		std::cout << json_object->toString();

		// destroy json_object
		delete json_object;

	}catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

#ifdef __MEMMANAGER__
   MEMMGR_print_status();
#endif

    // that's all :)
    return 0;


}
