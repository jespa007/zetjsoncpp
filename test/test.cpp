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
		auto n2=zetjsoncpp::parse<zetjsoncpp::JsonVarNumber<>>("3.7e+2");
		auto n3=1.2+*n1+1+*n2+10; // test operations
		printf("n1=%.2f n2=%.2f n3=%.2f\n",(float)*n1,(float)*n2,(float)n3);

		auto s1=zetjsoncpp::parse<zetjsoncpp::JsonVarString<>>("\"my_string\"");
		auto s2=zetjsoncpp::parse<zetjsoncpp::JsonVarString<>>("\"_2\"");
		auto s3="s1_"+*s1+"_s2_"+*s2+"_end"; // concatenate
		printf("s1=%s s2=%s s3=%s\n",s1->toString().c_str(),s2->toString().c_str(),s3.toString().c_str());

		auto b1=zetjsoncpp::parse<zetjsoncpp::JsonVarBoolean<>>("true");
		auto b2=zetjsoncpp::parse<zetjsoncpp::JsonVarBoolean<>>("false");
		bool b3=true || *b1 || false || *b2 || true;
		printf("b1=%s b2=%s b3=%s\n",b1->toString().c_str(),b2->toString().c_str(),b3?"true":"false");


		std::cout << "2. Testing object..."<< std::endl;
		auto o1=zetjsoncpp::parse<zetjsoncpp::JsonVarObject<TestJson>>("{"
			"\"length\":1000"
			",\"use_space\":false"
		"}");

		printf("o1.length=%.02f o1.use_space=%s\n",(float)o1->length,o1->use_space==true?"true":"false");

		std::cout << "3. Testing json vector primitives..."<< std::endl;

		auto v1=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorNumber<>>("[1,2,3,4]");
		printf("v1=%s\n",v1->toString().c_str());

		auto v2=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorString<>>("[\"string_1\",\"string_2\",\"string_3\",\"string_5\"]");
		printf("v2=%s\n",v2->toString().c_str());

		auto v3=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorBoolean<>>("[true,false,true]");
		printf("v3=%s\n",v3->toString().c_str());

		auto v4=zetjsoncpp::parse<zetjsoncpp::JsonVarVectorObject<TestJson>>("[{"
			"\"length\":1000"
			",\"use_space\":false"
		"},{"
			"\"length\":1500"
			",\"use_space\":true"
		"}]");
		printf("v4=%s\n",v4->toString().c_str());

		std::cout << "3. Testing json map primitives..."<< std::endl;

		auto m1=zetjsoncpp::parse<zetjsoncpp::JsonVarMapNumber<>>("{\"id1\":1,\"id2\":2,\"id3\":3,\"id4\":4}");
		printf("m1=%s\n",m1->toString().c_str());

		auto m2=zetjsoncpp::parse<zetjsoncpp::JsonVarMapString<>>("{\"id1\":\"string_1\",\"id2\":\"string_2\",\"id3\":\"string_3\",\"id4\":\"string_5\"}");
		printf("m2=%s\n",m2->toString().c_str());
		auto m3=zetjsoncpp::parse<zetjsoncpp::JsonVarMapBoolean<>>("{\"id1\":true,\"id2\":false,\"id3\":true}");
		printf("m3=%s\n",m3->toString().c_str());
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
		printf("m4=%s\n",m4->toString().c_str());

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
