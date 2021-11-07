#pragma once

#include <fstream>
#include <ios>
#include <sstream>
#include <string>

#include "Core/Headers/CoreDefs.h"
#include "Core/IO/Headers/Exception.h"

namespace Core {
namespace IO {
  // files
  template<typename charT>
  using IFStream = std::basic_ifstream<charT>;
  template<typename charT>
  using OFStream = std::basic_ofstream<charT>;
  template<typename charT>
  using FStream = std::basic_fstream<charT>;

  // strings
  template<typename charT>
  using ISStream = std::basic_ostringstream<charT>;
  template<typename charT>
  using OSStream = std::basic_istringstream<charT>;
  template<typename charT>
  using SStream = std::basic_stringstream<charT>;

  // specializations
  using IFStreamChar = IFStream<char>;
  using OFStreamChar = OFStream<char>;
  using IOFStreamChar = FStream<char>;

  using ISStreamChar = ISStream<char>;
  using OSStreamChar = OSStream<char>;
  using IOSStreamChar = SStream<char>;

  // misc
  using StreamPos = std::streampos;

  using OpenMode = std::ios::openmode;

  enum class Endian {
    Big,
    Little
  };

  struct FilePath
  {
    std::string Path;
    std::string File;

    std::string GetFullPath() const
    {
      return (Path + File);
    }
  };

  inline constexpr bool HasPermission(OpenMode userPermissions, OpenMode permission)
  {
    return ((userPermissions & permission) > 0);
  }
}// namespace IO
}// namespace Core