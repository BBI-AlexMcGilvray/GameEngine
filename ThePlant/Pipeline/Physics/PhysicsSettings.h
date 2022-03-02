#pragma once

#include "Core/Math/Headers/Vector3.h"

namespace Application
{
namespace Physics
{
struct Settings
{
    Core::Math::Float3 gravity = Core::Math::Float3(0.0f, -9.0f, 0.0f);
};
}
}