#include "zetjsoncpp.h"

namespace zetjsoncpp
{
	namespace path{
		
			std::string  get_filename(const std::string & _filename) {
				size_t found;
				std::string ss = _filename;
				found = _filename.find_last_of("/\\");
				if ((int)found != -1)
					ss = _filename.substr(found + 1);
				return ss;
			}
	}
}
