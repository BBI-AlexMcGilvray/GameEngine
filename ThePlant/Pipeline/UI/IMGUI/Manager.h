#pragma once

#include <unordered_map>
#include <memory>
#include <mutex>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"

#include "Core/IdTypes/InstanceId.h"

#include "Pipeline/Headers/WindowManager.h"
#include "Pipeline/Headers/GLContextManager.h"
#include "Pipeline/UI/IMGUI/Window.h"

namespace Application {
namespace UI {
namespace IMGUI {
  class Manager
  {
    public:
    Manager(const WindowManager& window, const GLContextManager& glContext);

    Manager(Manager&&) = default;
    Manager& operator=(Manager&&) = default;

    Manager(const Manager&) = delete;
    Manager& operator=(const Manager&) = delete;

    void Initialize();
    void Start();

    void End();
    void CleanUp();

    template <typename T, typename ...ARGS>
    Core::instanceId<Window> AddWindow(ARGS&& ...args)
    {
      SCOPED_MEMORY_CATEGORY("IMGUI");
      Core::instanceId<Window> newId = Core::GetInstanceId<Window>();

      std::unique_lock<std::recursive_mutex> lock(_mutex);
      _windows.emplace(std::make_pair(newId, std::make_unique<T>(std::forward<ARGS>(args)...)));

      return newId;
    }

    template <typename T>
    T& GetWindow(Core::instanceId<Window> window)
    {
      // should we have a DEBUG only dynamic_cast check to catch issues?
      return static_cast<T&>(GetWindow(window));
    }

    Window& GetWindow(Core::instanceId<Window> window)
    {
      std::unique_lock<std::recursive_mutex> lock(_mutex); // this may not need to be locked as it is a get only, not a modification of _windows
      return *(_windows[window]);
    }

    // will lock while gathering references, but outside of that scope be sure to call LockWindows and UnlockWindows
    std::vector<std::reference_wrapper<Window>> GetAllWindows();

    // can't do this currently, removing windows will cause the references returned by GetAllWindows() to break
    // void RemoveWindow(const Core::instanceId<Window>& window)
    // {
    //   std::unique_lock<std::recursive_mutex> lock(_mutex);
    //   _windows.erase(window);
    // }

    std::unique_lock<std::recursive_mutex> LockWindows();
    void UnlockWindows(std::unique_lock<std::recursive_mutex>&& lock);

    private:
      const WindowManager& _window;
      const GLContextManager& _glContext;

      std::unordered_map<Core::instanceId<Window>, std::unique_ptr<Window>, Core::instanceIdHasher<Window>> _windows;
      // since the rendering thread is separate, we may gets hitches when trying to add/remove due to it being locked up more frequently (something to watch out for)
      mutable std::recursive_mutex _mutex; // for some reason _mutex being placed above _windows causes issued (race conditions or something...)
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application