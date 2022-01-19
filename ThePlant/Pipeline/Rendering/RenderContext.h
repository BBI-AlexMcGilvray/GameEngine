#pragma once

#include <array>
#include <vector>

#include "Core/Headers/CoreDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Pipeline/Rendering/Material.h"
#include "Pipeline/Rendering/Mesh.h"

namespace Application {
namespace Rendering {
    enum class Mode { FILL, LINE };

    // not references because we can create contexts for each object on main thread, then pass them all to rendering thread without worrying aobut lifetime
    // though we will need a way to validate the mesh VAO and such are still valid?
    struct Context
    {
        const Material material;
        Core::Math::Float4x4 mvp; // may be modified by other things (ex: including the camera matrix)
        Core::Math::Color color; // may be modified by other things (ex: general render setting changing the color)
        const Mesh mesh;
        const Mode mode = Mode::FILL;

        bool operator==(const Context& other) const
        {
            return (material == other.material
                && mvp == other.mvp
                && color == other.color
                && mesh == other.mesh
                && mode == other.mode);
        }
    };

    struct SkinnedContext
    {
        Context context;
        const std::array<Core::Math::Float4x4, 50> bones; // currently cap the number of bones at 50, could make it a vector if we care about the space, but alignment/cache misses make array probably better

        bool operator==(const SkinnedContext& other) const
        {
            return (context == other.context
                && bones == other.bones);
        }
    };

    // maybe have this include the camera(s?) to use
    struct RenderFrame
    {
        std::vector<Context> contexts;
        std::vector<SkinnedContext> skinnedContexts;
    };
}// namespace Rendering
}// namespace Application