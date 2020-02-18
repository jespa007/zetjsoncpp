/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once



namespace zetjsoncpp{

	class CParserBase{
	public:
	  CParserBase(){}

	 virtual ~CParserBase(){}

	protected:

		std::string filename;
		std::string error;

		void writeError(const char *file, int line, const char *start_str, char *current_ptr, const char *string_text, ...);
		void writeWarning(const char *file, int line,bool ignore_warnings, const char *string_text, ...);

	};

};

