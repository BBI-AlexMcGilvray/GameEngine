#include "Pipeline/Rendering/DisplayManager.h"

#include "Pipeline/Rendering/Display.h"

namespace Application {
namespace Rendering {
    Core::instanceId<IDisplayLayer> DisplayManager::AddDisplay(std::unique_ptr<IDisplayLayer> display)
    {
        Core::instanceId<IDisplayLayer> newDisplayId = Core::GetInstanceId<IDisplayLayer>();

        auto lock = _GetLock();
        _displays.push_back(std::make_pair(newDisplayId, std::move(display)));

        return newDisplayId;
    }

    void DisplayManager::RemoveDisplay(Core::instanceId<IDisplayLayer> displayId)
    {
        auto lock = _GetLock();
        for (auto iter = _displays.begin(); iter != _displays.end(); ++iter)
        {
            if (iter->first == displayId)
            {
                _displays.erase(iter);
                return;
            }
        }
    }

    void DisplayManager::Render(Renderer& renderer) const
    {
        auto lock = _GetLock();
        for (const auto& display : _displays)
        {
            display.second->Render(renderer);
        }
    }
    
    std::unique_lock<std::recursive_mutex> DisplayManager::_GetLock() const
    {
        return std::unique_lock(_mutex);
    }
} // namespace Application
} // namespace Rendering