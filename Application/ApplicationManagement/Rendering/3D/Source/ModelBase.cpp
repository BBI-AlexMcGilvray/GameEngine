#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

#include "Data/Headers/AssetUtils.h"

namespace Application
{
	namespace Rendering
	{
		ModelBase::ModelBase(RenderManager& manager, Ptr<const Transform> renderTransform, Data::AssetName<SimpleMeshBase> asset)
			: RenderObjectBase(manager, renderTransform)
			, Mesh(asset)
			, Shader(manager.ObjectShaderManager.DefaultShader)
		{
			// load material using mat file in folder
		}

		uint ModelBase::GetVertexCount() const
		{
			// again, should would be much easier with a DataPtr<T>
			return Mesh.Data->Data.VertexCount;
		}

		void ModelBase::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Mesh.Prepare();
			Shader.Prepare(mvp, ObjectColor);
		}

		void ModelBase::CleanUp() const
		{
			Mesh.CleanUp();
			Shader.CleanUp();
		}
	}
}