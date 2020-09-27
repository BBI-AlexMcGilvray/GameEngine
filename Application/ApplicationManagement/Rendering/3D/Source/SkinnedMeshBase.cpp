#include "ApplicationManagement/Rendering/3D/Headers/SkinnedMeshBase.h"

// testing
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Debugging/Headers/Macros.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		SkinnedMeshBase::SkinnedMeshBase(Data::AssetName<Data::Rendering::AnimatedMeshData> asset)
			: Data(asset)
		{
			CreateRenderData();
			Initialize();
		}

		SkinnedMeshBase::~SkinnedMeshBase()
		{
			Vao.Delete();
			for (int i = 0; i < Vbos.size(); i++)
			{
				Vbos[i].Delete();
			}
		}

		void SkinnedMeshBase::Initialize()
		{
			Vao.Generate();
			Vao.Bind();

			auto newBuffer = GLBuffer(0, GL_ARRAY_BUFFER);
			newBuffer.Generate();
			newBuffer.Bind();

			// glBufferData( < type >, < size of data >, < start of data >, < draw type >); // GL_DYNAMIC_DRAW because Skin(...) could be called multiple times, changing indices
			glBufferData(newBuffer.Type, RenderData.size() * sizeof(Application::Rendering::AnimatedVertexRenderDataBase), &(RenderData[0]), GL_DYNAMIC_DRAW);

			// glVertexAttribPointer(< vertex attrib array >, < number of ... >, < ... type of element >, < normalized? >, < new vertex every sizeof(<>) >, < offset of attribute >);
			// position
			glEnableVertexAttribArray(0); // this matches with object shader construction
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void*)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::Position)));
			// normal
			glEnableVertexAttribArray(1); // this matches with object shader construction
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void*)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::Normal)));
			// bone weight
			glEnableVertexAttribArray(2); // this matches with object shader construction
			glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void*)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::BoneWeight)));
			// bone indices
			glEnableVertexAttribArray(3); // this matches with object shader construction
			glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(Application::Rendering::AnimatedVertexRenderDataBase), (void*)(offsetof(Application::Rendering::AnimatedVertexRenderDataBase, Application::Rendering::AnimatedVertexRenderDataBase::BoneIndices)));

			Vao.Unbind(); // must be done first, as it stores the states of the binded vbos
			newBuffer.Unbind();
			glDisableVertexAttribArray(0);

			Push(Vbos, newBuffer);

			// keep track of mesh data to write to
			MappedMesh = GLMappedBuffer(&Vbos[0]);
		}

		void SkinnedMeshBase::Prepare() const
		{
			Vao.Bind();
		}

		void SkinnedMeshBase::CleanUp() const
		{
			Vao.Unbind();
		}

		void SkinnedMeshBase::Skin(const Skeleton& skeleton)
		{
			for (int i = 0; i < Data.Data.Vertices.size(); i++)
			{
				Data::Rendering::AnimatedVertexDataBase vertexData = Data.Data.Vertices[i];
				Application::Rendering::AnimatedVertexRenderDataBase vertexRenderData = RenderData[i];

				if (i == 2262)
				{
					LOG("Trying to get bone index for 2262");
				}
				if (i == 2337)
				{
					LOG("Trying to get bone index for 2337");
				}

				int bonesPerVert = 4;
				for (int j = 0; j < bonesPerVert; j++)
				{
					if (j < vertexData.BoneName.size() && vertexData.BoneName[j] != "")
					{
						vertexRenderData.BoneIndices[j] = skeleton.GetIndexOf(vertexData.BoneName[j]);
					}
					else
					{
						// unused bone indices should be zeroed out by the weight
						vertexRenderData.BoneIndices[j] = 0;
					}
				}

				if (i == 2262)
				{
					LOG("Index 2262: BoneIndices: " + Core::Math::VectorString(vertexRenderData.BoneIndices));
				}
				if (i == 2337)
				{
					LOG("Index 2337: BoneIndices: " + Core::Math::VectorString(vertexRenderData.BoneIndices));
				}

				RenderData[i] = vertexRenderData;
			}

			// Update the data in the opengl buffer
			MappedMesh.Map(GL_WRITE_ONLY);
			MappedMesh.Assign(&(RenderData[0]), RenderData.size() * sizeof(Application::Rendering::AnimatedVertexRenderDataBase));
			MappedMesh.Unmap();
		}

		void SkinnedMeshBase::CreateRenderData()
		{
			for (int i = 0; i < Data.Data.Vertices.size(); i++)
			{
				Push(RenderData, AnimatedVertexRenderDataBase(Data.Data.Vertices[i]));
			}
		}
	}
}