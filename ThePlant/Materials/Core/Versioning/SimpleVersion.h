#pragma once

#include "core/Versioning/Version.h"
#include <stdint.h>

namespace Core::Versioning {
struct SimpleVersion : IVersion<SimpleVersion>
{
  SimpleVersion() = default;

  SimpleVersion(uint32_t version)
    : _version(version)
  {}

  SimpleVersion(const SimpleVersion &other)
    : _version(other._version)
  {}

  SimpleVersion &operator=(const SimpleVersion &other)
  {
    _version = other._version;
    return *this;
  }

protected:
  uint32_t _version;

  friend struct IVersion<SimpleVersion>;

  bool Equals(const SimpleVersion &other) const
  {
    return (_version == other._version);
  }

  bool LessThan(const SimpleVersion &other) const
  {
    return (_version < other._version);
  }
};
}// namespace Core::Versioning