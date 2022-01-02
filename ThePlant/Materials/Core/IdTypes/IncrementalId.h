#pragma once

#include <cstdint>
#include <functional>

namespace Core {
struct IncrementalId;
IncrementalId GetIncrementalId();

template <>
struct ::std::hash<IncrementalId>;

// all ids increment the hidden counter, regardless of what it is used for - each is unique (unless there is overflow)
struct IncrementalId
{
    friend IncrementalId GetIncrementalId();

    friend struct ::std::hash<IncrementalId>;

    IncrementalId();
    IncrementalId(const IncrementalId& rhs);
    IncrementalId& operator=(const IncrementalId& other);

    bool IsValid() const;

    bool operator==(const IncrementalId& other) const;
    bool operator!=(const IncrementalId& other) const;

    bool operator<(const IncrementalId& other) const
    {
        return _id < other._id;
    }
    bool operator<=(const IncrementalId& other) const
    {
        return !(other < *this);
    }
    bool operator>(const IncrementalId& other) const
    {
        return !(*this <= other);
    }
    bool operator>=(const IncrementalId& other) const
    {
        return !(*this < other);
    }

    // explicit operator const uint64_t() const { return _id; }

protected:
    enum class Constructor { TAG };
    IncrementalId(Constructor tag);

private:
    uint64_t _id;
};
}// namespace Core

template <>
struct std::hash<Core::IncrementalId>
{
    size_t operator()(const Core::IncrementalId& id) const
    {
        return id._id;
    }
};
