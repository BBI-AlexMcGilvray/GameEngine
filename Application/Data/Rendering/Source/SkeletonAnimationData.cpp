#include "Data/Rendering/Headers/SkeletonAnimationData.h"

#include "Core/IO/Headers/IOUtils.h"

#include "Core/Debugging/Headers/Macros.h"

using namespace std;

using namespace Core;
using namespace Core::IO;
using namespace Core::Math;

namespace Data
{
	namespace Rendering
	{
		PositionFrameData::PositionFrameData(Float3 position, Second time)
			: Position(position)
			, Time(time)
		{

		}

		RotationFrameData::RotationFrameData(FQuaternion rotation, Second time)
			: Rotation(rotation)
			, Time(time)
		{

		}

		ScaleFrameData::ScaleFrameData(Float3 scale, Second time)
			: Scale(scale)
			, Time(time)
		{

		}

		BoneAnimationData::BoneAnimationData(String name)
			: Name(name)
		{

		}

		void BoneAnimationData::ReadAnimationData(String name, File& animationFile)
		{
			bool doneReading = false;

			String word;
			int frames;
			while (!doneReading)
			{
				String line = animationFile.GetLine();

				IOSStreamChar lineStream(line);

				lineStream >> word;

				if (word == "preState")
				{
					lineStream >> word;
					PreBehaviour = GetBehaviourFromString(word);
				}
				else if (word == "postState")
				{
					lineStream >> word;
					PostBehaviour = GetBehaviourFromString(word);
				}
				else if (word == "position")
				{
					lineStream >> frames;

					for (int i = 0; i < frames; i++)
					{
						String line = animationFile.GetLine();

						IOSStreamChar lineStream(line);

						Float3 position;
						Second time;

						lineStream >> position.X;
						lineStream >> position.Y;
						lineStream >> position.Z;

						float dataTime;
						lineStream >> dataTime;
						time = Second(dataTime);

						AddPositionFrame(position, time);
					}
					continue;
				}
				else if (word == "rotation")
				{
					for (int i = 0; i < frames; i++)
					{
						String line = animationFile.GetLine();

						IOSStreamChar lineStream(line);

						FQuaternion rotation;
						Second time;

						lineStream >> rotation.X;
						lineStream >> rotation.Y;
						lineStream >> rotation.Z;
						lineStream >> rotation.W;

						float dataTime;
						lineStream >> dataTime;
						time = Second(dataTime);

						AddRotationFrame(rotation, time);
					}
					continue;
				}
				else if (word == "scale")
				{
					for (int i = 0; i < frames; i++)
					{
						String line = animationFile.GetLine();

						IOSStreamChar lineStream(line);

						Float3 scale;
						Second time;

						lineStream >> scale.X;
						lineStream >> scale.Y;
						lineStream >> scale.Z;

						float dataTime;
						lineStream >> dataTime;
						time = Second(dataTime);

						AddScaleFrame(scale, time);
					}
					continue;
				}

				doneReading = true;
			}
		}

		BoneAnimationData::AnimationBehaviour BoneAnimationData::GetBehaviourFromString(String string)
		{
			if (string == "default")
			{
				return AnimationBehaviour::Default;
			}
			else if (string == "constant")
			{
				return AnimationBehaviour::Constant;
			}
			else if (string == "linear")
			{
				return AnimationBehaviour::Linear;
			}
			else if (string == "repeat")
			{
				return AnimationBehaviour::Repeat;
			}
			else
			{
				return AnimationBehaviour::Unknown;
			}
		}

		void BoneAnimationData::AddPositionFrame(Float3 position, Second time)
		{
			Push(PositionChannel, PositionFrameData(position, time));
		}

		void BoneAnimationData::AddRotationFrame(FQuaternion rotation, Second time)
		{
			Push(RotationChannel, RotationFrameData(rotation, time));
		}

		void BoneAnimationData::AddScaleFrame(Float3 scale, Second time)
		{
			Push(ScaleChannel, ScaleFrameData(scale, time));
		}

		SkeletonAnimationData::SkeletonAnimationData(AssetName<SkeletonAnimationData> asset)
		{
			File animationFile = OpenFileI(asset.GetFilePath());

			MESSAGE(animationFile.FileStream.is_open(), "FAILED TO READ FILE <<" + asset.GetFilePath().GetFullPath() + ">>");

			try
			{
				String line = animationFile.GetLine();

				IOSStreamChar lineStream(line);

				int boneCount;

				lineStream >> Name;
				lineStream >> boneCount;

				float time;
				lineStream >> time;
				Duration = Second(time);

				String animationName;
				for (int i = 0; i < boneCount; i++)
				{
					lineStream >> animationName;

					BoneAnimationData newBoneAnimation = BoneAnimationData("UnNamed");
					newBoneAnimation.ReadAnimationData(animationName, animationFile);

					Push(BoneAnimations, newBoneAnimation);
				}
			}
			catch (EOFException& e)
			{
				std::cout << e.GetError() << std::endl;
			}

			animationFile.Close();
		}
	}
}