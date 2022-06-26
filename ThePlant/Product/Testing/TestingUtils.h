#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/ECS/DataOriented/IDs.h"
#include "Pipeline/StateSystem/Headers/State.h"

namespace Product
{
namespace Testing
{
    Application::Entity SpawnStaticModel(Application::State& state);
    Application::Entity SpawnAnimatedModel(Application::State& state);

    Application::Entity SpawnCollider(Application::State& state, const Core::Math::Float3& velocity, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::Entity SpawnStaticCollider(Application::State& state, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::Entity SpawnTrigger(Application::State& state, const Core::Math::Float3& velocity, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::Entity SpawnStaticTrigger(Application::State& state, const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
} // namespace Testing
} // namespace Product