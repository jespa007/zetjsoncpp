namespace zetjsoncpp{

	// ARRAY STRING
	template<char... _T_NAME>
	class JsonVarVectorString : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarString<>> {
	public:
		//_T_NAME name;
		JsonVarVectorString() {
			init();
		}

		JsonVarVectorString(const std::vector<std::string> & _vec_string) {
			init();
			copy(_vec_string);
		}


		JsonVarVectorString<> & operator=(const std::vector<std::string> & _vec_string){
			copy(_vec_string);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vector_data__.push_back(JsonVarString<>());

			return &this->__zj_vector_data__[this->__zj_vector_data__.size()-1];
		}

		virtual ~JsonVarVectorString(){}

	private:

		void copy(const std::vector<std::string> & v){
			this->__zj_vector_data__.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->__zj_vector_data__.push_back(*it);
			}
		}

		void init() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS;
			this->__zj_size_data__ = sizeof(JsonVarVectorString< _T_NAME...>);
		}


	};
}
