#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"

#include "ApplicationManagement/Rendering/OpenGL/Headers/GLArrayBuffer.h"
#include "ApplicationManagement/Rendering/OpenGL/Headers/GLBuffer.h"

#include "ApplicationManagement/Rendering/Shaders/Headers/ObjectShader.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"
#include "Data/Rendering/Headers/VertexBaseData.h"

namespace Application
{
	namespace Rendering
	{
		// holds the information about the mesh of a 3D object
		struct SphereRenderObject : RenderObjectBase
		{
			GLArrayBuffer Vao;
			Core::List<GLBuffer> Vbos;
			Core::List<Data::Rendering::SimpleVertexDataBase> Vertices;

			SphereRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color);
			SphereRenderObject(Core::Ptr<RenderManager> manager, Core::Ptr<Core::Geometric::Transform> renderTransform, Core::Math::Color color, float radius);

			~SphereRenderObject();

			virtual void Initialize();

			virtual void Prepare(const Core::Math::Float4x4& mvp, const Core::Math::Color& color) const;
			virtual void CleanUp() const;

			Core::size GetVertexCount() const override
			{
				return Vertices.size();
			}

		protected:
			ObjectShader& Shader;

			float Radius;

			void CreateMesh();
		};
	}
}