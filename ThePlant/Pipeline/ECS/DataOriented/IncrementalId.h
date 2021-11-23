#pragma once

#include <cstdint>

struct IncrementalId;
IncrementalId GetIncrementalId();

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