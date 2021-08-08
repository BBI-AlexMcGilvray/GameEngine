#pragma once

#include "Core/Headers/TimeDefs.h"

namespace Application {
namespace Animation {
  struct Keyframe
  {
  public:
    Keyframe();
    Keyframe(Core::Second time, float value);
    Keyframe(Core::Second time, float value, float inWeight, float infloatangent, float outWeight, float outfloatangent);

    void SetTime(Core::Second time);
    Core::Second GetTime();

    void SetValue(float value);
    float GetValue();

    void SetInWeight(float weight);
    float GetInWeight();

    void SetInTangent(float tangent);
    float GetInTangent();

    void SetOutWeight(float weight);
    float GetOutWeight();

    void SetOutTangent(float tangent);
    float GetOutTangent();

  private:
    Core::Second _time;
    float _value;

    float _inWeight;
    float _inTangent;

    float _outWeight;
    float _outTangent;
  };
}// namespace Animation
}// namespace Application