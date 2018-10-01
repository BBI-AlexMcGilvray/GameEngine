#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/ListDefs.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct CircleRenderObject : RenderObjectBase
		{
			GLArrayBuffer Vao;
			List<GLBuffer> Vbos;
			List<Data::Rendering::VertexDataBase> Vertices;

			CircleRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color);
			CircleRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color, float radius);

			virtual void Initialize();

			virtual void Prepare(const Float4x4& mvp, const Color& color) const;
			virtual void CleanUp() const;

			uint GetVertexCount() const override
			{
				return Vertices.size();
			}

		protected:
			ObjectShader& Shader;

			float Radius;
		};
	}
}