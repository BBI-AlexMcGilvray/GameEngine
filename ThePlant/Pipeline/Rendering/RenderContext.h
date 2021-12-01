#pragma once

#include <array>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/Material_NEW.h"
#include "Pipeline/Rendering/Mesh_NEW.h"

namespace Application {
namespace Rendering {
    // not references because we can create contexts for each object on main thread, then pass them all to rendering thread without worrying aobut lifetime
    // though we will need a way to validate the mesh VAO and such are still valid?
    struct Context
    {
        const Material_NEW material;
        const Core::Math::Float4x4 mvp;
        const Core::Math::Color color;
        const Mesh_NEW mesh;
    };

    struct SkinnedContext
    {
        Context context;
        std::array<Core::Math::Float4x4, 50> bones; // currently cap the number of bones at 50, could make it a vector if we care about the space, but alignment/cache misses make array probably better
    };
}// namespace Rendering
}// namespace Application