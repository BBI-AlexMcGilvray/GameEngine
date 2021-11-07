#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IODefs.h"

namespace Core {
namespace IO {
  enum class CreateFolderResult {
    AlreadyExists,
    Created,
    Error
  };

  CreateFolderResult CreateFolder(std::string path);
  bool FolderExists(std::string path);

  // Functions to be done later:

  /*

		void DeleteFolder(string path
		void Clearfolder(string path);

		*/
}// namespace IO
}// namespace Core