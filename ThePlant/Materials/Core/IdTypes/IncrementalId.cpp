#include "Core/IDTypes/IncrementalId.h"

namespace Core {
namespace
{
    constexpr uint64_t INVALID_ID = 0u;
    static uint64_t next_id = 1u;
}

IncrementalId::IncrementalId()
: _id(INVALID_ID)
{}

IncrementalId::IncrementalId(const IncrementalId& rhs)
: _id(rhs._id)
{}

IncrementalId& IncrementalId::operator=(const IncrementalId& other)
{
    _id = other._id;
    return *this;
}

bool IncrementalId::IsValid() const
{
    return _id != INVALID_ID;
}

bool IncrementalId::operator==(const IncrementalId& other) const
{
    return _id == other._id;
}

bool IncrementalId::operator!=(const IncrementalId& other) const
{
    return !(*this == other);
}

IncrementalId::IncrementalId(Constructor tag)
: _id(next_id++)
{}

IncrementalId GetIncrementalId()
{
    return IncrementalId(IncrementalId::Constructor::TAG);
}
}// namespace Core
