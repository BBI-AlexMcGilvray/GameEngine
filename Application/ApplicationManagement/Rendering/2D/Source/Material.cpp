#include "ApplicationManagement/Rendering/2D/Headers/Material.h"

namespace Application
{
	namespace Rendering
	{
		Material::Material()
		{}

		Material::Material(Data::AssetName<Data::Rendering::MaterialData> asset)
			: Data::Rendering::MaterialData(asset)
		{}
	}
}