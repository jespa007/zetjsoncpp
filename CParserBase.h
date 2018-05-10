/*
 * CbaseParser.h
 *
 *  Created on: Jul 5, 2014
 *      Author: jespada
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

