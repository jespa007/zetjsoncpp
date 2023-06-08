#include "zetjsoncpp.h"

namespace zetjsoncpp
{
	std::string  path_utils::getFilename(const std::string & _filename) {
		size_t found;
		std::string ss = _filename;
		found = _filename.find_last_of("/\\");
		if ((int)found != -1)
			ss = _filename.substr(found + 1);
		return ss;
	}
}
