#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

#include "Data/Headers/DataUtils.h"

namespace Application
{
	namespace Rendering
	{
		ModelBase::ModelBase(RenderManager& manager, SharedPtr<const Transform> renderTransform, String folderName)
			: RenderObjectBase(manager, renderTransform)
			, Mesh(Data::GetData<MeshBase>(folderName + ".msh"))
			, Shader(manager.ObjectShaderManager.DefaultShader)
		{
			// load material using mat file in folder
		}

		uint ModelBase::GetVertexCount() const
		{
			return Mesh.VertexCount;
		}

		void ModelBase::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Mesh.Prepare();
			Shader.Prepare(mvp, ObjectColor);
		}

		void ModelBase::CleanUp() const
		{
			Mesh.Cleanup();
			Shader.CleanUp();
		}
	}
}