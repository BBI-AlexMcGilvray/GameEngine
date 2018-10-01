#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

namespace Application
{
	namespace Rendering
	{
		CircleRenderObject::CircleRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color)
			: CircleRenderObject(manager, renderTransform, color, 1.0f)
		{}

		CircleRenderObject::CircleRenderObject(RenderManager& manager, Ptr<const Transform> renderTransform, Color color, float radius)
			: RenderObjectBase(manager, renderTransform, color)
			, Radius(radius)
			, Shader(manager.ObjectShaderManager.DefaultShader)
		{
			Initialize();
		}

		void CircleRenderObject::Initialize()
		{
			Float3 center = RenderTransform->GetPosition();
			float stepCountPerQuadrant = 20.0f;

			auto createVertices = [this, center, stepCountPerQuadrant](bool positiveX, bool positiveY)
			{
				for (float i = 0.0f; i < stepCountPerQuadrant; i++)
				{
					if (int(i) % 2 == 0)
					{
						Push(Vertices, { Float3{ center.X, center.Y, 0.0f }, Float3{ 0.0f } });
					}

					float xRatio = positiveX ? (positiveY ? i : stepCountPerQuadrant - i) : (positiveY ? stepCountPerQuadrant - i : i);
					float xPercent = xRatio / stepCountPerQuadrant;

					float xPos = center.X + (xPercent * (positiveX ? Radius : -Radius));
					float yPos = center.Y + ((1.0f - xPercent) * (positiveY ? Radius : -Radius));

					Push(Vertices, { Float3{ xPos, yPos, 0.0f }, Float3{ 0.0f } });
				}
			};

			createVertices(false, true);
			createVertices(true, true);
			createVertices(true, false);
			createVertices(false, false);

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

		void CircleRenderObject::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Vao.Bind();
			Shader.Prepare(mvp, ObjectColor);
		}

		void CircleRenderObject::CleanUp() const
		{
			Vao.Unbind();
			Shader.CleanUp();
		}
	}
}