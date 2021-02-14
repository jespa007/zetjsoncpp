namespace zetjsoncpp{

	// ARRAY FLOAT
	template<char... _T_NAME>
	class JsonVarVectorNumber : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarNumber<>> {
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


		virtual JsonVar *newJsonVar(){
			this->__js_vec_data__.push_back(JsonVarNumber<>(10));

			return &this->__js_vec_data__[this->__js_vec_data__.size()-1];
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::vector<JsonVarNumber<>> * v = (std::vector<JsonVarNumber<>> *)this->__js_ptr_data__;
			std::string str_value = "";

			str_value+=toStringFormattedStart(ident,properties);

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					if (not_minimized) {
						ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident+1,j);
					}
					str_value += ",";
				}

				str_value += v->at(j).toString();

			}

			str_value+=toStringFormattedEnd(ident,properties);

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
