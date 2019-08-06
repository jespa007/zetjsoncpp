#pragma once

namespace zetjsoncpp
{
	namespace io{
		bool file_exists(const string & m_file) ;
		char * read_file(const string & filename, bool end_string_char=true);
		int  get_file_length(const  string  & file);
	}

}
