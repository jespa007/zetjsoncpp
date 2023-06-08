#define TEST_STRING_OP(op)\
printf("Testing ((%s"#op"%s) == (%s"#op"%s)) == ((%s"#op"%s)"#op"(%s"#op"%s))\n",\
jvn1[i].c_str(),v2[i].c_str(),v1[i].c_str(),jvn2[i].c_str(),v1[i].c_str(),v2[i].c_str(),jvn1[i].c_str(),jvn2[i].c_str()\
);\
assert(\
		(((jvn1[i]) op (v2[i])) == ((v1[i]) op (jvn2[i]))) == ((v1[i] op v2[i]) == ((jvn1[i]) op (jvn2[i])))\
)



void test_json_var_string(){
	std::vector<std::string> v1={"string_1_","string_2_","string_3_"};
	std::vector<std::string> v2={"string_3_","string_2_","string_1_"};
	std::map<std::string,std::string> m1={
			 {"id_1","string_1_"}
			,{"id_2","string_2_"}
			,{"id_3","string_3_"}
	};

	zetjsoncpp::ArrayStringJsonVar<> jvn1=v1;
	zetjsoncpp::ArrayStringJsonVar<> jvn2=v2;
	zetjsoncpp::MapStringJsonVar<>	  jmn1=m1;
	size_t len=v1.size();

	//assert(1.00<-1.00 == 1.00<-1.00 == 1.00<-1.00);

	std::cout << "Testing string arithmetic ops ..." << std::endl;


	// check all boolean ops
	for(unsigned i=0; i < len; i++){
		assert(v1[i]==jvn1[i]);
		assert(v2[i]==jvn2[i]);

		TEST_STRING_OP(==);
		TEST_STRING_OP(!=);
		TEST_STRING_OP(+);
	}

	std::cout << "Testing string vector insert/erase/push_back ops ..." << std::endl;
	std::vector<std::string> string_extra={"string_8_","string_9_","string_10_"};

	for(unsigned i=0; i < string_extra.size(); i++){
		v1.push_back(string_extra[i]);
		jvn1.push_back(string_extra[i]);
	}

	// remove at...1
	v1.erase(v1.begin()+1);
	jvn1.erase(1);

	// insert at...2
	v1.insert(v1.begin()+2,"string_extra");
	jvn1.insert(2,std::string("string_extra"));

	// check integrity ...
	for(unsigned i=0; i < v1.size(); i++){
		assert(v1[i]==jvn1[i]);
	}

	// check map
	std::cout << "Testing string map insert/erase ops ..." << std::endl;
	for(auto it=m1.begin(); it != m1.end(); it++){
		assert(it->second==jmn1[it->first]);
	}

	for(unsigned i=0; i < string_extra.size(); i++){
		std::string key=zetjsoncpp::string_utils::format("id_%i",i+4);
		m1[key]=string_extra[i];
		jmn1.insert(key,string_extra[i]);
	}

	// remove at
	m1.erase("id_2");
	jmn1.erase("id_2");

	// check integration
	for(auto it=m1.begin(); it != m1.end(); it++){
		assert(it->second==jmn1[it->first]);
	}

}
