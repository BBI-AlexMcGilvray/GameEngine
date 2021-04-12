#include "ApplicationManagement/Animation/TransformAnimation/Headers/TransformAnimationTrack.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application
{
	namespace Animation
	{
		TransformAnimationTrack::TransformAnimationTrack()
		{}

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