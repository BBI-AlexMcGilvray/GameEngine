#include "Data/Rendering/Headers/SkeletonData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		SkeletonBoneData::SkeletonBoneData(String name, Float3 position, FQuaternion rotation, Float3 scale)
			: Name(name)
			, Position(position)
			, Rotation(rotation)
			, Scale(scale)
		{
		}

		void SkeletonBoneData::AddBone(UniquePtr<SkeletonBoneData> bone)
		{
			Push(ChildBones, move(bone));
		}

		SkeletonData::SkeletonData(AssetName<SkeletonData> asset)
		{
			File skeletonFile = OpenFileI(asset.GetFilePath());

			MESSAGE(skeletonFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			try
			{
				ReadAnimations(skeletonFile);

				String line = skeletonFile.GetLine();

				IOSStreamChar lineStream(line);

				String name;
				Float3 position;
				FQuaternion rotation;
				Float3 scale;

				int children;

				char comma;

				ReadName(lineStream, name);
				lineStream >> children;

				lineStream >> comma;
				ReadScale(lineStream, scale);
				lineStream >> comma;
				ReadRotation(lineStream, rotation);
				lineStream >> comma;
				ReadPosition(lineStream, position);

				Root = MakeUnique<SkeletonBoneData>(name, position, rotation, scale);

				//LOG("Adding " + ToString(children) + " bones to " + name);
				for (int i = 0; i < children; i++)
				{
					ReadBoneChildren(Root.get(), skeletonFile);
				}
				//LOG(name + " now has " + ToString(Root->ChildBones.size()) + " children");
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}
			
			skeletonFile.Close();
		}

		void SkeletonData::ReadAnimations(File& skeletonFile)
		{
			String line = skeletonFile.GetLine();

			IOSStreamChar lineStream(line);

			String animations;
			int numAnimations;

			lineStream >> animations;
			lineStream >> numAnimations;

			//LOG("num animations: " + ToString(numAnimations));
			for (int i = 0; i < numAnimations; i++)
			{
				line = skeletonFile.GetLine();
				lineStream = IOSStreamChar(line);

				AssetName<SkeletonAnimationData> animationName;
				lineStream >> animationName.Name.H;
				Push(Animations, animationName);
			}
			//LOG("num animations read: " + ToString(Animations.size()));
		}

		void SkeletonData::ReadBoneChildren(Ptr<SkeletonBoneData> parent, File& skeletonFile)
		{
			String line = skeletonFile.GetLine();

			IOSStreamChar lineStream(line);

			String name;
			Float3 position;
			FQuaternion rotation;
			Float3 scale;

			int children;

			char comma;

			ReadName(lineStream, name);
			lineStream >> children;
			
			lineStream >> comma;
			ReadScale(lineStream, scale);
			lineStream >> comma;
			ReadRotation(lineStream, rotation);
			lineStream >> comma;
			ReadPosition(lineStream, position);

			UniquePtr<SkeletonBoneData> newParent = MakeUnique<SkeletonBoneData>(name, position, rotation, scale);
			//LOG("Adding " + ToString(children) + " bones to " + name);
			for (int i = 0; i < children; i++)
			{
				ReadBoneChildren(newParent.get(), skeletonFile);
			}
			//LOG(name + " now has " + ToString(newParent->ChildBones.size()) + " children");
			parent->AddBone(move(newParent));
		}

		void SkeletonData::ReadName(IOSStreamChar& lineStream, String& name)
		{
			lineStream >> name;
		}

		void SkeletonData::ReadPosition(IOSStreamChar& lineStream, Float3& position)
		{
			String positionSection;
			lineStream >> positionSection;

			lineStream >> position.X;
			lineStream >> position.Y;
			lineStream >> position.Z;

			position /= 10.0f;
			LOG("Position values should be modified on the data side!");
		}

		void SkeletonData::ReadRotation(IOSStreamChar& lineStream, FQuaternion& rotation)
		{
			String rotationSection;
			lineStream >> rotationSection;

			lineStream >> rotation.X;
			lineStream >> rotation.Y;
			lineStream >> rotation.Z;
			lineStream >> rotation.W;
		}

		void SkeletonData::ReadScale(IOSStreamChar& lineStream, Float3& scale)
		{
			String scaleSection;
			lineStream >> scaleSection;

			lineStream >> scale.X;
			lineStream >> scale.Y;
			lineStream >> scale.Z;
		}
	}
}