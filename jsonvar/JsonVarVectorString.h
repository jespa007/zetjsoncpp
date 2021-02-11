namespace zetjsoncpp{

	// ARRAY STRING
	template<char... _T_NAME>
	class JsonVarVectorString : public JsonVarNamed<_T_NAME...>, public JsonVarVector<std::string> {
	public:
		//_T_NAME name;
		JsonVarVectorString() {
			this->__js_type__ = JsonVarType::JSON_VAR_TYPE_VECTOR_OF_STRINGS;
			this->__js_size_data__ = sizeof(JsonVarVectorString< _T_NAME...>);
			this->__js_ptr_data_start__ = &this->__js_vec_data__;
		}

		void add(std::string const & s) {
			((std::vector<std::string> *)this->__js_ptr_data_start__)->push_back(s);
		}

		virtual std::string toStringFormatted(int ident, uint16_t properties = 0) {
			bool not_minimized = ((properties & ZJ_PROPERTY_OUTPUT_FORMAT_MINIMIZED) == 0);
			std::string str_value = "";
			std::vector<std::string> * v = (std::vector<std::string> *)this->__js_ptr_data_start__;

			if (not_minimized){
				ZJ_FORMAT_OUTPUT_IDENT(str_value,ident);
			}

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					str_value += ",";
				}

				str_value = str_value + "\"" + v->at(j) + "\"";

				if(not_minimized){
					ZJ_FORMAT_OUTPUT_NEW_LINE_VECTOR_ELEMENTS(str_value,ident,j);
				}

			}
			return str_value;
		}

		virtual ~JsonVarVectorString(){}

	};
}
