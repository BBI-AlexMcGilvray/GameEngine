#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/IO/Headers/File.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Data/Headers/AssetType.h"

namespace Data
{
	namespace Rendering
	{
		struct PositionFrameData
		{
			Core::Math::Float3 Position;
			Core::Second Time;

			PositionFrameData() = delete;
			PositionFrameData(Core::Math::Float3 position, Core::Second time);
		};

		struct RotationFrameData
		{
			Core::Math::FQuaternion Rotation;
			Core::Second Time;

			RotationFrameData() = delete;
			RotationFrameData(Core::Math::FQuaternion rotation, Core::Second time);
		};

		struct ScaleFrameData
		{
			Core::Math::Float3 Scale;
			Core::Second Time;

			ScaleFrameData() = delete;
			ScaleFrameData(Core::Math::Float3 scale, Core::Second time);
		};

		struct BoneAnimationData
		{
			enum class AnimationBehaviour
			{
				Default,
				Constant,
				Linear,
				Repeat,
				Unknown
			};

			Core::String Name;

			AnimationBehaviour PreBehaviour;
			AnimationBehaviour PostBehaviour;

			Core::List<PositionFrameData> PositionChannel;
			Core::List<RotationFrameData> RotationChannel;
			Core::List<ScaleFrameData> ScaleChannel;

			BoneAnimationData() = delete;
			BoneAnimationData(Core::String name);

			void ReadAnimationData(Core::String name, Core::IO::File& animationFile);

		private:
			AnimationBehaviour GetBehaviourFromString(String string);
			void AddPositionFrame(Core::Math::Float3 position, Core::Second time);
			void AddRotationFrame(Core::Math::FQuaternion rotation, Core::Second time);
			void AddScaleFrame(Core::Math::Float3 scale, Core::Second time);
		};

		struct SkeletonAnimationData
		{
			Core::String Name;

			Core::List<BoneAnimationData> BoneAnimations;

			Core::Second Duration;

			SkeletonAnimationData() = default;
			SkeletonAnimationData(Core::String fileName);
		};
	}

	/*
	template <>
	struct AssetType<Rendering::SkeletonAnimationData>
	{
		Hash ClassHash() const
		{
			return HashValue("SkeletonAnimationData");
		}

		String GetPath() const
		{
			return "Resources/ExportedAssets/SkeletonAnimations/";
		}

		String GetFileType() const
		{
			return ".SAnim";
		}
	};
	*/
}