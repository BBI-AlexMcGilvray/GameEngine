#pragma once

#include "Core/Logging/LogFunctions.h"

namespace Application {
namespace Rendering {
  struct RenderDataCreator
  {
    template <typename RENDER_DATA, typename INITIALIZER, typename ...ARGS>
    static void InitializeRenderData(RENDER_DATA&& renderData, INITIALIZER&& initializer, ARGS&& ...args)
    {
        initializer(std::forward<RENDER_DATA>(renderData), std::forward<ARGS>(args)...);

        // would be nice to have some type of check for here sanity (or do we leave it to the initializers?)
        // if (!constructed)
        // {
        //     CORE_THROW("RenderDataCreator", "Failed to construct render data!");
        // }

        renderData._Initialize();
    }

    template <typename RENDER_DATA, typename DESTRUCTOR, typename ...ARGS>
    static void DestroyRenderData(RENDER_DATA& renderData, DESTRUCTOR&& destructor, ARGS&& ...args)
    {
        renderData._Uninitialize();
        destructor(std::forward<RENDER_DATA>(renderData), std::forward<ARGS>(args)...);
    }
  };
}// namespace Rendering
}// namespace Application