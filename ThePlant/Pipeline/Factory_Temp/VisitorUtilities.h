#pragma once

#include "Core/Headers/Factory.h"
#include "Core/IdTypes/RuntimeId.h"
#include "Core/Reflection/Reflectable.h"

#include "Pipeline/ECS/DataOriented/TemporaryComponentRef.h"
#include "Pipeline/ECS/DataOriented/EntitySnapshot.h"

// testing
// these shouldn't be here because we are just testing stuff
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

// these shouldn't be here because they should be registered elsewhere
#include "Pipeline/ECSSystems/TransformComponents.h"
#include "Pipeline/ECSSystems/ColliderComponents.h"
#include "Pipeline/Physics/PhysicsComponents.h"
// \testing

namespace Application {
template <typename VISITOR>
using TemporaryComponentRefVisitorFactory = Core::TypeFactory<void, VISITOR, ITemporaryComponentRef&>;

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
        Register(Core::GetTypeId<PositionComponent>(), [](VISITOR visitor, ITemporaryComponentRef& componentRef)
        {
            PositionComponent& component = componentRef.GetComponent<PositionComponent>();
            std::cout << std::string(Core::TemplateTypeAsString<PositionComponent>()) << '\n';
            // reflector::visit_all(component, visitor);
            std::cout << Core::Math::VectorString(component.position) << '\n';
        });
        Register(Core::GetTypeId<RotationComponent>(), [](VISITOR visitor, ITemporaryComponentRef& componentRef)
        {
            RotationComponent& component = componentRef.GetComponent<RotationComponent>();
            std::cout << std::string(Core::TemplateTypeAsString<RotationComponent>()) << '\n';
            // reflector::visit_all(component, visitor);
            std::cout << Core::Math::QuaternionString(component.rotation) << '\n';
        });
        Register(Core::GetTypeId<ScaleComponent>(), [](VISITOR visitor, ITemporaryComponentRef& componentRef)
        {
            ScaleComponent& component = componentRef.GetComponent<ScaleComponent>();
            std::cout << std::string(Core::TemplateTypeAsString<ScaleComponent>()) << '\n';
            // reflector::visit_all(component, visitor);
            std::cout << Core::Math::VectorString(component.scale) << '\n';
        });
        Register(Core::GetTypeId<WorldTransformComponent>(), [](VISITOR visitor, ITemporaryComponentRef& componentRef)
        {
            WorldTransformComponent& component = componentRef.GetComponent<WorldTransformComponent>();
            std::cout << std::string(Core::TemplateTypeAsString<WorldTransformComponent>()) << '\n';
            // reflector::visit_all(component, visitor);
        });
        Register(Core::GetTypeId<ColliderComponent>(), [](VISITOR visitor, ITemporaryComponentRef& componentRef)
        {
            ColliderComponent& component = componentRef.GetComponent<ColliderComponent>();
            std::cout << std::string(Core::TemplateTypeAsString<ColliderComponent>()) << '\n';
            // reflector::visit_all(component, visitor);
        });
        Register(Core::GetTypeId<RigidBodyComponent>(), [](VISITOR visitor, ITemporaryComponentRef& componentRef)
        {
            RigidBodyComponent& component = componentRef.GetComponent<RigidBodyComponent>();
            std::cout << std::string(Core::TemplateTypeAsString<RigidBodyComponent>()) << '\n';
            // reflector::visit_all(component, visitor);
        });
    }

    void Visit(const EntitySnapshot& snapshot)
    {
        for (auto& component : snapshot.GetComponents())
        {
            Visit(*component);
        }
    }

    // should visitors be passed down by ref? should they be perfect-forwarded (&&)? probably, would support everything
    void Visit(ITemporaryComponentRef& componentRef)
    {
        VISITOR visitor;
        Create(componentRef.GetComponentType(), std::move(visitor), componentRef);
    }
};

using PrintVisitor = ComponentRefVisitor<print_visitor>;
}// namespace Application
