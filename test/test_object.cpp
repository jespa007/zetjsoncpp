
#include "../zetjsoncpp.h"



// json data to c-structure

typedef struct{
	zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("length")>  	length;
	zetjsoncpp::JsonVarBoolean<ZJ_CONST_CHAR("use_space")> use_space;
}Ident;

typedef struct{
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("code")>  	code;
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("text")> text;
}Language;

typedef struct
{
    // Default encoding for text
	zetjsoncpp::JsonVarString<ZJ_CONST_CHAR("encoding")> 		encoding;

    // Example number
	zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("number")> 		number;
	
    // Plug-ins loaded at start-up
	zetjsoncpp::JsonVarVectorString<ZJ_CONST_CHAR("plug-ins")> 	plugins;
        
    // Tab indent size
    zetjsoncpp::JsonVarObject<Ident,ZJ_CONST_CHAR("indent")> 	indent;

    // Tab indent size
    zetjsoncpp::JsonVarVectorObject<Language,ZJ_CONST_CHAR("languages")> 	languages;

    // Map
    zetjsoncpp::JsonVarMapString<ZJ_CONST_CHAR("properties")> 	properties;
}SampleJson;


int main(int argc, char *argv[]){

	bool print_utf8 = false;

    // create json-parser


    try{

    	auto  parser = new zetjsoncpp::ZetJsonCpp<zetjsoncpp::JsonVarObject<SampleJson>>();
    	auto  data_json = parser->evalFile("test_object.json");

		// the values before modifications.
		std::cout << " Before modifications:"<< std::endl;
		std::cout << data_json->toString();

		//parser->getData(); // gets first element group...

		// From here we can operate with loaded data in our program using c++ operators
		// put m_use_space to false...
		data_json->indent.use_space = false;

		// iterate of all m_plugins var and Replace with random strings...
		for(unsigned i = 0; i < data_json->plugins.size(); i++) {
			data_json->plugins[i] = "my_randomstring"+zetjsoncpp::zj_strutils::int_to_str(i+1);
		}

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;

		// show the modifications at screen (it can be saved in file too)
		std::string json_out = data_json->toString();

		std::cout << json_out;

	    // deallocates parser
	    delete parser;

    }catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

    


#ifdef __MEMMANAGER__
   MEMMGR_print_status();
#endif

    // that's all :)
    return 0;

}
