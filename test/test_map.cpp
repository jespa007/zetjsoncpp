
#include "../zetjsoncpp.h"


// json data to c-structure

int main(int argc, char *argv[]){

	bool print_utf8 = false;


	if(argc <=1){
		std::cerr << std::endl;
		std::cerr << "put json file with starting json map string"<< std::endl;
		std::cerr << std::endl;
		std::cerr << "example:"<< std::endl;
		std::cerr << std::endl;
		std::cerr << "test_map test_map.json"<< std::endl;
		return 0;
	}
    // declare our data var interface.
	//zetjsoncpp::JsonVarObject<SampleJson> * data_json=NULL;

    // create json-parser
	auto parser = new zetjsoncpp::ZetJsonCpp<zetjsoncpp::JsonVarMapString<>>();
	//auto  parser = new zetjsoncpp::ZetJsonCpp<zetjsoncpp::JsonVarObject<SampleJson>>();

    try{
		auto data=parser->evalFile(argv[1]);

		// get data from parser.
		std::cout << "elements:" << data->size()<< std::endl;
		// the values before modifications.
		std::cout << " Before modifications:"<< std::endl;
		std::cout << data->toString();

		/*for(unsigned g = 0; g < parser->getData()->size(); g++){
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
		std::cout << " After modifications:"<< std::endl;*/

		// show the modifications at screen (it can be saved in file too)
		std::string json_out = data->toString();

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
