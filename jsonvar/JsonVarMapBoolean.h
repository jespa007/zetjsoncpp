namespace zetjsoncpp{

	template<char... _T_NAME>
	class JsonVarMapBoolean: public JsonVarNamed<_T_NAME...>, public JsonVarMap<bool> {

	public:

		JsonVarMapBoolean() {
			this->type = JsonVar::JSON_VAR_TYPE_MAP_BOOLEAN;
			this->size_data = sizeof(JsonVarMapString< _T_NAME...>);
			this->p_data = &this->map_data;
		}

		/*void set(std::string const & key, std::string const & value) {
			((std::map<std::string,std::string> *)this->p_data)->;
		}*/


		/*virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			this->str_value = "??";
			return this->str_value;
		}*/

		/*virtual void add(JsonVar * s) {
			JsonVarObject< _T_DATA> *tt = (JsonVarObject< _T_DATA> *)s;
			this->push_back(tt);
		}*/

		//std::string result_json;
		virtual std::string & toString(int ident=0, uint32_t flags = 0) {

			bool not_minimized = ((flags & JsonVar::PROPERTY_STR_MINIMIZED) == 0);
			this->str_value = "";

			if (not_minimized)
				for (int k = 0; k <= (ident + 1); k++){
					this->str_value = this->str_value + "\t";
				}

			int j=0;
			for (auto it=map_data.begin();it !=map_data.end();it++,j++) {

				if (j > 0){
					this->str_value = this->str_value + ",";
				}

				this->str_value = this->result_json += "\""+it->first +"\":"+ (it->second==true?"true":"false")+"";// this->str_value + "\"" + v->at(j) + "\" ";

				if (not_minimized)
					if (j != 0 && ((j%N_ELEMENTS_JSON_VECTOR_PRINT) == 0))
					{
						for (int k = 0; k <= (ident + 1); k++){
							this->str_value = this->str_value + "\t";
						}
						this->str_value += "\n";
					}

			}
			return this->str_value;

		}

		void destroy() {

			/*for (unsigned i = 0; i < this->vec_data.size(); i++) {
				delete this->vec_data[i];
				this->vec_data[i] = NULL;
			}

			this->vec_data.clear();*/
		}

		virtual ~JsonVarMapString() {
			destroy();
		}
	};
}
