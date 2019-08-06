#include "zetjsoncpp.h"

namespace zetjsoncpp
{
	namespace path{
		
			string  get_filename(const string & _filename) {
				size_t found;
				string ss = _filename;
				found = _filename.find_last_of("/\\");
				if ((int)found != -1)
					ss = _filename.substr(found + 1);
				return ss;
			}
	}
}
