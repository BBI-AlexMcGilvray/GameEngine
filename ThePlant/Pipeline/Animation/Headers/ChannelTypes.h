#pragma once

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Pipeline/Animation/Headers/Channel.h"

namespace Application {
namespace Animation {
    using Channel_Float3 = Channel<Core::Math::Float3>;
    using Channel_Float4 = Channel<Core::Math::Float4>;
    using Channel_FQuat = Channel<Core::Math::FQuaternion>;
}// namespace Animation
}// namespace Application