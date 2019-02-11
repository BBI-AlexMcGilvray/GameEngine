#include "ApplicationManagement/Rendering/3D/Headers/SkinnedMeshBase.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		SkinnedMeshBase::SkinnedMeshBase(Data::AssetName<Data::Rendering::AnimatedMeshData> asset)
			: Data(asset)
		{
			Initialize();
		}

		void SkinnedMeshBase::Initialize()
		{
			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >);
			// the Data->Data would go away with a DataPtr<T>
			glBufferData(newBuffer.Type, Data.Data.VertexCount * sizeof(Data::Rendering::AnimatedVertexDataBase), &(Data.Data.Vertices[0]), GL_STATIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::AnimatedVertexDataBase), (void*)(0));
			// normal
			glEnableVertexAttribArray(1); // this matches with object shader construction
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Data::Rendering::AnimatedVertexDataBase), (void*)(offsetof(Data::Rendering::AnimatedVertexDataBase, Data::Rendering::AnimatedVertexDataBase::Position)));

			Vao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(Vbos, newBuffer);
		}

		void SkinnedMeshBase::Prepare() const
		{
			Vao.Bind();
		}

		void SkinnedMeshBase::CleanUp() const
		{
			Vao.Unbind();
		}
	}
}