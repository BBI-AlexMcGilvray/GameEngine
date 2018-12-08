#pragma once

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/3D/Headers/SimpleMeshBase.h"

#include "Data/Rendering/Headers/SimpleModelData.h"

namespace Application
{
	namespace Rendering
	{
		// holds the mesh, texture(s), and shader that a model uses
		struct ModelBase : RenderObjectBase
		{
			Data::Rendering::SimpleModelData Data;
			Material Material;
			SimpleMeshBase Mesh;

			// this should be loading up the model data instead of the mesh data
			ModelBase(RenderManager& manager, Ptr<const Transform> renderTransform, Data::AssetName<Data::Rendering::SimpleModelData> asset);

			uint GetVertexCount() const override;

		protected:
			ObjectShader& Shader;

			void Prepare(const Float4x4& mvp, const Color& color) const override;
			void CleanUp() const override;
		};
	}
}