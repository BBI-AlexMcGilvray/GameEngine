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
			if (_material != material.get())
			{
				RemoveMaterial();
			}

			_material = _materialManager->AddMaterial(move(material));

			return _material;
		}

		void MaterialComponent::RemoveMaterial()
		{
			// this needs to be changed to include
			// _materialManager->RemoveMaterial(_material)
			// that means that _materialManager will need to also include a reference counting implementation
			// could make all managers hold a type of reference counting implementation
			_material = nullptr;
		}
	}
}