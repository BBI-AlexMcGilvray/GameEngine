#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

#include "ApplicationManagement/Rendering/2D/Headers/Material.h"
#include "ApplicationManagement/Rendering/3D/Headers/SimpleMeshBase.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		ModelBase::ModelBase(Core::Ptr<RenderManager> manager, Ptr<Transform> renderTransform, Data::AssetName<Data::Rendering::SimpleModelData> asset)
			//: RenderObjectBase(manager, renderTransform)
			: ContentBase()
			, Data(asset)
			, _transform(renderTransform)
			//, Mesh(Data.Data.Mesh)
			//, Shader(manager->ObjectShaderManager.DefaultShader)
		{
			// load material using mat file in folder
			_renderComponent = AddComponent<Render>(manager->GetObjectManagerForState(manager->GetActiveState()));
			_materialComponent = AddComponent<MaterialComponent>(manager->GetMaterialManagerForState(manager->GetActiveState()));
		}

		//Core::size ModelBase::GetVertexCount() const
		//{
		//	// again, should would be much easier with a DataPtr<T>
		//	return Mesh.Data.Data.VertexCount;
		//}

		//void ModelBase::Prepare(const Float4x4& mvp, const Color& color) const
		//{
		//	Mesh.Prepare();
		//	Shader.Prepare(mvp, color);
		//}

		//void ModelBase::CleanUp() const
		//{
		//	Mesh.CleanUp();
		//	Shader.CleanUp();
		//}

		void ModelBase::Initialize()
		{
			// create components
			_materialComponent->SetMaterial<Material>(Data.Data.Material);

			_renderComponent->SetRenderObject<SimpleMeshBase>(_transform, Data.Data.Mesh)->SetMaterialComponent(_materialComponent);
		}

		void ModelBase::Start()
		{

		}

		void ModelBase::Update(Core::Second dt)
		{

		}

		void ModelBase::End()
		{

		}

		void ModelBase::CleanUp()
		{
			// cleanup components
			_renderComponent->GetRenderObject<SimpleMeshBase>()->ClearMaterialComponent();
			_renderComponent->RemoveRenderObject();
			_materialComponent->RemoveMaterial();
		}
	}
}