#pragma once

#include <mutex>
#include <string>

#include "Core/Headers/PtrDefs.h"
#include "Core/Debugging/Memory/InternalUtils/Utils.h"

#include <iostream>

// testing
#include "Core/Threading/Thread.h"

namespace Core
{
namespace Memory
{
class MemoryTracker
{
private:
    static constexpr inline size_t _ERROR_ID = 0;
    static inline std::atomic<int> unaccounted_allocations = 0;

    static inline std::atomic<uint64_t> allocationIndex = 0; // testing

    struct MemoryHeader
    {
        const uint64_t allocation; // testing
        const size_t categoryId;
        const size_t size;
        const uint8_t flag = static_cast<uint8_t>(0) - 1; // not using numeric_limits because max() is a windows macro and conflicts

        MemoryHeader(const size_t& categoryId, const size_t& size)
        : categoryId(categoryId)
        , size(size)
        , allocation(++allocationIndex) // testing
        {}
    };

    struct CategoryInfo
    {
        size_t size = 0;
        size_t highWatermark = 0;
        size_t count = 0;
        const size_t categoryId;

        CategoryInfo()
        : categoryId(_ERROR_ID)
        {}

        CategoryInfo(const size_t& categoryId)
        : categoryId(categoryId)
        {}

        CategoryInfo(const CategoryInfo&) = default;
        CategoryInfo(CategoryInfo&&) = default;
        CategoryInfo& operator=(const CategoryInfo&) = default;
        CategoryInfo& operator=(CategoryInfo&&) = default;
    };

    /*
    if we want this to be tracked per-thread, threads need to check for this service and register/deregister their categories (by ref) to a single point of truth
    this way, threads do not need to lock to create/delete memory and are only locked when we get a snap-shot of the current memory
    */
    static inline size_t _currentId = _ERROR_ID;
    std::recursive_mutex _mutex; // to make sure the categories are not raced across threads
    UntrackedMap<size_t, CategoryInfo> _categories; // can't be thread local as we want all info in one place (?)
    UntrackedMap<UntrackedString, size_t> _categoryToId;

public:
    // thread local to avoid even MORE lock contention
    thread_local static inline UntrackedString current_category = "unknown";

    ~MemoryTracker()
    {
        // testing
        /*
        NOTE: not sure why there are allocations unaccounted for. maybe when the parent object is destroyed the destructors are optimized out and just ignored?
            overall this issue (exception on game end) seems like it can just be ignored for now...
        */
        // i think this should be 0 for everything before this is destroyed...
        for (const auto& category : _categories)
        {
            if (category.second.count != 0)
            {
                for (const auto& map : _categoryToId)
                {
                    if (map.second == category.first)
                    {
                        std::cout << "MemoryTracker: " << std::string(map.first) + " has " + std::to_string(category.second.count) + " allocations totalling " + std::to_string(category.second.size) << '\n';
                        break;
                    }
                }
            }
        }
        if (unaccounted_allocations != 0)
        {
            std::cout << "MemoryTracker: " << std::to_string(unaccounted_allocations) << " unaccounted allocations" << '\n';
        }
        // \testing
    }

    Ptr<void> Allocate(size_t size);
    void Deallocate(Ptr<void> memory);

    const std::string Info();
};

class ScopedMemoryCategory
{
    public:
        ScopedMemoryCategory(const UntrackedString& category)
        : _previousCategory(MemoryTracker::current_category)
        {
            MemoryTracker::current_category = category;
        }

        ~ScopedMemoryCategory()
        {
            MemoryTracker::current_category = _previousCategory;
        }

    private:
        const UntrackedString _previousCategory;
};
} // namespace Memory
} // namespace Core