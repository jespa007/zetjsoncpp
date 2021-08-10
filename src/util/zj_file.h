#pragma once

namespace zetjsoncpp
{
	namespace zj_file{
		bool exists(const std::string & m_file) ;
		char * read(const std::string & filename, bool end_string_char=true);
		int  length(const  std::string  & file);
	}

}
