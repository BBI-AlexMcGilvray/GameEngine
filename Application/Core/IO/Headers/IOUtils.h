#pragma once

#include "Core/IO/Headers/IODefs.h"
#include "Core/IO/Headers/File.h"

namespace Core
{
	namespace IO
	{
		File OpenFileI(FilePath file);
		File OpenFileO(FilePath file);

		String GetCWD();
	}
}