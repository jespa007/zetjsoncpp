namespace zetjsoncpp{

	// ARRAY STRING
	class ArrayStringJsonVar : public JsonVar, public ArrayJsonVar<StringJsonVar> {
	public:
		//_T_NAME name;
		explicit ArrayStringJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_ARRAY_OF_STRINGS
		) {
		}

		ArrayStringJsonVar(const std::vector<std::string> & _vec_string) {
			copy(_vec_string);
		}


		ArrayStringJsonVar & operator=(const std::vector<std::string> & _vec_string){
			copy(_vec_string);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->_vector_data.push_back(StringJsonVar());

			return &this->_vector_data[this->_vector_data.size()-1];
		}

		virtual ~ArrayStringJsonVar(){}

	private:

		void copy(const std::vector<std::string> & v){
			this->_vector_data.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->_vector_data.push_back(*it);
			}
		}

	};
}
