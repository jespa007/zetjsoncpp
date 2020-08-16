#include "zetjsoncpp.h"

namespace zetjsoncpp
{
	namespace zj_file{

		bool exists(const std::string & m_file) {

			if (zj_strutils::ends_with(m_file, "/"))
				return false;

			if (m_file == "")
				return false;

			struct stat buffer;
			return (stat(m_file.c_str(), &buffer) == 0);

		}

		char * read(const std::string & filename, bool end_string_char){

			int  file_length, readed_elements;
				FILE  *fp;
				int with_end_char=0;

				if(end_string_char){
					with_end_char=1;
				}

				if((fp  =  fopen(filename.c_str(),"rb"))  !=  NULL)
				{
					if((file_length = length(filename)) != -1) {


						char *buffer = (char *)malloc (file_length+with_end_char);
						memset(buffer,0,file_length+with_end_char );
						readed_elements = fread(buffer, 1, file_length, fp);

						if(readed_elements != file_length) {
							//fprintf(stderr,"number elements doesn't match with length file (%s)\n",filename.c_str());
							free(buffer);

							throw std::runtime_error("number elements doesn't match with length file ("+filename+")");

						}

						//ByteBuffer *ch = new ByteBuffer(buffer, file_length+with_end_char);

						//delete [] buffer;

						fclose(fp);

						return buffer;
					}
					else  throw std::runtime_error("I can't read file \""+filename+"\"");
				}
				else  throw std::runtime_error("I can't open file \""+filename+"\"");



				return NULL;
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
