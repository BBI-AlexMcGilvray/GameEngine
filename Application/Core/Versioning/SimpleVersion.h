#include <stdint.h>

#include "core/Versioning/Version.h"

namespace Core::Versioning
{
    struct SimpleVersion : IVersion<SimpleVersion>
    {
        SimpleVersion() = default;

        SimpleVersion(uint32_t version)
        : _version(version)
        {}

        SimpleVersion(const SimpleVersion& other)
        : _version(other._version)
        {}

        SimpleVersion& operator=(const SimpleVersion& other)
        {
            _version = other._version;
            return *this;
        }

    protected:
        uint32_t _version;

        friend struct IVersion<SimpleVersion>;

        bool Equals(const SimpleVersion& other) const
        {
            return (_version == other._version);
        }

        bool LessThan(const SimpleVersion& other) const
        {
            return (_version < other._version);
        }
    };
}