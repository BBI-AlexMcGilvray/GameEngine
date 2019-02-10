#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		ModelBase::ModelBase(Core::Ptr<RenderManager> manager, Ptr<const Transform> renderTransform, Data::AssetName<Data::Rendering::SimpleModelData> asset)
			: RenderObjectBase(manager, renderTransform)
			, Data(asset)
			, Mesh(Data.Data.Mesh)
			, Shader(manager->ObjectShaderManager.DefaultShader)
		{
			// load material using mat file in folder
		}

		Core::size ModelBase::GetVertexCount() const
		{
			// again, should would be much easier with a DataPtr<T>
			return Mesh.Data.Data.VertexCount;
		}

		void ModelBase::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Mesh.Prepare();
			Shader.Prepare(mvp, color);
		}

		void ModelBase::CleanUp() const
		{
			Mesh.CleanUp();
			Shader.CleanUp();
		}
	}
}