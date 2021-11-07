#pragma once

#include "Core/Headers/Exception.h"

namespace Core {
Exception::Exception()
  : Error("")
{}

Exception::Exception(const std::string &error)
  : Error(error)
{}

Exception::Exception(const Exception &exception)
  : Error(exception.GetError())
{}

std::string Exception::GetError() const
{
  return Error;
}
}// namespace Core