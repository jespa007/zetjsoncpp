#include <assert.h>
#include "zetjsoncpp.h"


#include "test_number.cpp"
#include "test_boolean.cpp"
#include "test_string.cpp"

typedef struct{
	// Number length
	ZJ_VAR_NUMBER(length);

	// Boolean use_space
	ZJ_VAR_BOOLEAN(use_space);

}TestJson;



/*

-int test primitive values from C and test them out automatically

std::vector<bool/float/string> [1,2,-3,4]
add
remove

std::map<bool/float/string> [1,2,-3,4]
add
remove

*/

int main(int argc, char *argv[]){

	ZJ_UNUSUED_2PARAMS(argc,argv);

	std::cout << "zetjsoncpp ver. "<< ZETJSONCPP_VERSION_MAJOR << "." << ZETJSONCPP_VERSION_MINOR << "."<< ZETJSONCPP_VERSION_PATCH << std::endl;

	try{

		std::cout << "1. Testing json primitives and basic operations..."<< std::endl;
		auto n1=zetjsoncpp::deserialize<zetjsoncpp::JsonVarNumber<>>("1");
		auto n2=zetjsoncpp::deserialize<zetjsoncpp::JsonVarNumber<>>("3.7e+2");
		auto n3=1.2+*n1+1+*n2+10; // test operations
		std::cout << zetjsoncpp::zj_strutils::format("n1=%.2f n2=%.2f n3=%.2f",(float)*n1,(float)*n2,(float)n3)<< std::endl;

		auto s1=zetjsoncpp::deserialize<zetjsoncpp::JsonVarString<>>("\"my_string\"");
		auto s2=zetjsoncpp::deserialize<zetjsoncpp::JsonVarString<>>("\"_2\"");
		auto s3="s1_"+*s1+"_s2_"+*s2+"_end"; // concatenate

		std::cout <<zetjsoncpp::zj_strutils::format("s1=%s s2=%s s3=%s"
				,zetjsoncpp::serialize(s1).c_str()
				,zetjsoncpp::serialize(s2).c_str()
				,zetjsoncpp::serialize(&s3).c_str())<< std::endl;

		auto b1=zetjsoncpp::deserialize<zetjsoncpp::JsonVarBoolean<>>("true");
		auto b2=zetjsoncpp::deserialize<zetjsoncpp::JsonVarBoolean<>>("false");
		bool b3=true || *b1 || false || *b2 || true;
		std::cout <<zetjsoncpp::zj_strutils::format("b1=%s b2=%s b3=%s\n"
				,zetjsoncpp::serialize(b1).c_str()
				,zetjsoncpp::serialize(b2).c_str(),b3?"true":"false")<< std::endl;


		std::cout << std::endl << "2. Testing object..."<< std::endl<< std::endl;
		auto o1=zetjsoncpp::deserialize<zetjsoncpp::JsonVarObject<TestJson>>("{"
			"\"length\":1000"
			",\"use_space\":false"
		"}");

		std::cout <<zetjsoncpp::zj_strutils::format("o1.length=%.02f o1.use_space=%s\n",(float)o1->length,o1->use_space==true?"true":"false")<< std::endl;

		std::cout << std::endl << "3. Testing json vector primitives..."<< std::endl<< std::endl;

		auto v1=zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorNumber<>>("[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]");
		std::cout <<"v1="<< zetjsoncpp::serialize(v1)<< std::endl;

		auto v2=zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorString<>>("[\"string_1\",\"string_2\",\"string_3\",\"string_5\"]");
		std::cout <<"v2="<<zetjsoncpp::serialize(v2)<< std::endl;

		auto v3=zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorBoolean<>>("[true,false,true]");
		std::cout <<"v3="<<zetjsoncpp::serialize(v3)<< std::endl;

		auto v4=zetjsoncpp::deserialize<zetjsoncpp::JsonVarVectorObject<TestJson>>("[{"
			"\"length\":1000"
			",\"use_space\":false"
		"},{"
			"\"length\":1500"
			",\"use_space\":true"
		"}]");
		std::cout <<"v4="<<zetjsoncpp::serialize(v4)<< std::endl;

		std::cout << std::endl << "4. Testing json map primitives..."<< std::endl<< std::endl;

		auto m1=zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapNumber<>>("{\"id1\":1,\"id2\":2,\"id3\":3,\"id4\":4}");
		std::cout <<"m1="<<zetjsoncpp::serialize(m1)<< std::endl;

		auto m2=zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapString<>>("{\"id1\":\"string_1\",\"id2\":\"string_2\",\"id3\":\"string_3\",\"id4\":\"string_5\"}");
		std::cout <<"m2="<<zetjsoncpp::serialize(m2)<< std::endl;

		auto m3=zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapBoolean<>>("{\"id1\":true,\"id2\":false,\"id3\":true}");
		std::cout <<"m3="<<zetjsoncpp::serialize(m3)<< std::endl;

		auto m4=zetjsoncpp::deserialize<zetjsoncpp::JsonVarMapObject<TestJson>>("{"
			"\"id1\":{"
				"\"length\":1000"
				",\"use_space\":false"
			"}"
			",\"id2\":{"
				"\"length\":1500"
				",\"use_space\":true"
			"}"
		"}");
		std::cout <<"m4="<<zetjsoncpp::serialize(m4)<< std::endl;

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

		test_json_var_number();
		test_json_var_boolean();
		test_json_var_string();

	}catch(std::exception & ex){
    	fprintf(stderr, "%s\n",ex.what());
    }

    // that's all :)
    return 0;


}
