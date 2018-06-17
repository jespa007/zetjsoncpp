/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once

namespace zetjsoncpp {

	template<typename _T>
	class CParser : public CParserBase {

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



		virtual void evalString(const string & m_expression, int level = 0, bool ignore_warnings =
			false) = 0;

		virtual void evalFile(const string & m_filename, bool ignore_warnings =
			false) {


			m_filesrc = m_filename.c_str();

			ByteBuffer *buf = CZetJsonCppUtils::readFile(m_filename);
			if (buf != NULL) {
				try{
					evalString((char *)buf->data_buffer, 0, ignore_warnings);
				}
				catch(zetjsoncpp::parse_error_exception & err){
					delete buf;
					throw err;
				}
				catch(zetjsoncpp::parse_warning_exception & wrn){
					delete buf;
					throw wrn;

				}
				delete buf;
			}
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
