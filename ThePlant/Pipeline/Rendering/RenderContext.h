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
        const size_t vertices;
        const Mesh_NEW mesh;
    };

    struct SkinnedContext
    {
        Context context;
        std::array<Core::Math::Float4x4, 50> bones;
    };
}// namespace Rendering
}// namespace Application