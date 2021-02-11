#include "../zetjsoncpp.h"

typedef struct{
	// Number length
	zetjsoncpp::JsonVarNumber<ZJ_CONST_CHAR("length")>
	length;

	// Boolean use_space
	zetjsoncpp::JsonVarBoolean<ZJ_CONST_CHAR("use_space")>
	use_space;

}TestJson;

int main(int argc, char *argv[]){

	std::cout << "zetjsoncpp ver. "<< ZETJSONCPP_MAJOR_VERSION << "." << ZETJSONCPP_MINOR_VERSION << "."<< ZETJSONCPP_PATCH_VERSION << std::endl;

	try{

		std::cout << "1. Testing json primitives and basic operations..."<< std::endl;
		auto n1=zetjsoncpp::parse<zetjsoncpp::JsonVarNumber<>>("1");
		auto n2=zetjsoncpp::parse<zetjsoncpp::JsonVarNumber<>>("3.7e-5");
		auto n3=*n1+*n2; // concatenate

		auto s1=zetjsoncpp::parse<zetjsoncpp::JsonVarString<>>("\"my_string\"");
		auto s2=zetjsoncpp::parse<zetjsoncpp::JsonVarString<>>("\"_2\"");
		auto s3=*s1+*s2; // concatenate

		auto b1=zetjsoncpp::parse<zetjsoncpp::JsonVarBoolean<>>("true");
		auto b2=zetjsoncpp::parse<zetjsoncpp::JsonVarBoolean<>>("false");
		auto b3=*b1 || *b2;

		if(b3 == true){
			std::cout << "b3 is true" << std::endl;
		}

		std::cout << "3. Testing object..."<< std::endl;
		auto o1=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorObject<TestJson>>("{"
			"\"length\":1000"
			",\"use_space\":false"
		"}");

		std::cout << "2. Testing json vector primitives..."<< std::endl;

		auto v1=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorNumber<>>("[1,2,3,4]");
		auto v2=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorString<>>("[\"string_1\",\"string_2\",\"string_3\",\"string_5\"]");
		auto v3=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorBoolean<>>("[true,false,true]");
		auto v4=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorObject<TestJson>>("[{"
			"\"length\":1000"
			",\"use_space\":false"
		"},{"
			"\"length\":1500"
			",\"use_space\":true"
		"}]");

		std::cout << "3. Testing json map primitives..."<< std::endl;

		auto m1=zetjsoncpp::parse<zetjsoncpp::JsonVarMapNumber<>>("{\"id1\":1,\"id2\":2,\"id3\":3,\"id4\":4}");
		auto m2=zetjsoncpp::parse<zetjsoncpp::JsonVarMapString<>>("{\"id1\":\"string_1\",\"id2\":\"string_2\",\"id3\":\"string_3\",\"id4\":\"string_5\"}");
		auto m3=zetjsoncpp::parse<zetjsoncpp::JsonVarMapBoolean<>>("{\"id1\":true,\"id2\":false,\"id3\":true}");
		auto m4=zetjsoncpp::parse<zetjsoncpp::JsonVarMapObject<TestJson>>("{"
			"\"id1\":{"
				"\"length\":1000"
				",\"use_space\":false"
			"}"
			",\"id2\":{"
				"\"length\":1500"
				",\"use_space\":true"
			"}"
		"}");

		// destroy json_object
		delete n1;
		delete n2;

		delete s1;
		delete s2;

		delete b1;
		delete b2;

		delete o1;

		delete v1;
		delete v2;
		delete v3;
		delete v4;

		delete m1;
		delete m2;
		delete m3;
		delete m4;


	}catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

#ifdef __MEMMANAGER__
   MEMMGR_print_status();
#endif

    // that's all :)
    return 0;


}
