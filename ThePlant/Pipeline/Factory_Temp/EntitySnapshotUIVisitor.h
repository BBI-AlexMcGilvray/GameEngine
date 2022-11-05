#pragma once

#include "Core/Headers/Factory.h"
#include "Core/IdTypes/RuntimeId.h"
#include "Core/Reflection/Reflectable.h"

#include "Pipeline/ECS/DataOriented/TemporaryComponentRef.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"
#include "Pipeline/Factory_Temp/UICreator.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"

// testing
// these shouldn't be here because we are just testing stuff
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

// these shouldn't be here because they should be registered elsewhere
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"
// \testing

namespace Editor {
namespace UI {
namespace IMGUI {
using TemporaryComponentRefUIFactory = Core::TypeFactory<void, Application::ITemporaryComponentRef&>;

// where would these visitors be held? where would the registration be called?
class ComponentRefUI : TemporaryComponentRefUIFactory
{
    public:
    ComponentRefUI()
    {
        // registration needs to happen elsewhere

        /*
        This is printing the names of everything correctly, but we need to fix the visitor
            - to do that, we will need to handle all the different 'types' held by the components (ex: vector, quaternion, ...)
            - can definitely heaviliy reference how the json is done
            - maybe we can make it more generic to be used by both?
        */
        Register<Application::PositionComponent>();
        Register<Application::RotationComponent>();
        Register<Application::ScaleComponent>();
        Register<Application::WorldTransformComponent>();
        Register<Application::ColliderComponent>();
        Register<Application::RigidBodyComponent>();
    }

    // default UI for component - iterates over all reflectable variables
    template <typename T>
    void Register()
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
