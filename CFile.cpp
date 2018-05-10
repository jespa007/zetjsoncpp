//    This file is part of zetjsoncpp.
//
//    zetjsoncpp is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.

//    zetjsoncpp is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.

//    You should have received a copy of the GNU General Public License
//    along with zetjsoncpp.  If not, see <http://www.gnu.org/licenses/>.


#include "zetjsoncpp.h"


namespace zetjsoncpp {

	bool fileExists(const string & m_file) {

		if (endsWith(m_file, "/"))
			return false;

		if (m_file == "")
			return false;

		struct stat buffer;
		return (stat(m_file.c_str(), &buffer) == 0);

	}

	ByteBuffer * readFile(const string & filename, bool end_string_char){

		int  file_length, readed_elements;
			FILE  *fp;
			int with_end_char=0;

			if(end_string_char){
				with_end_char=1;
			}

			if((fp  =  fopen(filename.c_str(),"rb"))  !=  NULL)
			{
				if((file_length = getLengthFile(filename)) != -1) {


					unsigned char *buffer = new unsigned char [file_length+with_end_char];
					memset(buffer,0,file_length+with_end_char );
					readed_elements = fread(buffer, 1, file_length, fp);

					if(readed_elements != file_length) {
						fprintf(stderr,"number elements doesn't match with length file (%s)\n",filename.c_str());
						delete  buffer;
						return NULL;
					}

					ByteBuffer *ch = new ByteBuffer(buffer, file_length+with_end_char);

					delete [] buffer;

					fclose(fp);

					return ch;
				}
				else  fprintf(stderr,"I can't read file \"%s\"\n",filename.c_str());
			}
			else  fprintf(stderr,"I can't open file \"%s\"\n",filename.c_str());


			return NULL;
	}


	int  getLengthFile(const  string  & file)
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

	string  extractFile(const string & _filename) {
		size_t found;
		string ss = _filename;
		found = _filename.find_last_of("/\\");
		if ((int)found != -1)
			ss = _filename.substr(found + 1);
		return ss;
	}

};
