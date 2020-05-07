#pragma once

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedObjectShader.h"

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/3D/Headers/SkinnedMeshBase.h"

#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"

namespace Application
{
	namespace Rendering
	{
		// is a model,  but also has a list of timelines that can be called for animations
		// also holds a list of the relevant bones
		struct AnimatedModel : RenderObjectBase
		{
			Data::AssetData<Data::Rendering::AnimatedModelData> Data;
			Material Material;
			SkinnedMeshBase Mesh;

			AnimatedModel(Core::Ptr<RenderManager> manager, Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::AnimatedModelData> asset);

			// be able to change what skeleton a model is listening to - returns true if able to map to skeleton
			bool SkinToSkeleton(Core::UniquePtr<Skeleton> skeleton);

			Core::size GetVertexCount() const override;

		protected:
			SkinnedObjectShader& Shader;

			// should this be a unique ptr? or is the skeleton owned by the node heirarchy?
			Core::UniquePtr<Skeleton> SkinnedSkeleton;

			List<Uint4> BoneIndices;

			void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const override;
			void CleanUp() const override;
		};
	}
}