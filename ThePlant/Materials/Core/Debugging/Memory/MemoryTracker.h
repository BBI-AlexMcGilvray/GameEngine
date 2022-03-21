#pragma once

#include <mutex>
#include <string>

#include "Core/Headers/PtrDefs.h"
#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Memory/InternalUtils/Utils.h"

namespace Core
{
namespace Memory
{
#if DEBUG
class MemoryTracker
{
private:
    static constexpr inline size_t _ERROR_ID = 0;

    struct MemoryHeader
    {
        const size_t categoryId;
        const size_t size;
        const uint8_t flag = std::numeric_limits<uint8_t>::max();

        MemoryHeader(const size_t& categoryId, const size_t& size)
        : categoryId(categoryId)
        , size(size)
        {}
    };

    struct CategoryInfo
    {
        size_t size = 0;
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

    Ptr<void> Allocate(size_t size);
    void Deallocate(Ptr<void> memory);

    const std::string Info();
};

class ScopedMemoryCategory
{
    public:
        ScopedMemoryCategory(const UntrackedString& category)
        : _category(category)
        , _previousCategory(MemoryTracker::current_category)
        {
            MemoryTracker::current_category = _category;
        }

        ~ScopedMemoryCategory()
        {
            MemoryTracker::current_category = _previousCategory;
        }

    private:
        const UntrackedString _category;
        const UntrackedString _previousCategory;
};
#endif
} // namespace Memory
} // namespace Core

#if DEBUG
#define SCOPED_MEMORY_CATEGORY(CATEGORY) Core::Memory::ScopedMemoryCategory _scoped_memory_category(CATEGORY);
#else
#define SCOPED_MEMORY_CATEGORY(CATEGORY)
#endif