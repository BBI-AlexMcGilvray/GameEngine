#include "Data/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

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

		// following https://msdn.microsoft.com/en-us/library/sf98bd4y.aspx
		String GetCWD()
		{
			char* buffer;
			bool success = false;

			// Get the current working directory:   
			if ((buffer = _getcwd(NULL, 0)) == NULL)
			{
				std::cout << "Failed to get CWD" << std::endl;
			}
			else
			{
				success = true;
			}

			String cwd = buffer;

			if (success)
			{
				free(buffer);
			}
			
			std::cout << "CWD: " << cwd << std::endl;

			return cwd;
		}
	}
}