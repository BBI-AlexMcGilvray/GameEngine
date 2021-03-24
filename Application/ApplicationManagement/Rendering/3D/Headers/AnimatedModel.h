#pragma once

#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/SkinnedObjectShader.h"

#include "ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"

#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/AnimatedModelData.h"

namespace Application
{
	namespace Rendering
	{
		// is a model,  but also has a list of timelines that can be called for animations
		// also holds a list of the relevant bones
		struct AnimatedModel : public Geometric::ContentBase
		{
			Data::AssetData<Data::Rendering::AnimatedModelData> Data;
			//Material Material;
			//SkinnedMeshBase Mesh;

			AnimatedModel(Core::Ptr<RenderManager> manager, Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::AnimatedModelData> asset);

			// be able to change what skeleton a model is listening to - returns true if able to map to skeleton
			bool SkinToSkeleton(Core::UniquePtr<Skeleton> skeleton);

			//Core::size GetVertexCount() const override;

			void Initialize() override;
			void Start() override;
			void Update(Core::Second dt) override;
			void End() override;
			void CleanUp() override;

		protected:
			//SkinnedObjectShader& Shader;

		private:
			// do we need this?
			Core::Ptr<Core::Geometric::Transform> _transform;

			// should this be a unique ptr? or is the skeleton owned by the node heirarchy?
			// no, it should be a skeleton component
			Core::UniquePtr<Skeleton> SkinnedSkeleton;

			ComponentPtr<MaterialComponent> _materialComponent;
			ComponentPtr<Render> _renderComponent;
		};
	}
}