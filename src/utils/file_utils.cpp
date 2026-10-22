#include "zetjsoncpp.h"

namespace zetjsoncpp
{

	namespace file_utils{

		bool exists(const std::string & m_file) {

			if (string_utils::endsWith(m_file, "/"))
				return false;

			if (m_file == "")
				return false;

			struct stat buffer;
			return (stat(m_file.c_str(), &buffer) == 0);

		}

		std::string read_text(const std::string &_filename) {

		    std::ifstream file(_filename, std::ios::binary | std::ios::ate);

		    if(!file.is_open()) {
		        throw std::runtime_error("Cannot open file \"" + _filename + "\"");
		    }

		    std::streampos file_length = file.tellg();

		    if(file_length < 0) {
		        throw std::runtime_error("Cannot get file size \"" + _filename + "\"");
		    }

		    std::string result(static_cast<size_t>(file_length), '\0');

		    file.seekg(0, std::ios::beg);

		    if(!result.empty()) {
		        file.read(&result[0], static_cast<std::streamsize>(result.size()));

		        if(!file) {
		            throw std::runtime_error("Cannot read file \"" + _filename + "\"");
		        }
		    }

		    return result;
		}


		int  length(const  std::string  & file)
		{
			int  ini, end;
			FILE  *fp;

			if ((fp = fopen(file.c_str(), "rb")) != NULL)
			{

				fseek(fp, 0, SEEK_SET);
				ini = ftell(fp);
				fseek(fp, 0, SEEK_END);
				end = ftell(fp);

				fclose(fp);

				return  (end - ini);

			}

			return    -1;
		}

	}
}
