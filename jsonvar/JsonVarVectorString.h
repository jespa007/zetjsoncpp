namespace zetjsoncpp{

	// ARRAY STRING
	template<char... _T_NAME>
	class JsonVarVectorString : public JsonVarNamed<_T_NAME...>, public JsonVarVector<JsonVarString<>> {
	public:
		//_T_NAME name;
		JsonVarVectorString() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS;
			this->__js_size_data__ = sizeof(JsonVarVectorString< _T_NAME...>);
			this->__js_ptr_data_start__ = &this->__js_vec_data__;
		}

		virtual JsonVar *newJsonVar(){
			this->__js_vec_data__.push_back(JsonVarString<>());

			return &this->__js_vec_data__[this->__js_vec_data__.size()-1];
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties = 0) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = "";
			std::vector<JsonVarString<>> * v = (std::vector<JsonVarString<>> *)this->__js_ptr_data_start__;

			str_value+=toStringFormattedStart(ident,properties);

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					if (not_minimized) {
						ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident+1,j);
					}
					str_value += ",";
				}

				str_value += (std::string)("\"" + v->at(j) + "\"");

			}

			str_value+=toStringFormattedEnd(ident,properties);

			return str_value;
		}

		virtual ~JsonVarVectorString(){}

	};
}
