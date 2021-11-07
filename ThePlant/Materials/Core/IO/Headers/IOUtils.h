#pragma once

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IODefs.h"

namespace Core {
namespace IO {
  File OpenFileI(FilePath file);
  File OpenFileO(FilePath file);

  std::string GetCWD();
}// namespace IO
}// namespace Core