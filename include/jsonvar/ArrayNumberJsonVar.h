namespace zetjsoncpp{

	// ARRAY FLOAT
	class ArrayNumberJsonVar : public JsonVar, public ArrayJsonVar<NumberJsonVar> {

	public:
		using JsonVar::newJsonVar;

		//_T_NAME name;
		explicit ArrayNumberJsonVar(const char * _name = "")
		:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_ARRAY_OF_NUMBERS
		) {
		}


		ArrayNumberJsonVar(const std::vector<double> &_vec_numbers)
		    : JsonVar("", JsonVarType::JSON_VAR_TYPE_ARRAY_OF_NUMBERS) {
		    copy(_vec_numbers);
		}


		ArrayNumberJsonVar & operator=(const std::vector<double> & _vec_numbers){
			copy(_vec_numbers);
			return *this;
		}

		virtual JsonVar *newJsonVar(){

			this->_vector_data.push_back(NumberJsonVar(10));

			return &this->_vector_data[this->_vector_data.size()-1];
		}

		void forEachArrayElement(ConstFieldCallback _callback ,void *_context) const override {
		    this->visitArrayElements(
		        _callback
		        ,_context
		    );
		}


		virtual ~ArrayNumberJsonVar() {
		}

	private:
		void copy(const std::vector<double> & v){
			this->_vector_data.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->_vector_data.push_back(*it);
			}
		}

	};
}
