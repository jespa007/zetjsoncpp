
#include "../zetjsoncpp.h"



// json data to c-structure

typedef struct{
	zetjsoncpp::Number<ZJ_CONST_CHAR("length")>  	m_length;
	zetjsoncpp::Boolean<ZJ_CONST_CHAR("use_space")> m_use_space;
}Ident;

typedef struct{
	zetjsoncpp::String<ZJ_CONST_CHAR("code")>  	m_code;
	zetjsoncpp::String<ZJ_CONST_CHAR("text")> m_text;
}Language;

typedef struct
{
    // Default encoding for text
	zetjsoncpp::String<ZJ_CONST_CHAR("encoding")> 		m_encoding;

    // Example number
	zetjsoncpp::Number<ZJ_CONST_CHAR("number")> 		m_number;
	
    // Plug-ins loaded at start-up
	zetjsoncpp::ArrayString<ZJ_CONST_CHAR("plug-ins")> 	m_plugins;
        
    // Tab indent size
    zetjsoncpp::Object<Ident,ZJ_CONST_CHAR("indent")> 	m_indent;

    // Tab indent size
    zetjsoncpp::ArrayObject<Language,ZJ_CONST_CHAR("languages")> 	m_languages;
}SampleJson;


int main(int argc, char *argv[]){

	bool print_utf8 = false;
	std::cout << "zetjsoncpp ver. "<< ZETJSONCPP_MAJOR_VERSION << "." << ZETJSONCPP_MINOR_VERSION << "."<< ZETJSONCPP_PATCH_VERSION << std::endl;
	if(argc <=1){
		std::cerr << "put file to parse"<< std::endl;
		return 0;
	}

    // declare our data var interface.
	zetjsoncpp::Object<SampleJson> * data_json=NULL;

    // create json-parser
	zetjsoncpp::ZetJsonCpp<SampleJson> * parser = new zetjsoncpp::ZetJsonCpp<SampleJson>();

    try{
		parser->evalFile(argv[1]);

		// get data from parser.
		std::cout << "elements:" << parser->getData()->size()<< std::endl;
		// the values before modifications.
		std::cout << " Before modifications:"<< std::endl;
		std::cout << parser->getData()->toString();

		for(unsigned g = 0; g < parser->getData()->size(); g++){
			data_json = parser->getData()->at(0); // gets first element group...

			// From here we can operate with loaded data in our program using c++ operators
			// put m_use_space to false...
			data_json->m_indent.m_use_space = false;

			// iterate of all m_plugins var and Replace with random strings...
			for(unsigned i = 0; i < data_json->m_plugins.size(); i++) {
				data_json->m_plugins[i] = "my_randomstring"+zetjsoncpp::zj_strutils::int_to_str(i+g+1);
			}

		}

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;

		// show the modifications at screen (it can be saved in file too)
		std::string json_out = parser->getData()->toString();

		std::cout << json_out;

    }catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

    

    // deallocates parser
   delete parser;

#ifdef __MEMMANAGER__
   MEMMGR_print_status();
#endif

    // that's all :)
    return 0;

}
