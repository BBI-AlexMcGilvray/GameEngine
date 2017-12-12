#include "ApplicationManagement\Rendering\3D\Headers\MeshBase.h"

namespace Application
{
	namespace Rendering
	{
		MeshBase::MeshBase()
		{}

		MeshBase::MeshBase(String fileName)
			: Data::Rendering::MeshData(fileName)
		{
			// set up vbo/vaos
		}
	}
}