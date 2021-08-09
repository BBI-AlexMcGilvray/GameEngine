#pragma once

#include "core/Versioning/Version.h"
#include <stdint.h>

namespace Core::Versioning {
struct SemanticVersion : public IVersion<SemanticVersion>
{
  SemanticVersion() = default;

  SemanticVersion(uint32_t major, uint32_t minor, uint32_t patch)
    : _major(major), _minor(minor), _patch(patch)
  {}

  SemanticVersion(const SemanticVersion &other)
    : _major(other._major), _minor(other._minor), _patch(other._patch)
  {}

  SemanticVersion &operator=(const SemanticVersion &other)
  {
    _major = other._major;
    _minor = other._minor;
    _patch = other._patch;

    return *this;
  }

protected:
  uint32_t _major;
  uint32_t _minor;
  uint32_t _patch;

  friend struct IVersion<SemanticVersion>;

  bool Equals(const SemanticVersion &other) const
  {
    return (_major == other._major && _minor == other._minor && _patch == other._patch);
  }

  bool LessThan(const SemanticVersion &other) const
  {
    if (_major < other._major) {
      return true;
    } else if (_major == other._major) {
      if (_minor < other._minor) {
        return true;
      } else if (_minor == other._minor) {
        if (_patch < other._patch) {
          return true;
        }
      }
    }
    return false;
  }
};
}// namespace Core::Versioning