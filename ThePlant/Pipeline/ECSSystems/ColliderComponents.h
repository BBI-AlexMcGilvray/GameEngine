#pragma once

#include "Core/Geometric/GeometryDefs.h"

namespace Application
{
struct ColliderComponent
{
    Core::Geometric::Shape3D shape;
    bool trigger;
};
} // namespace Application