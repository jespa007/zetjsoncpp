namespace zetjsoncpp{

	// ARRAY STRING
	template<char... _T_NAME>
	class ArrayStringJsonVar : public NamedJsonVar<_T_NAME...>, public ArrayJsonVar<StringJsonVar<>> {
	public:
		//_T_NAME name;
		ArrayStringJsonVar() {
			init();
		}

		ArrayStringJsonVar(const std::vector<std::string> & _vec_string) {
			init();
			copy(_vec_string);
		}


		ArrayStringJsonVar & operator=(const std::vector<std::string> & _vec_string){
			copy(_vec_string);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vector_data__.push_back(StringJsonVar<>());

			return &this->__zj_vector_data__[this->__zj_vector_data__.size()-1];
		}

		virtual ~ArrayStringJsonVar(){}

	private:

		void copy(const std::vector<std::string> & v){
			this->__zj_vector_data__.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->__zj_vector_data__.push_back(*it);
			}
		}

		void init() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_ARRAY_OF_STRINGS;
			this->__zj_size_data__ = sizeof(ArrayStringJsonVar< _T_NAME...>);
		}


	};
}
