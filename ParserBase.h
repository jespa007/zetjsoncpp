/*
 *  This file is distributed under the MIT License.
 *  See LICENSE file for details.
 */

#pragma once



namespace ZetJsonCpp{




	class CParserBase{
	protected:

		std::string filename;
		std::string m_error;



	public:
	  CParserBase(){}

	 virtual ~CParserBase(){}
	};

};
