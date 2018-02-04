#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

#include "Data/Headers/DataUtils.h"

namespace Application
{
	namespace Rendering
	{
		ModelBase::ModelBase(String folderName, RenderManager& manager, SharedPtr<const Transform> renderTransform)
			: RenderObjectBase(manager, renderTransform)
			, mesh(Data::GetData<MeshBase>(folderName + ".msh"))
			, Shader(manager.ObjectShaderManager.DefaultShader)
		{
			// load material using mat file in folder
		}

		uint ModelBase::GetVertexCount() const
		{
			return mesh.VertexCount;
		}

		void ModelBase::Prepare(const Float4x4& mvp, const Color& color) const
		{
			mesh.Prepare();
			Shader.Prepare(mvp, ObjectColor);
		}

		void ModelBase::CleanUp() const
		{
			mesh.Cleanup();
			Shader.CleanUp();
		}
	}
}