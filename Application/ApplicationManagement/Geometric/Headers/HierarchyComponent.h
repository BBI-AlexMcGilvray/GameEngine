#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/Hash.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"
#include "ApplicationManagement/Headers/Component.h"

namespace Application
{
	namespace Geometric
	{
		// a recursive struct to hold elements in a scene
		struct Hierarchy : Component<Hierarchy>
		{
			Core::Ptr<Node> HierarchyNode = nullptr;

			Hierarchy(Core::Ptr<EntityBase> entity);
			Hierarchy(Core::Ptr<EntityBase> entity, Core::Ptr<Node> hierarchyNode);

			static Hash ClashHash()
			{
				return Core::HashValue("Hierarchy");
			}
		};
	}
}