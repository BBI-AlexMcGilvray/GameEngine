#include "Data/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Data
{
	namespace IO
	{
		IOFStreamChar OpenFileIO(String file)
		{
			IOFStreamChar openedFile(file);

			MESSAGE(openedFile.is_open(), "File <<" + file + ">> failed to open");

			return openedFile;
		}

		IFStreamChar OpenFileI(String file)
		{
			IFStreamChar openedFile(file);

			MESSAGE(openedFile.is_open(), "File <<" + file + ">> failed to open");

			return openedFile;
		}

		OFStreamChar OpenFileO(String file)
		{
			OFStreamChar openedFile(file);

			MESSAGE(openedFile.is_open(), "File <<" + file + ">> failed to open");

			return openedFile;
		}
	}
}