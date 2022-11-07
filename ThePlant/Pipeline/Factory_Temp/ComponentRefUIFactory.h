#pragma once

#include "Core/Headers/Factory.h"
#include "Core/IdTypes/RuntimeId.h"
#include "Core/Reflection/Reflectable.h"

#include "Pipeline/ECS/DataOriented/TemporaryComponentRef.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/Factory_Temp/UICreator.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"

namespace Editor {
namespace UI {
namespace IMGUI {
using TemporaryComponentRefUIFactory = Core::TypeFactory<void, Application::ITemporaryComponentRef&>;

// where would these visitors be held? where would the registration be called?
class ComponentRefUIFactory : TemporaryComponentRefUIFactory
{
    public:
    ComponentRefUIFactory() = default;

    // default UI for component - iterates over all reflectable variables
    template <typename T>
    void DefaultRegister()
    {
        using base_type = TemporaryComponentRefUIFactory;
        base_type::Register(Core::GetTypeId<T>(), [](Application::ITemporaryComponentRef& componentRef)
        {
            T& component = componentRef.GetComponent<T>();

            std::string componentName = std::string(Core::TemplateTypeAsString<T>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                ui_creator<T>().CreateUI(component);
            }
        });
    }

    void Visit(const Application::EntitySnapshot& snapshot)
    {
        for (auto& component : snapshot.GetComponents())
        {
            Visit(*component);
        }
    }

    // should visitors be passed down by ref? should they be perfect-forwarded (&&)? probably, would support everything
    void Visit(Application::ITemporaryComponentRef& componentRef)
    {
        Create(componentRef.GetComponentType(), componentRef);
    }
};
}// namespace UI
}// namespace IMGUI
}// namespace Editor
