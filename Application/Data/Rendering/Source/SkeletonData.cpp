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

		SkeletonData::SkeletonData(String fileName)
		{
			File skeletonFile = OpenFileI(FilePath{ String("Resources/ExportedAssets/Skeletons/"), fileName });

			MESSAGE(skeletonFile.FileStream.is_open(), "FAILED TO READ FILE <<" + fileName + ">>");

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

				ReadName(lineStream, name);
				lineStream >> children;
				ReadScale(lineStream, scale);
				ReadRotation(lineStream, rotation);
				ReadPosition(lineStream, position);

				Root = MakeUnique<SkeletonBoneData>(name, position, rotation, scale);

				for (int i = 0; i < children; i++)
				{
					ReadBoneChildren(Root.get(), skeletonFile);
				}
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

			for (int i = 0; i < numAnimations; i++)
			{
				AssetName<SkeletonAnimationData> animationName;
				lineStream >> animationName.Name.H;
				Push(Animations, animationName);
			}
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

			ReadName(lineStream, name);
			lineStream >> children;

			ReadScale(lineStream, scale);
			ReadRotation(lineStream, rotation);
			ReadPosition(lineStream, position);

			UniquePtr<SkeletonBoneData> newParent = MakeUnique<SkeletonBoneData>(name, position, rotation, scale);

			for (int i = 0; i < children; i++)
			{
				ReadBoneChildren(newParent.get(), skeletonFile);
			}

			parent->AddBone(move(newParent));
		}

		void SkeletonData::ReadName(IOSStreamChar& lineStream, String& name)
		{
			lineStream >> name;
		}

		void SkeletonData::ReadPosition(IOSStreamChar& lineStream, Float3& position)
		{
			lineStream >> position.X;
			lineStream >> position.Y;
			lineStream >> position.Z;
		}

		void SkeletonData::ReadRotation(IOSStreamChar& lineStream, FQuaternion& rotation)
		{
			lineStream >> rotation.X;
			lineStream >> rotation.Y;
			lineStream >> rotation.Z;
			lineStream >> rotation.W;
		}

		void SkeletonData::ReadScale(IOSStreamChar& lineStream, Float3& scale)
		{
			lineStream >> scale.X;
			lineStream >> scale.Y;
			lineStream >> scale.Z;
		}
	}
}