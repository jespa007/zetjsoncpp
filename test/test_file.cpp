#include "zetjsoncpp.h"

ZJ_DEFINE_OBJECT(
	Ident
		// Number length
		,ZJ_NUMBER(length)
		// Boolean use_space
		,ZJ_BOOLEAN(use_space)
);

ZJ_DEFINE_OBJECT(
	Language
		// string_utils code
		, ZJ_STRING(code)
		// Map of strings general_texts
		, ZJ_MAP_STRING(general_texts)
);


ZJ_DEFINE_OBJECT(
	Interpolation
		// string_utils type
		,ZJ_STRING(type)
		// string_utils channels
		,ZJ_STRING(channels)
		// Array of numbers data
		,ZJ_ARRAY_NUMBER(data)
);

ZJ_DEFINE_OBJECT(
	SampleJson
    	// string_utils encoding
		,ZJ_STRING(encoding)
		// Number number
		,ZJ_NUMBER(number)
		// Array of strings plug-ins
		,ZJ_ARRAY_STRING(plugins)
		// Object indent
		,ZJ_OBJECT(Ident,indent)
		// Object languages
		,ZJ_ARRAY_OBJECT(Language,languages)
		// Map of objects interpolations
		,ZJ_MAP_OBJECT(Interpolation,interpolations)
		// Map of array of strings
		,ZJ_MAP_ARRAY_STRING(map_array_strings)
);

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
		for(auto it_map : json_object->interpolations) {
			for(auto it = it_map.second->data.begin(); it != it_map.second->data.end(); it++) {
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

		std::cout << std::endl;
		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;
		std::cout << zetjsoncpp::serialize(json_object);


	}catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

    // that's all :)
    return 0;


}
