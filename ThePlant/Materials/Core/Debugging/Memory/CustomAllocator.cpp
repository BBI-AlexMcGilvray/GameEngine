#include <new>

#include "Core/Debugging/Memory/MemoryTracker.h"
#include "Core/Headers/Service.h"
#include "Core/Logging/LogFunctions.h"

/******************
 * NOTE: THIS IS INCLUDED BY DEFAULT BY BEING A .cpp FILE AND BEING LINKED TO
******************/

// References:
/*
- new operator: https://en.cppreference.com/w/cpp/memory/new/operator_new
- delete operator: https://en.cppreference.com/w/cpp/memory/new/operator_delete
*/

// NOT namespaced because operators must be in highest scope
// and not wrapping in any Core::Ptr<> types to enforce that this is very specific

// not implementing an over-aligned overload as it shouldn't be needed for our purposes
// that means any calls from this will not be tracked
/*
[[nodiscard]] void* operator new(size_t size, std::align_van_t alignment);
*/

[[nodiscard]] void* operator new(size_t size)
{
    WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
    (
        return service->Allocate(size);
    )
    return malloc(size);
}

[[nodiscard]] void* operator new[](size_t size)
{
    WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
    (
        return service->Allocate(size);
    )
    return malloc(size);
}

// not implementing an over-aligned overload as it shouldn't be needed for our purposes
/*
void operator delete(void* memory, std::align_val_t alignment)
*/

void operator delete(void* memory)
{
    WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
    (
        service->Deallocate(memory);
        return;
    )
    free(memory);
}

void operator delete[](void* memory)
{
    WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
    (
        service->Deallocate(memory);
        return;
    )
    free(memory);
}

// apparently need the below, though this should not be required as-per the standard...
void operator delete(void* memory, size_t size)
{
    WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
    (
        service->Deallocate(memory);
        return;
    )
    free(memory); // why does this throw issues?
}

void operator delete[](void* memory, size_t size)
{
    WITH_DEBUG_SERVICE(Core::Memory::MemoryTracker)
    (
        service->Deallocate(memory);
        return;
    )
    free(memory);
}