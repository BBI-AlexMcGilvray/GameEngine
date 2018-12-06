#include "ApplicationManagement\Rendering\3D\Headers\SimpleMeshBase.h"

#include "Data/Headers/AssetUtils.h"

namespace Application
{
	namespace Rendering
	{
		SimpleMeshBase::SimpleMeshBase()
		{}

		SimpleMeshBase::SimpleMeshBase(Data::AssetName<Data::Rendering::SimpleMeshData> asset)
			: Data(Data::GetAssetData(asset))
		{
			Initialize();
		}

		void SimpleMeshBase::Initialize()
		{
			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			// the Data->Data would go away with a DataPtr<T>
			glBufferData(newBuffer.Type, Data->Data.VertexCount * sizeof(Data::Rendering::VertexDataBase), &(Data->Data.Vertices[0]), GL_STATIC_DRAW);

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

		void SimpleMeshBase::Prepare() const
		{
			Vao.Bind();
		}

		void SimpleMeshBase::CleanUp() const
		{
			Vao.Unbind();
		}
	}
}