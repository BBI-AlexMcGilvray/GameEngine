#pragma once

#include "IODefs.h"

namespace Core
{
	namespace IO
	{
		enum class CreateFolderResult
		{
			AlreadyExists,
			Created,
			Error
		};

		CreateFolderResult CreateFolder(String path);
		bool FolderExists(String path);

		// Functions to be done later:

		/*

		void DeleteFolder(string path
		void Clearfolder(string path);

		*/
	}
}