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
			/*
				Bones will need to hold onto their inverse bind matrix so that we can multiply their LOCAL transfom matrix by it (the multiply this by the model transformation matrix)
				to get the matrix that represents the mesh deformation
			*/

			// this constructor should take in the inverse bind matrix and the local transfromation matrix (the latter to set up it's world/local position)
			// Also, nodes should be able to be set to local or world for their transformations
			// Local nodes should be required to have a parent node to build their final transformation matrix
			Bone(Core::Ptr<State> parentState, Ptr<Node> parentNode, Ptr<Bone> rootBone, Core::String name, Float3 position, FQuaternion rotation, Float3 scale);

			// child bones are handled through the Node inheritance

			void Start() override;

			Float4x4 GetBindOffset();

			List<Float4x4> GetBoneMatrices();

		private:
			Float4x4 InverseBindMatrix;
		};

		struct Skeleton
		{
			// animation system and how we want to plug it in is TBD - presumably a more generic system than wiring it specific to bones and such
			//Core::List<BoneAnimation> Animations;

			// we will need the parent node in constructor to know where our bones are rooted to
			Skeleton(Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::SkeletonData> asset);

			int GetBoneCount() const;
			Core::Ptr<Bone> GetSkeletonHierarchy() const;

			List<Float4x4> GetBoneMatrices() const;

		private:
			Data::AssetData<Data::Rendering::SkeletonData> Data;
			// unsure if we need the below two pieces of data
			Core::Functionality::Delegate<> OnRootDeleted;
			Core::Ptr<Bone> Root = nullptr;
			// hold list of all bones - in order - to be able to calculate the matrices to pass to shader in the same order
			Core::List<Core::Ptr<Bone>> BoneList;

			Core::Ptr<Bone> CreateBoneHeirarchy(Core::Ptr<Geometric::Node> parentNode, Core::Ptr<Data::Rendering::SkeletonBoneData> boneData, Core::Ptr<Bone> rootBone = nullptr);
		};
	}
}