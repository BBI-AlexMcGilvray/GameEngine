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
template <typename VISITOR>
using TemporaryComponentRefVisitorFactory = Core::TypeFactory<void, VISITOR, Application::ITemporaryComponentRef&>;

// where would these visitors be held? where would the registration be called?
template <typename VISITOR>
class ComponentRefVisitor : TemporaryComponentRefVisitorFactory<VISITOR>
{
    public:
    ComponentRefVisitor()
    {
        // registration needs to happen elsewhere
        // also, this can clearly be heavily templatized AND/OR macro'd

        /*
        This is printing the names of everything correctly, but we need to fix the visitor
            - to do that, we will need to handle all the different 'types' held by the components (ex: vector, quaternion, ...)
            - can definitely heaviliy reference how the json is done
            - maybe we can make it more generic to be used by both?
        */
        Register(Core::GetTypeId<Application::PositionComponent>(), [](VISITOR visitor, Application::ITemporaryComponentRef& componentRef)
        {
            Application::PositionComponent& component = componentRef.GetComponent<Application::PositionComponent>();

            std::string componentName = std::string(Core::TemplateTypeAsString<Application::PositionComponent>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                reflector::visit_all(component, visitor);
            }
        });
        Register(Core::GetTypeId<Application::RotationComponent>(), [](VISITOR visitor, Application::ITemporaryComponentRef& componentRef)
        {
            Application::RotationComponent& component = componentRef.GetComponent<Application::RotationComponent>();

            std::string componentName = std::string(Core::TemplateTypeAsString<Application::RotationComponent>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                reflector::visit_all(component, visitor);
            }
        });
        Register(Core::GetTypeId<Application::ScaleComponent>(), [](VISITOR visitor, Application::ITemporaryComponentRef& componentRef)
        {
            Application::ScaleComponent& component = componentRef.GetComponent<Application::ScaleComponent>();
            
            std::string componentName = std::string(Core::TemplateTypeAsString<Application::ScaleComponent>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                reflector::visit_all(component, visitor);
            }
        });
        Register(Core::GetTypeId<Application::WorldTransformComponent>(), [](VISITOR visitor, Application::ITemporaryComponentRef& componentRef)
        {
            Application::WorldTransformComponent& component = componentRef.GetComponent<Application::WorldTransformComponent>();
            
            std::string componentName = std::string(Core::TemplateTypeAsString<Application::WorldTransformComponent>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                reflector::visit_all(component, visitor);
            }
        });
        Register(Core::GetTypeId<Application::ColliderComponent>(), [](VISITOR visitor, Application::ITemporaryComponentRef& componentRef)
        {
            Application::ColliderComponent& component = componentRef.GetComponent<Application::ColliderComponent>();
            
            std::string componentName = std::string(Core::TemplateTypeAsString<Application::ColliderComponent>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                reflector::visit_all(component, visitor);
            }
        });
        Register(Core::GetTypeId<Application::RigidBodyComponent>(), [](VISITOR visitor, Application::ITemporaryComponentRef& componentRef)
        {
            Application::RigidBodyComponent& component = componentRef.GetComponent<Application::RigidBodyComponent>();
            
            std::string componentName = std::string(Core::TemplateTypeAsString<Application::RigidBodyComponent>());
            if (ImGui::CollapsingHeader(componentName.c_str(), ImGuiTreeNodeFlags_None))
            {
                reflector::visit_all(component, visitor);
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
        VISITOR visitor;
        Create(componentRef.GetComponentType(), std::move(visitor), componentRef);
    }
};

struct CreateUIVisitor
{
    template<class FieldData>
    void operator()(FieldData f)
    {
        ui_creator<raw_type_t<decltype(f.get())>>().CreateUI(f.get());
    }
};

using UIVisitor = ComponentRefVisitor<CreateUIVisitor>;
}// namespace UI
}// namespace IMGUI
}// namespace Editor
