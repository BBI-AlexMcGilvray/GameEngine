#pragma once

#include "Core/Debugging/Headers/Declarations.h"
#include "Core/Debugging/Memory/MemoryTracker.h"

#if DEBUG
#define SCOPED_MEMORY_CATEGORY(CATEGORY) Core::Memory::ScopedMemoryCategory _scoped_memory_category(CATEGORY)
#else
#define SCOPED_MEMORY_CATEGORY(CATEGORY)
#endif