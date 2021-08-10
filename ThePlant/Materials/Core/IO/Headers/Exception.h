#pragma once

#include "Core/Headers/Exception.h"

namespace Core {
namespace IO {
  struct IOException : Exception
  {
    using Exception::Exception;

    IOException(const String &error)
    : Exception(error)
    {}
  };

  struct EOFException : IOException
  {
    using IOException::IOException;

    EOFException(const String &error)
    : IOException(error)
    {}
  };
}// namespace IO
}// namespace Core