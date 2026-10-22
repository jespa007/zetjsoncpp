#pragma once

namespace zetjsoncpp
{
	namespace file_utils{
		bool exists(const std::string & m_file) ;
		std::string read_text(const std::string & filename);
		int  length(const  std::string  & file);
	}
}
