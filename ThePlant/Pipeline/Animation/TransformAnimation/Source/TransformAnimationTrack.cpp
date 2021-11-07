#include "Pipeline/Animation/TransformAnimation/Headers/TransformAnimationTrack.h"

#include <utility>
#include <vector>

#include "Core/Logging/Logger.h"

namespace Application {
namespace Animation {
  TransformAnimationTrack::TransformAnimationTrack(const Data::Rendering::BoneAnimationData &data)
  {
    // position
    std::vector<Keyframe> posX;
    std::vector<Keyframe> posY;
    std::vector<Keyframe> posZ;
    for (const Data::Rendering::PositionFrameData& positionData : data.positionChannel) {
      posX.push_back(Keyframe(positionData.time, positionData.position.X));
      posY.push_back(Keyframe(positionData.time, positionData.position.Y));
      posZ.push_back(Keyframe(positionData.time, positionData.position.Z));
    }
    SetTrack(TransformTarget::P_X, FloatAnimationTrack(AnimationCurve(posX)));
    SetTrack(TransformTarget::P_Y, FloatAnimationTrack(AnimationCurve(posY)));
    SetTrack(TransformTarget::P_Z, FloatAnimationTrack(AnimationCurve(posZ)));

    // rotation
    std::vector<Keyframe> rotX;
    std::vector<Keyframe> rotY;
    std::vector<Keyframe> rotZ;
    std::vector<Keyframe> rotW;
    for (const Data::Rendering::RotationFrameData& rotationData : data.rotationChannel) {
      posX.push_back(Keyframe(rotationData.time, rotationData.rotation.X));
      posY.push_back(Keyframe(rotationData.time, rotationData.rotation.Y));
      posZ.push_back(Keyframe(rotationData.time, rotationData.rotation.Z));
      posZ.push_back(Keyframe(rotationData.time, rotationData.rotation.W));
    }
    SetTrack(TransformTarget::R_X, FloatAnimationTrack(AnimationCurve(rotX)));
    SetTrack(TransformTarget::R_Y, FloatAnimationTrack(AnimationCurve(rotY)));
    SetTrack(TransformTarget::R_Z, FloatAnimationTrack(AnimationCurve(rotZ)));
    SetTrack(TransformTarget::R_W, FloatAnimationTrack(AnimationCurve(rotW)));

    // scale
    std::vector<Keyframe> scaleX;
    std::vector<Keyframe> scaleY;
    std::vector<Keyframe> scaleZ;
    for (const Data::Rendering::ScaleFrameData& scaleData : data.scaleChannel) {
      scaleX.push_back(Keyframe(scaleData.time, scaleData.scale.X));
      scaleY.push_back(Keyframe(scaleData.time, scaleData.scale.Y));
      scaleZ.push_back(Keyframe(scaleData.time, scaleData.scale.Z));
    }
    SetTrack(TransformTarget::S_X, FloatAnimationTrack(AnimationCurve(scaleX)));
    SetTrack(TransformTarget::S_Y, FloatAnimationTrack(AnimationCurve(scaleY)));
    SetTrack(TransformTarget::S_Z, FloatAnimationTrack(AnimationCurve(scaleZ)));
  }

  void TransformAnimationTrack::SetTrack(TransformTarget target, FloatAnimationTrack animationTrack)
  {
    if (_tracks.find(target) != _tracks.end())
    {
      _tracks[target] = animationTrack;
    }

    DEBUG_THROW("TransformAnimationTrack", "target " + std::to_string(int(target)) + " already being affected by an animationtrack");
  }

  void TransformAnimationTrack::SetStartState(const Core::Geometric::Transform &transform)
  {
    _startState = transform;
  }

  Core::Geometric::Transform TransformAnimationTrack::Evaluate(Core::Second time)
  {
    Core::Math::Float3 position = _startState.GetPosition();
    Core::Math::FQuaternion rotation = _startState.GetRotation();
    Core::Math::Float3 scale = _startState.GetScale();

    for (std::pair<const TransformTarget, FloatAnimationTrack> &pair : _tracks) {
      switch (pair.first) {
      case TransformTarget::P_X: {
        position.X = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::P_Y: {
        position.Y = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::P_Z: {
        position.Z = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::R_X: {
        rotation.X = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::R_Y: {
        rotation.Y = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::R_Z: {
        rotation.Z = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::R_W: {
        rotation.W = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::S_X: {
        scale.X = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::S_Y: {
        scale.Y = pair.second.Evaluate(time);
        break;
      }
      case TransformTarget::S_Z: {
        scale.Z = pair.second.Evaluate(time);
        break;
      }
      }
    }

    return Core::Geometric::Transform(position, rotation, scale);
  }
}// namespace Animation
}// namespace Application