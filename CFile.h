/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */


#pragma once


namespace zetjsoncpp{

	bool fileExists(const string & m_file) ;
	ZETJSONCPP_MODULE_EXPORT ByteBuffer * readFile(const string & filename, bool end_string_char=true);
	int  getLengthFile(const  string  & file);
	string extractFile(const string & _filename);

};




