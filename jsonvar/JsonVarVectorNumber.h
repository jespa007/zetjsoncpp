namespace zetjsoncpp{

	// ARRAY FLOAT
	template<char... _T_NAME>
	class JsonVarVectorNumber : public JsonVarNamed<_T_NAME...>, public JsonVarVector<float> {
		short * shortBuf;
		float * floatBuf;

	public:
		//_T_NAME name;
		JsonVarVectorNumber() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_NUMBERS;
			this->__js_size_data__ = sizeof(JsonVarVectorNumber<_T_NAME...>);
			this->__js_ptr_data__ = &this->__js_vec_data__;
			shortBuf=NULL;
			floatBuf=NULL;
		}

		void add(float s) {
			((std::vector<float> *)this->__js_ptr_data__)->push_back(s);
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::vector<float> * v = (std::vector<float> *)this->__js_ptr_data__;
			std::string str_value = "";

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_IDENT(str_value,ident);
			}

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					str_value += ",";
				}

				str_value += zj_strutils::float_to_str(v->at(j));

				if (not_minimized) {
					ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident,j);
				}
			}
			return str_value;
		}

		float *toFloatBuffer(size_t & length) {

			float *floatBuf = new float[__js_vec_data__.size()];
			for (unsigned i = 0; i < __js_vec_data__.size(); i++){
				floatBuf[i]=__js_vec_data__[i];
			}

			length=__js_vec_data__.size();
			return floatBuf;
		}


		short *toShortBuffer(size_t & length) {

			short * shortBuf = new short[__js_vec_data__.size()];
			for (unsigned i = 0; i < __js_vec_data__.size(); i++){
				shortBuf[i]=__js_vec_data__[i];
			}

			length = __js_vec_data__.size();
			return shortBuf;
		}

		virtual ~JsonVarVectorNumber() {
		}
	};
}
