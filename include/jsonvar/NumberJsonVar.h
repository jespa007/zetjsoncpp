namespace zetjsoncpp{
	class NumberJsonVar : public JsonVar{
	public:
			static double parse(const std::string & str ){
				double f=0;
				if(string_utils::stringToDouble(&f,str)!=string_utils::STR_2_NUMBER_SUCCESS){
					throw std::runtime_error(std::string("cannot convert ") + str + std::string(" as double"));
				}

				return f;
			}

			explicit NumberJsonVar(const char *_name = "")
			:JsonVar(_name, JsonVarType::JSON_VAR_TYPE_NUMBER) {
			}

		    NumberJsonVar(double _value)
		        : JsonVar("", JsonVarType::JSON_VAR_TYPE_NUMBER) {
		    	this->_value = _value;
			}

			 NumberJsonVar(const std::string & s)
		     : JsonVar("", JsonVarType::JSON_VAR_TYPE_NUMBER){
				 this->_value = parse(s);
			}

			 NumberJsonVar(const NumberJsonVar &_other)
			     : JsonVar(_other)
			     ,_value(_other._value) {
			 }

			// assign
			 NumberJsonVar &operator=(const NumberJsonVar &_other) {
			     if(this != &_other) {
			         _value = _other._value;
			     }

			     return *this;
			 }


			double getValue() const{
				return this->_value;
			}

			void setValue(double _value){
				this->_value = _value;
			}

			virtual void * getPtrValue(){ return &this->_value;}


			virtual ~NumberJsonVar(){}
	private:

		double _value = 0;

	};
}
