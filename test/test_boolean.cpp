#define TEST_BOOLEAN_OP(op)\
printf("Testing ((%i"#op"%i) == (%i"#op"%i)) == ((%i"#op"%i)"#op"(%i"#op"%i))\n",\
(bool)jvn1[i],(bool)v2[i],(bool)v1[i],(bool)jvn2[i],(bool)v1[i],(bool)v2[i],(bool)jvn1[i],(bool)jvn2[i]\
);\
assert(\
		(((jvn1[i]) op (v2[i])) == ((v1[i]) op (jvn2[i]))) == ((v1[i] op v2[i]) == ((jvn1[i]) op (jvn2[i])))\
)



void test_json_var_boolean(){
	std::vector<bool> v1={false,true,true,false};
	std::vector<bool> v2={true,true,false,false};
	std::map<std::string,bool> m1={
			 {"id_1",false}
			,{"id_2",true}
			,{"id_3",false}
	};

	zetjsoncpp::ArrayBooleanJsonVar<> jvn1=v1;
	zetjsoncpp::ArrayBooleanJsonVar<> jvn2=v2;
	zetjsoncpp::MapBooleanJsonVar<>	  jmn1=m1;
	size_t len=v1.size();

	//assert(1.00<-1.00 == 1.00<-1.00 == 1.00<-1.00);

	std::cout << "Testing arithmetic ops ..." << std::endl;


	// check all boolean ops
	for(unsigned i=0; i < len; i++){
		assert(v1[i]==jvn1[i]);
		assert(v2[i]==jvn2[i]);

		TEST_BOOLEAN_OP(==);
		TEST_BOOLEAN_OP(!=);

		TEST_BOOLEAN_OP(||);
		TEST_BOOLEAN_OP(&&);

		assert(!v2[i]==!jvn2[i]);
	}

	std::cout << "Testing boolean vector insert/erase/push_back ops ..." << std::endl;
	std::vector<bool> bool_extra={true,false,true};

	for(unsigned i=0; i < bool_extra.size(); i++){
		v1.push_back(bool_extra[i]);
		jvn1.push_back((bool)bool_extra[i]);
	}

	// remove at...1
	v1.erase(v1.begin()+1);
	jvn1.erase(1);

	// insert at...2
	v1.insert(v1.begin()+2,true);
	jvn1.insert(2,true);

	// check integrity ...
	for(unsigned i=0; i < v1.size(); i++){
		assert(v1[i]==jvn1[i]);
	}

	// check map
	std::cout << "Testing boolean map insert/erase ops ..." << std::endl;
	for(auto it=m1.begin(); it != m1.end(); it++){
		assert(it->second==jmn1[it->first]);
	}

	for(unsigned i=0; i < bool_extra.size(); i++){
		std::string key=zetjsoncpp::zj_strutils::format("id_%i",i+4);
		m1[key]=bool_extra[i];
		jmn1.insert(key,(bool)bool_extra[i]);
	}

	// remove at
	m1.erase("id_2");
	jmn1.erase("id_2");

	// check integration
	for(auto it=m1.begin(); it != m1.end(); it++){
		assert(it->second==jmn1[it->first]);
	}

}
