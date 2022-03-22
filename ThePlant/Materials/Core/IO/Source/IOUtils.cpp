#include "Core/IO/Headers/IOUtils.h"

#include <Windows.h>
#include <direct.h>
#include <stdio.h>
#include <stdlib.h>
#include <stringapiset.h>

#include "Core/Debugging/Headers/Macros.h"
#include "Core/Logging/LogFunctions.h"

namespace Core {
namespace IO {
  File OpenFileI(FilePath file)
  {
    File openedFile(file, std::ios::in);

    openedFile.Open();

    VERIFY(openedFile.FileStream.is_open(), "File <<" + file.GetFullPath() + ">> failed to open");

    return openedFile;
  }

  File OpenFileO(FilePath file)
  {
    File openedFile(file, std::ios::out);

    openedFile.Open();

    VERIFY(openedFile.FileStream.is_open(), "File <<" + file.GetFullPath() + ">> failed to open");

    return openedFile;
  }

  // following https://msdn.microsoft.com/en-us/library/sf98bd4y.aspx
  std::string GetCWD()
  {
    char *buffer;
    bool success = false;

    // Get the current working directory:
    if ((buffer = _getcwd(NULL, 0)) == NULL) {
      CORE_WARNING("IOUtils", "Failed to get CWD");
    } else {
      success = true;
    }

    std::string cwd = buffer + std::string("\\");

    if (success) {
      free(buffer);
    }

    CORE_WARNING("IOUTILS", "CWD: " + cwd);

    return cwd;
  }
}// namespace IO
}// namespace Core