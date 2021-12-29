#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/Animation/Headers/Channel.h"

namespace Application {
namespace Animation {
    using Channel_Float3 = Channel<Core::Math::Float3, &Core::Math::Float3::X, &Core::Math::Float3::Y, &Core::Math::Float3::Z>;
    using Channel_Float4 = Channel<Core::Math::Float4, &Core::Math::Float4::X, &Core::Math::Float4::Y, &Core::Math::Float4::Z, &Core::Math::Float4::W>;
    using Channel_FQuat = Channel<Core::Math::FQuaternion, &Core::Math::FQuaternion::X, &Core::Math::FQuaternion::Y, &Core::Math::FQuaternion::Z, &Core::Math::FQuaternion::W>;
}// namespace Animation
}// namespace Application