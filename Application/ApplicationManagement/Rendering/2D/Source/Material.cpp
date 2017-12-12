#include "ApplicationManagement/Rendering/2D/Headers/Material.h"

namespace Application
{
	namespace Rendering
	{
		Material::Material()
		{}

		Material::Material(String fileName)
			: Data::Rendering::MaterialData(fileName)
		{}
	}
}