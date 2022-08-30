#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/ECS/DataOriented/EntityHandler.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Product
{
namespace Testing
{
    Application::EntityHandler& SpawnStaticModel(Application::State& state);
    Application::EntityHandler& SpawnAnimatedModel(Application::State& state);

    Application::EntityHandler& SpawnCollider(Application::State& state, const Core::Math::Float3& velocity, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::EntityHandler& SpawnStaticCollider(Application::State& state, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::EntityHandler& SpawnTrigger(Application::State& state, const Core::Math::Float3& velocity, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::EntityHandler& SpawnStaticTrigger(Application::State& state, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));

    Application::EntityHandler& TestEntityAsset(Application::State& state);
} // namespace Testing
} // namespace Product