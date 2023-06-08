#define TEST_NUMBER_OP(op)\
printf("Testing ((%.2f"#op"%.2f) == (%.2f"#op"%.2f)) == ((%.2f"#op"%.2f)"#op"(%.2f"#op"%.2f))\n",\
(float)jvn1[i],v2[i],v1[i],(float)jvn2[i],v1[i],v2[i],(float)jvn1[i],(float)jvn2[i]\
);\
assert(\
		(((jvn1[i]) op (v2[i])) == ((v1[i]) op (jvn2[i]))) == ((v1[i] op v2[i]) == ((jvn1[i]) op (jvn2[i])))\
)



void test_json_var_number(){
	std::vector<float> v1={1,2,2.5};
	std::vector<float> v2={-1,2,4};
	std::map<std::string,float> m1={
			 {"id_1",1}
			,{"id_2",2}
			,{"id_3",2.5}
	};

	zetjsoncpp::ArrayJsonVarNumber<> jvn1=v1;
	zetjsoncpp::ArrayJsonVarNumber<> jvn2=v2;
	zetjsoncpp::MapNumberJsonVar<> 	  jmn1=m1;
	size_t len=v1.size();

	//assert(1.00<-1.00 == 1.00<-1.00 == 1.00<-1.00);

	std::cout << "Testing arithmetic ops ..." << std::endl;

	// check all boolean ops
	for(unsigned i=0; i < len; i++){
		assert(v1[i]==jvn1[i]);
		assert(v2[i]==jvn2[i]);

		TEST_NUMBER_OP(<);
		TEST_NUMBER_OP(<=);
		TEST_NUMBER_OP(>);
		TEST_NUMBER_OP(>=);
		TEST_NUMBER_OP(==);
		TEST_NUMBER_OP(!=);

		TEST_NUMBER_OP(+);
		TEST_NUMBER_OP(-);
		TEST_NUMBER_OP(*);
		TEST_NUMBER_OP(/);

		assert(-v2[i]==-jvn2[i]);
	}

	std::cout << "Testing number vector insert/erase/push_back ops ..." << std::endl;
	std::vector<float> num={1,2,3};

	for(unsigned i=0; i < num.size(); i++){
		v1.push_back(num[i]);
		jvn1.push_back(num[i]);
	}

	// remove at...1
	v1.erase(v1.begin()+1);
	jvn1.erase(1);

	// insert at...2
	v1.insert(v1.begin()+2,10);
	jvn1.insert(2,10);

	// check integrity ...
	for(unsigned i=0; i < v1.size(); i++){
		assert(v1[i]==jvn1[i]);
	}

	// check map
	std::cout << "Testing number map insert/erase ops ..." << std::endl;
	for(auto it=m1.begin(); it != m1.end(); it++){
		assert(it->second==jmn1[it->first]);
	}

	for(unsigned i=0; i < num.size(); i++){
		std::string key=zetjsoncpp::string_utils::format("id_%i",i+4);
		m1[key]=num[i];
		jmn1.insert(key,num[i]);
	}

	// remove at
	m1.erase("id_2");
	jmn1.erase("id_2");

	// check integration
	for(auto it=m1.begin(); it != m1.end(); it++){
		assert(it->second==jmn1[it->first]);
	}

}
