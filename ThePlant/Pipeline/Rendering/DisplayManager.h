#pragma once

#include <memory>
#include <mutex>
#include <utility>

#include "Core/IdTypes/InstanceId.h"

#include "Pipeline/Rendering/Display.h"
#include "Pipeline/Rendering/Renderer.h"

namespace Application {
namespace Rendering {
    class DisplayManager
    {
        public:
            DisplayManager() = default;

            template <typename DISPLAY_LAYER, typename ...ARGS>
            Core::instanceId<IDisplayLayer> AddDisplay(ARGS&& ...args)
            {
                return AddDisplay(std::make_unique<DISPLAY_LAYER>(std::forward<ARGS>(args)...));
            }

            Core::instanceId<IDisplayLayer> AddDisplay(std::unique_ptr<IDisplayLayer> display);
            // in the future, we may want this to return the unique_ptr so we can remove inactive displays while optionally maintinaing state
            void RemoveDisplay(Core::instanceId<IDisplayLayer> displayId);

            void Render(Renderer& renderer) const;

        protected:
            mutable std::recursive_mutex _mutex;
            std::vector<std::pair<Core::instanceId<IDisplayLayer>, std::unique_ptr<IDisplayLayer>>> _displays;
            
            std::unique_lock<std::recursive_mutex> _GetLock() const;
    };
} // namespace Application
} // namespace Rendering