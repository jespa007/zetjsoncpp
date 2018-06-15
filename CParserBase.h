/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once



namespace zetjsoncpp{

	class CParserBase{
	protected:

		string filename;
		string m_error;



	public:
	  CParserBase(){}

	 virtual ~CParserBase(){}
	};

};

