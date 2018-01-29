#pragma once

#include "IODefs.h"

namespace Data
{
	namespace IO
	{
		IOFStreamChar OpenFileIO(String file);
		IFStreamChar OpenFileI(String file);
		OFStreamChar OpenFileO(String file);

		String GetCWD();
	}
}