#include "ApplicationManagement/Rendering/2D/Headers/MaterialComponent.h"

#include "ApplicationManagement/Rendering/Headers/MaterialManager.h"

namespace Application
{
	namespace Rendering
	{
		MaterialComponent::MaterialComponent(Core::Ptr<EntityBase> entity, Core::Ptr<MaterialManager> materialManager)
			: Component<MaterialComponent>(entity, this)
			, _materialManager(materialManager)
		{

		}

		const Core::Ptr<Material> MaterialComponent::GetMaterial() const
		{
			return _material;
		}

		Core::Ptr<Material> MaterialComponent::SetMaterial(Core::UniquePtr<Material> material)
		{
#if _DEBUG
			if (_material != nullptr)
			{
				LOG("Replacing a non-null material");
			}
#endif
			_material = _materialManager->AddMaterial(move(material));

			return _material;
		}

		void MaterialComponent::RemoveMaterial(Core::Ptr<Material> material)
		{
			if (_material == material)
			{
				_material = nullptr;
			}
		}
	}
}