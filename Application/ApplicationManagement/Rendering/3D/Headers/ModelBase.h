#pragma once

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/3D/Headers/MeshBase.h"

namespace Application
{
	namespace Rendering
	{
		// holds the mesh, texture(s), and shader that a model uses
		struct ModelBase : RenderObjectBase
		{
			Material Material;
			MeshBase Mesh;

			ModelBase(RenderManager& manager, Ptr<const Transform> renderTransform, String folderName);

			uint GetVertexCount() const override;

		protected:
			ObjectShader& Shader;

			void Prepare(const Float4x4& mvp, const Color& color) const override;
			void CleanUp() const override;
		};
	}
}