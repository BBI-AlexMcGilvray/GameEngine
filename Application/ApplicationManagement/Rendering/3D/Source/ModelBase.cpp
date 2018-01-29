#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"

#include "Data/Headers/DataUtils.h"

namespace Application
{
	namespace Rendering
	{
		ModelBase::ModelBase(String folderName)
			: mesh(Data::GetData<MeshBase>(folderName + ".msh"))
		{
			// load material using mat file in folder
			// load mesh using mesh file in folder
		}

		void ModelBase::Render()
		{
			Prepare();

			// draw

			Cleanup();
		}

		void ModelBase::Prepare()
		{
			mesh.Prepare();
		}

		void ModelBase::Cleanup()
		{
			mesh.Cleanup();
		}
	}
}