#include "ApplicationManagement/Rendering/2D/Headers/BoxRenderObject.h"

namespace Application
{
	namespace Rendering
	{
		BoxRenderObject::BoxRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color)
			: BoxRenderObject(manager, renderTransform, color, Float2(1.0f))
		{}

		BoxRenderObject::BoxRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color,float width, float height)
			: BoxRenderObject(manager, renderTransform, color, Float2(width, height))
		{}

		BoxRenderObject::BoxRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color, Float2 scale)
			: RenderObjectBase(manager, renderTransform, color)
			, Scale(scale)
			, Shader(manager.ObjectShaderManager.DefaultShader)
		{
			Initialize();
		}

		void BoxRenderObject::Initialize()
		{
			Float3 center = RenderTransform->GetPosition();

			Push(Vertices, { Float3{ center.X - Scale.X, center.Y - Scale.Y, 0.0f }, Float3{ 0.0f } });
			Push(Vertices, { Float3{ center.X - Scale.X, center.Y + Scale.Y, 0.0f }, Float3{ 0.0f } });
			Push(Vertices, { Float3{ center.X + Scale.X, center.Y + Scale.Y, 0.0f }, Float3{ 0.0f } });

			Push(Vertices, { Float3{ center.X + Scale.X, center.Y + Scale.Y, 0.0f }, Float3{ 0.0f } });
			Push(Vertices, { Float3{ center.X + Scale.X, center.Y - Scale.Y, 0.0f }, Float3{ 0.0f } });
			Push(Vertices, { Float3{ center.X - Scale.X, center.Y - Scale.Y, 0.0f }, Float3{ 0.0f } });

			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			glBufferData(newBuffer.Type, Vertices.size() * sizeof(Data::Rendering::VertexDataBase), &Vertices[0], GL_STATIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::VertexDataBase), (void*)(0));
			// normal
			glEnableVertexAttribArray(1); // this matches with object shader construction
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::VertexDataBase), (void*)(offsetof(Data::Rendering::VertexDataBase, Data::Rendering::VertexDataBase::Position)));

			Vao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(Vbos, newBuffer);
		}

		void BoxRenderObject::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Vao.Bind();
			Shader.Prepare(mvp, ObjectColor);
		}

		void BoxRenderObject::CleanUp() const
		{
			Vao.Unbind();
			Shader.CleanUp();
		}
	}
}