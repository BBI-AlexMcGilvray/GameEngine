#include "ApplicationManagement\Rendering\3D\Headers\MeshBase.h"

namespace Application
{
	namespace Rendering
	{
		MeshBase::MeshBase()
		{}

		MeshBase::MeshBase(String fileName)
			: Data::Rendering::MeshData(fileName)
		{
			Initialize();
		}

		void MeshBase::Initialize()
		{
			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			glBufferData(newBuffer.Type, VertexCount * sizeof(Float3), &Vertices[0], GL_STATIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Float3), (void*)(0));

			Vao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(Vbos, newBuffer);
		}

		void MeshBase::Draw()
		{
			Vao.Bind();

			// call renderer to draw

			Vao.Unbind();
		}
	}
}