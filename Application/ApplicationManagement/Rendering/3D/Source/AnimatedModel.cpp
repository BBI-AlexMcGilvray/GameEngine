#include "ApplicationManagement/Rendering/3D/Headers/AnimatedModel.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		AnimatedModel::AnimatedModel(Ptr<RenderManager> manager, Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::AnimatedModelData> asset)
			: RenderObjectBase(manager, &(parentNode->Transformation))
			, Data(asset)
			, Material(Data.Data.Material)
			, Mesh(Data.Data.Mesh)
			, Shader(manager->ObjectShaderManager.DefaultSkinnedShader)
		{
			SkinnedSkeleton = MakeUnique<Skeleton>(parentNode, Data.Data.Skeleton);
		}

		// be able to change what skeleton a model is listening to - returns true if able to map to skeleton
		bool AnimatedModel::SkinToSkeleton(Core::UniquePtr<Skeleton> skeleton)
		{
			// change the mesh to use this skeleton bones (if they work) instead of the one it is currently using
			return false;
		}

		Core::size AnimatedModel::GetVertexCount() const
		{
			// again, should would be much easier with a DataPtr<T>
			return Mesh.Data.Data.VertexCount;
		}

		void AnimatedModel::Prepare(const Float4x4& mvp, const Color& color) const
		{
			Mesh.Prepare();
			Shader.Prepare(mvp, color);
		}

		void AnimatedModel::CleanUp() const
		{
			Mesh.CleanUp();
			Shader.CleanUp();
		}
	}
}