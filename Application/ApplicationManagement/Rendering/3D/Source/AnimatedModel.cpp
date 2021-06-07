#include "ApplicationManagement/Rendering/3D/Headers/AnimatedModel.h"

#include "ApplicationManagement/Animation/Headers/Animator.h"

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
		{			
			_skeletonComponent = AddComponent<SkeletonComponent>();
			_renderComponent = AddComponent<Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(_onwningState));
			_materialComponent = AddComponent<MaterialComponent>(ApplicationManager::AppRenderManager().GetMaterialManagerForState(_onwningState));
			_animatorComponent = AddComponent<Animation::AnimatorComponent>(&ApplicationManager::AppAnimationManager()); // needs to be for a state (_owningState) in the future like the above, and not a ptr (like the above)
			_animatable = SkeletonAnimatable(*(_skeletonComponent->GetSkeleton()));
		}

		// be able to change what skeleton a model is listening to - returns true if able to map to skeleton
		bool AnimatedModel::SkinToSkeleton(Core::Ptr<Skeleton> skeleton)
		{
			_skeletonComponent->SetSkeleton(skeleton);
			_renderComponent->GetRenderObject<SkinnedMeshBase>()->Skin(skeleton);
			return true;
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
			ComponentPtr<Geometric::Hierarchy> hierarchyComponent = GetComponent<Geometric::Hierarchy>();
			_skeletonComponent->SetSkeleton<Skeleton>(_onwningState, hierarchyComponent->GetHeirarchyNode(), Data.Data.Skeleton);

			_materialComponent->SetMaterial<Material>(Data.Data.Material);
			// this should be in the material data, but is here for now
			_materialComponent->GetMaterial()->SetShader(&(ApplicationManager::AppRenderManager().ObjectShaderManager.DefaultSkinnedShader));

			Ptr<SkinnedMeshBase> mesh = _renderComponent->SetRenderObject<SkinnedMeshBase>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), Data.Data.Mesh);
			mesh->SetMaterialComponent(_materialComponent);

			SkinToSkeleton(_skeletonComponent->GetSkeleton());

			_animatorComponent->SetAnimator<Animation::Animator>(&_animatable);
			// add the animations from the skeleton data to the animator component
			// (maybe the skeleton component should be what adds the animation component? and the AnimatedModel pointer instead tries to get the component that is loaded up by the skeleton component)
			//for (Data::AssetName<Animation> animation : _skeletonComponent->GetSkeleton())
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