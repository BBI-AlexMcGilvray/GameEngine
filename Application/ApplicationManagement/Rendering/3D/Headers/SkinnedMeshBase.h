#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "Data/Headers/AssetData.h"
#include "Data/Rendering/Headers/AnimatedMeshData.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "ApplicationManagement/Rendering/3D/Headers/Skeleton.h"
#include "ApplicationManagement/Rendering/3D/Headers/RenderVertexBaseData.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLMappedBuffer.h"

#include "ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct SkinnedMeshBase : public RenderObjectBase
		{
			Data::AssetData<Data::Rendering::AnimatedMeshData> Data;
			List<AnimatedVertexRenderDataBase> RenderData;

			SkinnedMeshBase(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Data::AssetName<Data::Rendering::AnimatedMeshData> asset);
			~SkinnedMeshBase();

			Core::size GetVertexCount() const override;

			// should these be a part of render object base?
			void SetMaterialComponent(ComponentPtr<MaterialComponent> materialComponent);
			void ClearMaterialComponent();

			virtual void Initialize();

			void Skin(const Skeleton& skeleton);

		protected:
			virtual void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const;
			virtual void CleanUp() const;

		private:
			GLArrayBuffer Vao;
			List<GLBuffer> Vbos;
			GLMappedBuffer MappedMesh;

			Core::Functionality::Delegate<> _onMaterialDeleted;
			ComponentPtr<MaterialComponent> _materialComponent;

			void CreateRenderData();
		};
	}
}