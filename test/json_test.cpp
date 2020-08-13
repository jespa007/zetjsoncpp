
#include "../zetjsoncpp.h"



// json data to c-structure

typedef struct{
	zetjsoncpp::Number<ZJ_CONST_CHAR("length")>  m_length;
	zetjsoncpp::Boolean<ZJ_CONST_CHAR("use_space")> m_use_space;
}Ident;

typedef struct
{
    // Default encoding for text
	zetjsoncpp::String<ZJ_CONST_CHAR("encoding")> 		m_encoding;
	
    // Example number
	zetjsoncpp::Number<ZJ_CONST_CHAR("number")> 		m_number;
	
    // Plug-ins loaded at start-up
    StringArray<ZJ_CONST_CHAR("plug-ins")> 	 m_plugins;
        
    // Tab indent size
    zetjsoncpp::PropertyGroup<Ident,ZJ_CONST_CHAR("indent")> m_indent;
}SampleJson;


int main(int argc, char *argv[]){

	std::cout << "zetjsoncpp ver. "<< ZETJSONCPP_MAJOR_VERSION << "." << ZETJSONCPP_MINOR_VERSION << "."<< ZETJSONCPP_PATCH_VERSION << std::endl;
	if(argc <=1){
		std::cerr << "put file to parse"<< std::endl;
		return 0;
	}
    // declare our data var interface.
    //PropertyGroup<tSampleJson> * data_json_array;
	zetjsoncpp::PropertyGroup<SampleJson> * data_json=NULL;

    // create json-parser
	zetjsoncpp::ZetJsonCpp<SampleJson> * parser = new zetjsoncpp::ZetJsonCpp<SampleJson>();

    try{
		parser->evalFile(argv[1]);


			// get data from parser.
		std::cout << "elements:" << parser->getData()->size()<< std::endl;
		// the values before modifications.
		std::cout << " Before modifications:"<< std::endl;
		std::cout << parser->getData()->cpp2json();
		for(unsigned g = 0; g < parser->getData()->size(); g++){
			data_json = parser->getData()->at(0); // gets first element group...

			// From here we can operate with loaded data in our program using c++ operators
			// put m_use_space to false...
			data_json->m_indent.m_use_space = false;

			// iterate of all m_plugins var and Replace with random strings...
			for(unsigned i = 0; i < data_json->m_plugins.size(); i++) {
				data_json->m_plugins[i] = "my_randomstring"+zetjsoncpp::StrUtils::int2str(i+g+1);
			}

		}

		std::cout << "------------------------------------------------------------------------------" << std::endl;
		std::cout << " After modifications:"<< std::endl;

		// show the modifications at screen (it can be saved in file too)
		std::cout << parser->getData()->cpp2json();
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
