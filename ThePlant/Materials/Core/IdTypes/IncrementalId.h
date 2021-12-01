#pragma once

#include <cstdint>

namespace Application {
struct IncrementalId;
IncrementalId GetIncrementalId();

// all ids increment the hidden counter, regardless of what it is used for - each is unique (unless there is overflow)
struct IncrementalId
{
    friend IncrementalId GetIncrementalId();

    IncrementalId();
    IncrementalId(const IncrementalId& rhs);
    IncrementalId& operator=(const IncrementalId& other);

    bool operator==(const IncrementalId& other) const;
    bool operator!=(const IncrementalId& other) const;

    // explicit operator const uint64_t() const { return _id; }

protected:
    enum class Constructor { TAG };
    IncrementalId(Constructor tag);

private:
    uint64_t _id;
};
}// namespace Application
