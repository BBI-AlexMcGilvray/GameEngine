#include "ApplicationManagement/Headers/Entity.h"

namespace Application
{
	EntityBase::~EntityBase()
	{
		OnDestroyed();
	}
}