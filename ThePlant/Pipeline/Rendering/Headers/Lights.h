#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Geometric/Transform.h"

#include "Core/Math/Headers/Color.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Math;

namespace Application {
namespace Rendering {
  struct BaseLight
  {
    Color LightColor;
    float Intensity;

    BaseLight(SharedPtr<Transform> position, float intensity = 10.0f, Color lightColor = WHITE);

    virtual void Update(Second dt);

    virtual Float3 GetPosition() const;
    virtual Color GetColor() const;
    virtual float GetIntensity(const Float3 &position) const = 0;

  protected:
    SharedPtr<Transform> Position;
  };

  struct PointLight : BaseLight
  {
    float GetIntensity(const Float3 &position) const override;
  };

  struct DirectionalLight : BaseLight
  {
    Float3 Direction;
    FRad ConeAngle = 0.523599f;

    DirectionalLight(SharedPtr<Transform> position, Float3 direction = Float3(0.0f, 0.0f, -1.0f), FRad coneAngle = 0.523599f, Color lightColor = WHITE, float intensity = Inf_F);

    float GetIntensity(const Float3 &position) const override;
  };
}// namespace Rendering
}// namespace Application