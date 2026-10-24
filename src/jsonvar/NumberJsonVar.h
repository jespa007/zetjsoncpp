namespace zetjsoncpp{
	class NumberJsonVar : public JsonVar{
	public:
			static float parse(const std::string & str ){
				float f=0;
				if(string_utils::stringToFloat(&f,str)!=string_utils::STR_2_NUMBER_SUCCESS){
					throw std::runtime_error(std::string("cannot convert ") + str + std::string(" as float"));
				}

				return f;
			}

			explicit NumberJsonVar(const char *_name = "")
			:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_NUMBER) {
			}

			 NumberJsonVar(float f) {
				this->_value = f;
			}

			 NumberJsonVar(const std::string & s) {
				this->_value = parse(s);
			}


			// assign
			NumberJsonVar & operator=(float _value){
				this->_value = _value;
				return *this;
			}

			NumberJsonVar & operator=(const NumberJsonVar & _n){
				_value=_n._value;
				return *this;
			}

			float getValue() const{
				return this->_value;
			}

			void setValue(float _value){
				this->_value = _value;
			}

			virtual void * getPtrValue(){ return &this->_value;}


			virtual ~NumberJsonVar(){}
	private:

		float _value = 0;

	};
}
