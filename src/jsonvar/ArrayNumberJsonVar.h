namespace zetjsoncpp{

	// ARRAY FLOAT
	class ArrayNumberJsonVar : public JsonVar, public ArrayJsonVar<NumberJsonVar> {

	public:
		//_T_NAME name;
		explicit ArrayNumberJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_ARRAY_OF_NUMBERS
		) {
		}


		ArrayNumberJsonVar(const std::vector<float> & _vec_numbers) {
			copy(_vec_numbers);
		}


		ArrayNumberJsonVar & operator=(const std::vector<float> & _vec_numbers){
			copy(_vec_numbers);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vector_data__.push_back(NumberJsonVar(10));

			return &this->__zj_vector_data__[this->__zj_vector_data__.size()-1];
		}

		virtual ~ArrayNumberJsonVar() {
		}

	private:
		void copy(const std::vector<float> & v){
			this->__zj_vector_data__.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->__zj_vector_data__.push_back(*it);
			}
		}

	};
}
