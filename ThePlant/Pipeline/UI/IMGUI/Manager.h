#pragma once

#include <unordered_map>
#include <memory>

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

    void Render();

    void End();
    void CleanUp();

    template <typename T, typename ...ARGS>
    Core::instanceId<Window> AddWindow(ARGS ...args)
    {
      SCOPED_MEMORY_CATEGORY("IMGUI");
      Core::instanceId<Window> newId = Core::GetInstanceId<Window>();

      _windows.emplace(std::make_pair(newId, std::make_unique<T>(std::forward<ARGS>(args)...)));

      return newId;
    }

    void RemoveWindow(const Core::instanceId<Window>& window)
    {
      _windows.erase(window);
    }

    private:
      const WindowManager& _window;
      const GLContextManager& _glContext;

      std::unordered_map<Core::instanceId<Window>, std::unique_ptr<Window>, Core::instanceIdHasher<Window>> _windows;

      void _RenderManager();
      void _RenderWindows();
  };
}// namespace IMGUI
}// namespace UI
}// namespace Application