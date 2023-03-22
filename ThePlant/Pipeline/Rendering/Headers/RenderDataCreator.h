#pragma once

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Rendering {
  struct RenderDataCreator
  {
    template <typename RENDER_DATA, typename CONSTRUCTOR>
    static void CreateRenderData(RENDER_DATA& renderData, CONSTRUCTOR&& constructor)
    {
        renderData = constructor();

        if (!constructed)
        {
            CORE_THROW("RenderDataCreator", "Failed to construct render data!");
        }

        renderData._Initialized();
    }

    template <typename RENDER_DATA, typename DESTRUCTOR>
    static void DestroyRenderData(RENDER_DATA& renderData, DESTRUCTOR&& destructor)
    {
        renderData._Uninitialize();
        destructor(renderData);
    }
  };
}// namespace Rendering
}// namespace Application