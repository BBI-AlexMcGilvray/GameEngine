#include "ApplicationManagement/Rendering/3D/Headers/SphereRenderObject.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

#include "Core/Math/Headers/UtilityFunctions.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Geometric;

namespace Application
{
	namespace Rendering
	{
		SphereRenderObject::SphereRenderObject(Core::Ptr<RenderManager> manager, Ptr<Transform> renderTransform, Color color)
			: SphereRenderObject(manager, renderTransform, color, 1.0f)
		{}

		SphereRenderObject::SphereRenderObject(Core::Ptr<RenderManager> manager, Ptr<Transform> renderTransform, Color color, float radius)
			: RenderObjectBase(manager, renderTransform, color)
			, Radius(radius)
			, Shader(manager->ObjectShaderManager.DefaultShader)
		{
			Initialize();
		}

		SphereRenderObject::~SphereRenderObject()
		{
			Vao.Delete();
			for (int i = 0; i < Vbos.size(); i++)
			{
				Vbos[i].Delete();
			}
		}

		void SphereRenderObject::Initialize()
		{
			CreateMesh();

			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			glBufferData(newBuffer.Type, Vertices.size() * sizeof(Data::Rendering::SimpleVertexDataBase), &Vertices[0], GL_STATIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::SimpleVertexDataBase), (void*)(0));
			// normal
			glEnableVertexAttribArray(1); // this matches with object shader construction
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::SimpleVertexDataBase), (void*)(offsetof(Data::Rendering::SimpleVertexDataBase, Data::Rendering::SimpleVertexDataBase::Position)));

			Vao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(Vbos, newBuffer);
		}

		void SphereRenderObject::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Vao.Bind();
			Shader.Prepare(mvp, color);
		}

		void SphereRenderObject::CleanUp() const
		{
			Vao.Unbind();
			Shader.CleanUp();
		}

		void SphereRenderObject::CreateMesh()
		{
			// http://en.wikipedia.org/wiki/Icosahedron
			//(0, +/-1, +/-t)
			//(+/-1, +/-t, 0)
			//(+/-t, 0, +/-1)
			//where t = (1 + sqrt(5)) / 2 

			const float t = (1.0f + Sqrt(5.0f)) / 2.0f;
			// So each side has a length of sqrt( t*t + 1.0 )
			float rScale = Radius / Sqrt(t*t + 1.0f); // correct the radius
			List<Float3> vertices = List<Float3>(12);

			for (int i = 0; i < 4; i++)
				//v[ i ] = Vector( 0, -(i&2), -(i&1)*t ) ; 
				vertices[i] = rScale * Float3(0.0f, i & 2 ? -1.0f : 1.0f, i & 1 ? -t : t);

			for (int i = 4; i < 8; i++)
				//v[ i ] = Vector( -(i&2), -(i&1)*t, 0 ) ; 
				vertices[i] = rScale * Float3(i & 2 ? -1.0f : 1.0f, i & 1 ? -t : t, 0.0f);

			for (int i = 8; i < 12; i++)
				//v[ i ] = Vector( -(i&1)*t, 0, -(i&2) ) ; 
				vertices[i] = rScale * Float3(i & 1 ? -t : t, 0.0f, i & 2 ? -1.0f : 1.0f);

			Float3 normal = Float3(0.0f);
			Push(Vertices, { vertices[0], normal }); Push(Vertices, { vertices[2], normal }); Push(Vertices, { vertices[8], normal });
			Push(Vertices, { vertices[0], normal }); Push(Vertices, { vertices[8], normal }); Push(Vertices, { vertices[4], normal });
			Push(Vertices, { vertices[0], normal }); Push(Vertices, { vertices[4], normal }); Push(Vertices, { vertices[6], normal });
			Push(Vertices, { vertices[0], normal }); Push(Vertices, { vertices[6], normal }); Push(Vertices, { vertices[9], normal });
			Push(Vertices, { vertices[0], normal }); Push(Vertices, { vertices[9], normal }); Push(Vertices, { vertices[2], normal });

			Push(Vertices, { vertices[2], normal }); Push(Vertices, { vertices[7], normal }); Push(Vertices, { vertices[5], normal });
			Push(Vertices, { vertices[2], normal }); Push(Vertices, { vertices[5], normal }); Push(Vertices, { vertices[8], normal });
			Push(Vertices, { vertices[2], normal }); Push(Vertices, { vertices[9], normal }); Push(Vertices, { vertices[7], normal });

			Push(Vertices, { vertices[8], normal }); Push(Vertices, { vertices[5], normal }); Push(Vertices, { vertices[10], normal });
			Push(Vertices, { vertices[8], normal }); Push(Vertices, { vertices[10], normal }); Push(Vertices, { vertices[4], normal });

			Push(Vertices, { vertices[10], normal }); Push(Vertices, { vertices[5], normal }); Push(Vertices, { vertices[3], normal });
			Push(Vertices, { vertices[10], normal }); Push(Vertices, { vertices[3], normal }); Push(Vertices, { vertices[1], normal });
			Push(Vertices, { vertices[10], normal }); Push(Vertices, { vertices[1], normal }); Push(Vertices, { vertices[4], normal });

			Push(Vertices, { vertices[1], normal }); Push(Vertices, { vertices[6], normal }); Push(Vertices, { vertices[4], normal });
			Push(Vertices, { vertices[1], normal }); Push(Vertices, { vertices[3], normal }); Push(Vertices, { vertices[11], normal });
			Push(Vertices, { vertices[1], normal }); Push(Vertices, { vertices[11], normal }); Push(Vertices, { vertices[6], normal });

			Push(Vertices, { vertices[6], normal }); Push(Vertices, { vertices[11], normal }); Push(Vertices, { vertices[9], normal });

			Push(Vertices, { vertices[11], normal }); Push(Vertices, { vertices[3], normal }); Push(Vertices, { vertices[7], normal });
			Push(Vertices, { vertices[11], normal }); Push(Vertices, { vertices[7], normal }); Push(Vertices, { vertices[9], normal });

			Push(Vertices, { vertices[3], normal }); Push(Vertices, { vertices[5], normal }); Push(Vertices, { vertices[7], normal });
		}
	}
}