#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"

using namespace Core;

namespace Application
{
	namespace Geometric
	{
		Hierarchy::Hierarchy(Ptr<EntityBase> entity)
			: Hierarchy(entity, nullptr)
		{

		}

		Hierarchy::Hierarchy(Ptr<EntityBase> entity, Ptr<Node> hierarchyNode)
			: Component<Hierarchy>(entity)
			, HierarchyNode(hierarchyNode)
		{

		}
	}
}