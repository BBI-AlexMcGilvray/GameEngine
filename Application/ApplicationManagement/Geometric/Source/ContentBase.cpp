#include "ApplicationManagement\Geometric\Headers\ContentBase.h"

#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

namespace Application
{
	namespace Geometric
	{
		void ContentBase::OnContainerSet(Ptr<ContainerBase> parentContainer)
		{
			// do nothing by default
		}

		void ContentBase::OnContainerDeletion()
		{
			// do nothing by default
		}
	}
}