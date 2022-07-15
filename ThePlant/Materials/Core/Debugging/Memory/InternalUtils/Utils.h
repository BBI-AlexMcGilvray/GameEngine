#pragma once

#include <unordered_map>

namespace Core
{
namespace Memory
{
template <typename T>
struct SimpleUntrackedAllocator
{
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef void* void_pointer;
    typedef const void* const_void_pointer;
    typedef T value_type;
    typedef size_t size_type;
    typedef size_t difference_type;

    // needed for some casting
    template <typename O>
    SimpleUntrackedAllocator(const SimpleUntrackedAllocator<O>&) {}

    SimpleUntrackedAllocator() = default;
    SimpleUntrackedAllocator(const SimpleUntrackedAllocator&) = default;
    SimpleUntrackedAllocator(SimpleUntrackedAllocator&&) = default;
    SimpleUntrackedAllocator& operator=(const SimpleUntrackedAllocator&) = default;
    SimpleUntrackedAllocator& operator=(SimpleUntrackedAllocator&&) = default;
    
    static pointer allocate(size_type size)
    {
        return static_cast<pointer>(malloc(size * sizeof(T)));
    }

    static void deallocate(pointer memory, size_type size)
    {
        free(memory);
    }
};

template <typename KEY, typename VALUE>
using UntrackedMap = std::unordered_map<KEY, VALUE, std::hash<KEY>, std::equal_to<KEY>, SimpleUntrackedAllocator<std::pair<const KEY, VALUE>>>;
using UntrackedString = std::basic_string<char, std::char_traits<char>, SimpleUntrackedAllocator<char>>;
} // namespace Memory
} // namespace Core