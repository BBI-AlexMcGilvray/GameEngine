#include "ApplicationManagement/Animation/TransformAnimation/Headers/TransformAnimationTrack.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application
{
	namespace Animation
	{
		TransformAnimationTrack::TransformAnimationTrack(const Data::Rendering::BoneAnimationData& data)
		{
			// position
			Core::List<Keyframe> posX;
			Core::List<Keyframe> posY;
			Core::List<Keyframe> posZ;
			for (Data::Rendering::PositionFrameData positionData : data.PositionChannel)
			{
				Push(posX, Keyframe(positionData.Time, positionData.Position.X));
				Push(posY, Keyframe(positionData.Time, positionData.Position.Y));
				Push(posZ, Keyframe(positionData.Time, positionData.Position.Z));
			}
			SetTrack(TransformTarget::P_X, FloatAnimationTrack(AnimationCurve(posX)));
			SetTrack(TransformTarget::P_Y, FloatAnimationTrack(AnimationCurve(posY)));
			SetTrack(TransformTarget::P_Z, FloatAnimationTrack(AnimationCurve(posZ)));

			// rotation
			Core::List<Keyframe> rotX;
			Core::List<Keyframe> rotY;
			Core::List<Keyframe> rotZ;
			Core::List<Keyframe> rotW;
			for (Data::Rendering::RotationFrameData rotationData : data.RotationChannel)
			{
				Push(posX, Keyframe(rotationData.Time, rotationData.Rotation.X));
				Push(posY, Keyframe(rotationData.Time, rotationData.Rotation.Y));
				Push(posZ, Keyframe(rotationData.Time, rotationData.Rotation.Z));
				Push(posZ, Keyframe(rotationData.Time, rotationData.Rotation.W));
			}
			SetTrack(TransformTarget::R_X, FloatAnimationTrack(AnimationCurve(rotX)));
			SetTrack(TransformTarget::R_Y, FloatAnimationTrack(AnimationCurve(rotY)));
			SetTrack(TransformTarget::R_Z, FloatAnimationTrack(AnimationCurve(rotZ)));
			SetTrack(TransformTarget::R_W, FloatAnimationTrack(AnimationCurve(rotW)));

			// scale
			Core::List<Keyframe> scaleX;
			Core::List<Keyframe> scaleY;
			Core::List<Keyframe> scaleZ;
			for (Data::Rendering::ScaleFrameData scaleData : data.ScaleChannel)
			{
				Push(scaleX, Keyframe(scaleData.Time, scaleData.Scale.X));
				Push(scaleY, Keyframe(scaleData.Time, scaleData.Scale.Y));
				Push(scaleZ, Keyframe(scaleData.Time, scaleData.Scale.Z));
			}
			SetTrack(TransformTarget::S_X, FloatAnimationTrack(AnimationCurve(scaleX)));
			SetTrack(TransformTarget::S_Y, FloatAnimationTrack(AnimationCurve(scaleY)));
			SetTrack(TransformTarget::S_Z, FloatAnimationTrack(AnimationCurve(scaleZ)));
		}

		void TransformAnimationTrack::SetTrack(TransformTarget target, FloatAnimationTrack animationTrack)
		{
			if (!Core::In(_tracks, target))
			{
				_tracks[target] = animationTrack;
			}

			ALERT("target " + std::to_string(int(target)) + " already being affected by an animationtrack");
		}

		void TransformAnimationTrack::SetStartState(const Core::Geometric::Transform& transform)
		{
			_startState = transform;
		}

		Core::Geometric::Transform TransformAnimationTrack::Evaluate(Core::Second time)
		{
			Float3 position = _startState.GetPosition();
			FQuaternion rotation = _startState.GetRotation();
			Float3 scale = _startState.GetScale();

			for (Core::Pair<const TransformTarget, FloatAnimationTrack>& pair : _tracks)
			{
				switch (pair.first)
				{
				case TransformTarget::P_X:
				{
					position.X = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::P_Y:
				{
					position.Y = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::P_Z:
				{
					position.Z = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::R_X:
				{
					rotation.X = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::R_Y:
				{
					rotation.Y = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::R_Z:
				{
					rotation.Z = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::R_W:
				{
					rotation.W = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::S_X:
				{
					scale.X = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::S_Y:
				{
					scale.Y = pair.second.Evaluate(time);
					break;
				}
				case TransformTarget::S_Z:
				{
					scale.Z = pair.second.Evaluate(time);
					break;
				}
				}
			}

			return Core::Geometric::Transform(position, rotation, scale);
		}
	}
}