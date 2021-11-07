#pragma once

#include <exception>
#include <string>

#include "Core/Headers/CoreDefs.h"

namespace Core {
struct Exception : std::exception
{
  Exception();
  Exception(const std::string &error);
  Exception(const Exception &exception);

  std::string GetError() const;

private:
  const std::string Error;
};
}// namespace Core