namespace zetjsoncpp{

	// ARRAY FLOAT
	template<char chr1 = 'a', char chr2 = 'b', char... _T_NAME>
	class CParserVarNumberArray : public CParserVarNamed<chr1, chr2, _T_NAME...>, public CDinamicVector<float> {
		short * shortBuf;
		float * floatBuf;

	public:
		//_T_NAME name;
		CParserVarNumberArray() {
			this->_m_iType = CParserVar::TYPE_ARRAY_NUMBER;
			this->size_data = sizeof(CParserVarNumberArray<chr1, chr2, _T_NAME...>);
			this->p_data = &this->vec_data;
			shortBuf=NULL;
			floatBuf=NULL;
		}

		void add(float s) {
			((std::vector<float> *)this->p_data)->push_back(s);
		}

		virtual std::string & getStrValue(int ident, uint32_t flags = 0) {
			//this->str_value ="";
			bool not_minimized = ((flags & CParserVar::PROPERTY_STR_MINIMIZED) == 0);
			std::vector<float> * v = (std::vector<float> *)this->p_data;
			this->str_value = "";
			std::string m_sfValue;
			for (int k = 0; k <= (ident + 1); k++)
				this->str_value = this->str_value + "\t";

			for (unsigned j = 0; j < v->size(); j++) {

				if (j > 0){
					this->str_value = this->str_value + ",";
				}

				m_sfValue = zj_string_utils::float2str(v->at(j));

				this->str_value = this->str_value + "" + m_sfValue + " ";

				if (not_minimized) {
					if (j != 0 && ((j%N_ELEMENTS_JSON_ARRAY_PRINT) == 0)) {
						for (int k = 0; k <= (ident + 1); k++)
							this->str_value = this->str_value + "\t";
						this->str_value += "\n";
					}
				}

			}
			return this->str_value;
		}

		float *getFloatBuffer(size_t & length) {

			if(floatBuf == NULL){
				floatBuf = new float[vec_data.size()];

				for (unsigned i = 0; i < vec_data.size(); i++){
					floatBuf[i]=vec_data[i];
				}
			}

			length=vec_data.size();
			return floatBuf;
		}


		short *getShortBuffer(size_t & length) {

			if(shortBuf == NULL){

				short * shortBuf = new short[vec_data.size()];
				for (unsigned i = 0; i < vec_data.size(); i++){
					shortBuf[i]=vec_data[i];
				}
			}

			length = vec_data.size();
			return shortBuf;
		}


		//virtual ~CParserVarNumberArray(){}
		virtual ~CParserVarNumberArray() {
			if (floatBuf!=NULL)
				free(floatBuf);

			if (shortBuf!=NULL)
				free(shortBuf);


		}
	};
}
