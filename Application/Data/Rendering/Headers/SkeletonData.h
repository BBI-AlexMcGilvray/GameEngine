#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"

#include "Core/IO/Headers/File.h"
#include "Core/IO/Headers/IODefs.h"

#include "Data/Headers/AssetName.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

namespace Data
{
	namespace Rendering
	{
		struct SkeletonBoneData
		{
			Core::String Name;
			Core::Math::Float3 Position;
			Core::Math::FQuaternion Rotation;
			Core::Math::Float3 Scale;

			Core::List<Core::UniquePtr<SkeletonBoneData>> ChildBones;

			SkeletonBoneData() = delete;
			SkeletonBoneData(Core::String name, Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(Core::Math::II()));

			void AddBone(Core::UniquePtr<SkeletonBoneData> bone);
		};

		struct SkeletonData
		{
			Core::UniquePtr<SkeletonBoneData> Root;

			Core::List<AssetName<SkeletonAnimationData>> Animations;

			SkeletonData() = default;
			SkeletonData(AssetName<SkeletonData> asset);

		private:
			void ReadAnimations(Core::IO::File& skeletonFile);
			void ReadBoneChildren(Core::Ptr<SkeletonBoneData> parent, Core::IO::File& skeletonFile);

			void ReadName(Core::IO::IOSStreamChar& lineStream, Core::String& name);
			void ReadPosition(Core::IO::IOSStreamChar& lineStream, Core::Math::Float3& position);
			void ReadRotation(Core::IO::IOSStreamChar& lineStream, Core::Math::FQuaternion& rotation);
			void ReadScale(Core::IO::IOSStreamChar& lineStream, Core::Math::Float3& scale);
		};
	}

	template <>
	struct AssetType<Rendering::SkeletonData>
	{
		static Hash ClassHash()
		{
			return HashValue("SkeletonData");
		}

		static String GetPath()
		{
			return "Resources/Skeletons/";
		}

		static String GetFileType()
		{
			return ".skl";
		}
	};
}