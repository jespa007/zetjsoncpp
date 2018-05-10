/*
 * CbaseParser.h
 *
 *  Created on: Jul 5, 2014
 *      Author: jespada
 */

#pragma once

namespace json2cpp{

	class CBaseParser{
	protected:

		string filename;
		string m_error;



	public:
	  CBaseParser(){}

	 virtual ~CBaseParser(){}
	};

};

