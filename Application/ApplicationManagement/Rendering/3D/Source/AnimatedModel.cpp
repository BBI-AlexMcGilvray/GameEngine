#include "ApplicationManagement/Rendering/3D/Headers/AnimatedModel.h"

#include "ApplicationManagement/Headers/ApplicationManager.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/3D/Headers/SkinnedMeshBase.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		AnimatedModel::AnimatedModel(const Core::Ptr<State> owningState, Core::Ptr<Geometric::Node> parentNode, Data::AssetName<Data::Rendering::AnimatedModelData> asset)
			: ContentBase(owningState)
			, Data(asset)
			, _transform(&(parentNode->Transformation))
			//, Material(Data.Data.Material)
			//, Mesh(Data.Data.Mesh)
			//, Shader(manager->ObjectShaderManager.DefaultSkinnedShader)
		{
			// this should probably be a component
			SkinnedSkeleton = MakeUnique<Skeleton>(parentNode, Data.Data.Skeleton);
			//Mesh.Skin(*SkinnedSkeleton);
			
			_renderComponent = AddComponent<Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(_onwningState));
			_materialComponent = AddComponent<MaterialComponent>(ApplicationManager::AppRenderManager().GetMaterialManagerForState(_onwningState));

			// should this be in the constructor? or left up to creators to call?
			Initialize();
		}

		// be able to change what skeleton a model is listening to - returns true if able to map to skeleton
		bool AnimatedModel::SkinToSkeleton(Core::UniquePtr<Skeleton> skeleton)
		{
			// change the mesh to use this skeleton bones (if they work) instead of the one it is currently using
			return false;
		}

		//Core::size AnimatedModel::GetVertexCount() const
		//{
		//	// again, should would be much easier with a DataPtr<T>
		//	return Mesh.RenderData.size();
		//}

		//void AnimatedModel::Prepare(const Float4x4& mvp, const Color& color) const
		//{
		//	Mesh.Prepare();
		//	Shader.SetSkinningInformation(SkinnedSkeleton->GetBoneMatrices());
		//	Shader.Prepare(mvp, color);
		//}

		//void AnimatedModel::CleanUp() const
		//{
		//	Mesh.CleanUp();
		//	Shader.CleanUp();
		//}

		void AnimatedModel::Initialize()
		{
			// create components
			_materialComponent->SetMaterial<Material>(Data.Data.Material);

			Ptr<SkinnedMeshBase> mesh = _renderComponent->SetRenderObject<SkinnedMeshBase>(_transform, Data.Data.Mesh);
			mesh->SetMaterialComponent(_materialComponent);
			mesh->Skin(*SkinnedSkeleton);
		}

		void AnimatedModel::Start()
		{

		}

		void AnimatedModel::Update(Core::Second dt)
		{

		}

		void AnimatedModel::End()
		{

		}

		void AnimatedModel::CleanUp()
		{
			// cleanup components
			_renderComponent->GetRenderObject<SkinnedMeshBase>()->ClearMaterialComponent();
			_renderComponent->RemoveRenderObject();
			_materialComponent->RemoveMaterial();
		}
	}
}