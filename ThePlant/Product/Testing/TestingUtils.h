#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Core/Geometric/GeometryDefs.h"

#include "Pipeline/ECS/DataOriented/IDs.h"

namespace Product
{
namespace Testing
{
    Application::Entity SpawnStaticModel();
    Application::Entity SpawnAnimatedModel();

    Application::Entity SpawnCollider(const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
    Application::Entity SpawnTrigger(const Core::Geometric::Shape3D& shape, const Core::Math::Float3& position, const Core::Math::FQuaternion& rotation = Core::Math::FQuaternion(Core::Math::II()), const Core::Math::Float3& scale = Core::Math::Float3(Core::Math::II()));
} // namespace Testing
} // namespace Product