#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(RenderManager& manager, SharedPtr<const Transform> renderTransform, Color color)
			: ObjectColor(color)
			, Manager(manager)
			, RenderTransform(renderTransform)
		{
			Push(DebugVertices, { Float3{ -50.0f, -50.0f, 0.0f }, Float3{ 0.0f } });
			Push(DebugVertices, { Float3{ -50.0f, 50.0f, 0.0f }, Float3{ 0.0f } });
			Push(DebugVertices, { Float3{ 50.0f, 50.0f, 0.0f }, Float3{ 0.0f } });
			
			Push(DebugVertices, { Float3{ 50.0f, 50.0f, 0.0f }, Float3{ 0.0f } });
			Push(DebugVertices, { Float3{ 50.0f, -50.0f, 0.0f }, Float3{ 0.0f } });
			Push(DebugVertices, { Float3{ -50.0f, -50.0f, 0.0f }, Float3{ 0.0f } });

			DebugVao.Generate();
			DebugVao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			glBufferData(newBuffer.Type, DebugVertices.size() * sizeof(Data::Rendering::VertexDataBase), &DebugVertices[0], GL_STATIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::VertexDataBase), (void*)(0));
			// normal
			glEnableVertexAttribArray(1); // this matches with object shader construction
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::VertexDataBase), (void*)(offsetof(Data::Rendering::VertexDataBase, Data::Rendering::VertexDataBase::Position)));

			DebugVao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(DebugVbos, newBuffer);
		}

		RenderObjectBase::~RenderObjectBase()
		{

		}

		void RenderObjectBase::Update(Second dt)
		{
			// this will be used to handle animations and the like
		}

		void RenderObjectBase::Render(const Float4x4& mvp, const Color& color) const
		{
			auto renderMVP = mvp * RenderTransform->GetTransformationMatrix();

			Prepare(renderMVP, color);
			Draw();
			CleanUp();
			
			// debug
			Color dummyColor = BLACK;
			Manager.ObjectShaderManager.DefaultShader.Prepare(renderMVP, dummyColor);
			DebugVao.Bind();

			Manager.ObjectRenderer.DrawTriangles(DebugVertices.size());
			Manager.ObjectRenderer.DrawLines(DebugVertices.size());

			DebugVao.Unbind();
			Manager.ObjectShaderManager.DefaultShader.CleanUp();
		}

		void RenderObjectBase::Draw() const
		{
			Manager.ObjectRenderer.Draw(this);
		}
	}
}