#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Core/Functionality/Headers/Event.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/SkeletonData.h"

// testing
#include "Core/Math/Headers/Color.h"

namespace Application
{
	namespace Rendering
	{
		// holds positional information for each bone that the mesh is weighted against
		struct Bone : Geometric::Node
		{
			// maybe we want to change it so that bones hold a reference to a node instead of a BEING a node - TBD
			// Benefit of being a node - transform automatically updated
			// Downside of being a node - potentially slower to loop over and such (suboptimal - maybe)
			Bone(Core::Ptr<State> parentState, Core::String name, Float3 position, FQuaternion rotation, Float3 scale);

			// child bones are handled through the Node inheritance

			void Start() override;
		};

		struct Skeleton
		{
			// animation system and how we want to plug it in is TBD - presumably a more generic system than wiring it specific to bones and such
			//Core::List<BoneAnimation> Animations;

			// we will need the parent node in constructor to know where our bones are rooted to
			Skeleton(Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset);

			Core::Ptr<Bone> GetSkeletonHierarchy() const;

		private:
			Data::AssetData<Data::Rendering::SkeletonData> Data;
			Core::Functionality::Delegate<> OnRootDeleted;
			Core::Ptr<Bone> Root = nullptr;

			Core::Ptr<Bone> CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData);
		};
	}
}