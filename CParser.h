#pragma once

namespace json2cpp {

	template<typename _T>
	class CParser : public CBaseParser {

	protected:

		CParserVarArrayPropertyGroup<_T> * root_struct_field;
		const char *m_filesrc;
		int m_line;


	public:



		CParser() {
			m_filesrc = NULL;
			m_line = 0;
			root_struct_field = new CParserVarArrayPropertyGroup<_T>;
		}



		virtual bool evalString(const string & m_expression, int level = 0, bool ignore_warnings =
			false) = 0;

		virtual bool evalFile(const string & m_filename, bool ignore_warnings =
			false) {

			bool ok = false;
			m_filesrc = m_filename.c_str();

			ByteBuffer *buf = readFile(m_filename);
			if (buf != NULL) {
				ok = (evalString((char *)buf->data_buffer, 0, ignore_warnings) > 0);
				delete buf;
			}


			return ok;
		}

		CParserVarArrayPropertyGroup<_T> *getData() {
			return root_struct_field;
		}

		virtual ~CParser() {
			if (root_struct_field != NULL) {
				delete root_struct_field;
			}
			root_struct_field = NULL;
		}

	};

};
