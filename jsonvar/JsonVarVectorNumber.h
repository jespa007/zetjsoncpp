namespace zetjsoncpp{

	// ARRAY FLOAT
	template<char... _T_NAME>
	class JsonVarVectorNumber : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarNumber<>> {
		short * shortBuf;
		float * floatBuf;

	public:
		//_T_NAME name;
		JsonVarVectorNumber() {
			this->__zj_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS;
			this->__zj_size_data__ = sizeof(JsonVarVectorNumber<_T_NAME...>);
			this->__zj_ptr_data_start__ = &this->__zj_vec_data__;
			shortBuf=NULL;
			floatBuf=NULL;
		}

		virtual JsonVar *newJsonVar(){
			this->__zj_vec_data__.push_back(JsonVarNumber<>(10));

			return &this->__zj_vec_data__[this->__zj_vec_data__.size()-1];
		}

		float *toFloatBuffer(size_t & length) {

			float *floatBuf = new float[__zj_vec_data__.size()];
			for (unsigned i = 0; i < __zj_vec_data__.size(); i++){
				floatBuf[i]=__zj_vec_data__[i];
			}

			length=__zj_vec_data__.size();
			return floatBuf;
		}


		short *toShortBuffer(size_t & length) {

			short * shortBuf = new short[__zj_vec_data__.size()];
			for (unsigned i = 0; i < __zj_vec_data__.size(); i++){
				shortBuf[i]=__zj_vec_data__[i];
			}

			length = __zj_vec_data__.size();
			return shortBuf;
		}

		virtual ~JsonVarVectorNumber() {
		}
	};
}
