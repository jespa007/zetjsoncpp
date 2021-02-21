namespace zetjsoncpp{

	// ARRAY FLOAT
	template<char... _T_NAME>
	class JsonVarVectorNumber : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarNumber<>> {

	public:
		//_T_NAME name;
		JsonVarVectorNumber() {
			init();
		}

		JsonVarVectorNumber(const std::vector<float> & _vec_numbers) {
			init();
			copy(_vec_numbers);
		}


		JsonVarVectorNumber<> & operator=(const std::vector<float> & _vec_numbers){
			copy(_vec_numbers);
			return *this;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vector_data__.push_back(JsonVarNumber<>(10));

			return &this->__zj_vector_data__[this->__zj_vector_data__.size()-1];
		}

		float *toFloatBuffer(size_t & length) {

			float *floatBuf = new float[__zj_vector_data__.size()];
			for (unsigned i = 0; i < __zj_vector_data__.size(); i++){
				floatBuf[i]=__zj_vector_data__[i];
			}

			length=__zj_vector_data__.size();
			return floatBuf;
		}


		short *toShortBuffer(size_t & length) {

			short * shortBuf = new short[__zj_vector_data__.size()];
			for (unsigned i = 0; i < __zj_vector_data__.size(); i++){
				shortBuf[i]=__zj_vector_data__[i];
			}

			length = __zj_vector_data__.size();
			return shortBuf;
		}

		virtual ~JsonVarVectorNumber() {
		}

	private:
		void copy(const std::vector<float> & v){
			this->__zj_vector_data__.clear();
			for(auto it=v.begin(); it != v.end();it++){
				this->__zj_vector_data__.push_back(*it);
			}
		}

		void init(){
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS;
			this->__zj_size_data__ = sizeof(JsonVarVectorNumber<_T_NAME...>);
		}
	};
}
