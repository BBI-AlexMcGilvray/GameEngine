#pragma once

#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

namespace Application
{
	namespace Rendering
	{
		// holds positional information for each bone that the mesh is weighted against
		struct Bone
		{
			Core::List<Core::Ptr<Bone>> Children;
		};

		struct Skeleton
		{
			Core::Ptr<Bone> Root;
		};

		// is a model,  but also has a list of timelines that can be called for animations
		// also holds a list of the relevant bones
		struct AnimatedModel : ModelBase
		{

			// be able to change what skeleton a model is listening to - returns true if able to map to skeleton
			bool SkinToSkeleton(Core::UniquePtr<Skeleton> skeleton);

		private:
			// should this be a unique ptr? or is the skeleton owned by the node heirarchy?
			Core::UniquePtr<Skeleton> Skeleton;
		};
	}
}