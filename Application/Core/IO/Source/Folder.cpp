#include "Core/IO/Headers/Folder.h"

/*
Need to figure out how we want to split this for different operating systems. Maybe the standard
has a better way to do this.

Or, we don't need to care since directory CREATION will only happen when creating data.
The game running itself should only ever be READING from already created directories.
*/
#include <Windows.h>

namespace Core
{
	namespace IO
	{
		CreateFolderResult CreateFolder(String path)
		{
			if (path.empty())
			{
				return CreateFolderResult::Error;
			}

			if (FolderExists(path))
			{
				return CreateFolderResult::AlreadyExists;
			}

			auto codePage = GetACP();
			int sz = MultiByteToWideChar(codePage, 0, &path[0], (int)path.size(), 0, 0);
			wstring wPath(sz, 0);
			MultiByteToWideChar(codePage, 0, &path[0], (int)path.size(), &wPath[0], sz);

			if (CreateDirectory(wPath.c_str(), nullptr))
			{
				return CreateFolderResult::Created;
			}
			return CreateFolderResult::Error;
		}

		bool FolderExists(String path)
		{
			auto fileAttributes = GetFileAttributesA(path.c_str());

			if (fileAttributes == INVALID_FILE_ATTRIBUTES)
			{
				return false;
			}
			else if (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				return true;
			}
			return false;
		}
	}
}