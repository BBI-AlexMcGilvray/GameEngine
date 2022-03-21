#include "Core/Debugging/Memory/MemoryTracker.h"

namespace Core
{
namespace Memory
{
#if DEBUG
Ptr<void> MemoryTracker::Allocate(size_t size)
{
    size_t allocatedSize = size + sizeof(MemoryHeader);
    
    Ptr<void> allocated = malloc(allocatedSize);
    if (allocated == nullptr)
    {
        throw std::bad_alloc();
    }

    {   // make sure category name exists and is mapped to id
        const auto lock = std::lock_guard(_mutex);
        if (_categoryToId.find(current_category) == _categoryToId.end())
        {
            _categoryToId.emplace(current_category, ++_currentId);
        }
        _currentId = _categoryToId[current_category];
    }
    
    MemoryHeader* header = static_cast<MemoryHeader*>(allocated);
    MemoryHeader headerInfo(_currentId, size);
    memcpy(header, &headerInfo, sizeof(MemoryHeader));

    {   // create and update category info
        const auto lock = std::lock_guard(_mutex);
        if (_categories.find(_currentId) == _categories.end())
        {
            _categories.emplace(_currentId, CategoryInfo(_currentId));
        }
        CategoryInfo& info = _categories[_currentId];
        info.size += size;
        info.count += 1;
    }

    Ptr<void> requested = static_cast<Ptr<void>>(header + 1); // this is wrong somehow... returning the malloc'd pointer and freeing that works...

    if (requested == nullptr)
    {
        throw std::bad_alloc();
    }

    return requested;
}

void MemoryTracker::Deallocate(Ptr<void> memory)
{
    MemoryHeader* header = static_cast<MemoryHeader*>(memory) - 1;
    try
    {
        const auto lock = std::lock_guard(_mutex);
        CategoryInfo& info = _categories[header->categoryId];
        info.size -= header->size;
        info.count -= 1;
    }
    catch(...) // we accessed invalid memory
    {
        // deallocating memory that doesn't have a header
        free(memory);
        return;
    }
    
    if (header->flag != std::numeric_limits<uint8_t>::max()) // wasn't made by us?
    {
        // deallocating memory that doesn't seem to be made by up
        free(memory);
        return;
    }

    free(header); // deleting the whole block from the header
}

const std::string MemoryTracker::Info()
{
    SCOPED_MEMORY_CATEGORY("info");
    const auto lock = std::lock_guard(_mutex);

    std::string info = "";

    const auto categoryCopy = _categories;
    for (const auto& category : categoryCopy)
    {
        bool found = false;
        for (const auto& mapping : _categoryToId)
        {
            if (mapping.second == category.second.categoryId)
            {
                found = true;
                info += std::string(mapping.first) + ": " + std::to_string(category.second.size) + " (" + std::to_string(category.second.count) + ")";
                info += '\n';
                break;
            }
        }

        if (!found)
        {
            info += "[ERROR] UNKOWN ID: " + std::to_string(category.second.size) + " (" + std::to_string(category.second.count) + ")";
            info += '\n';
        }
    }

    return info;
}
#endif
} // namespace Memory
} // namespace Core