#pragma once

#include "Core/Headers/Exception.h"

namespace Core {
namespace IO {
  struct IOException : Exception
  {
    using Exception::Exception;

    IOException(const std::string &error)
    : Exception(error)
    {}
  };

  struct EOFException : IOException
  {
    using IOException::IOException;

    EOFException(const std::string &error)
    : IOException(error)
    {}
  };
}// namespace IO
}// namespace Core