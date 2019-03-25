#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"

using namespace Core;

namespace Application
{
	namespace Geometric
	{
		Hierarchy::Hierarchy(Ptr<EntityBase> entity)
			: Hierarchy(entity, nullptr)
		{}

		Hierarchy::Hierarchy(Ptr<EntityBase> entity, Ptr<Node> hierarchyNode)
			: Component<Hierarchy>(entity, this)
			, OnNodeDeleted([this]()
		{
			DeleteComponent();

			return false;
		})
			, HierarchyNode(hierarchyNode)
		{
			SetHierarchyNode(hierarchyNode);
		}

		void Hierarchy::SetHierarchyNode(Core::Ptr<Node> hierarchyNode)
		{
			if (hierarchyNode == nullptr)
			{
				return;
			}

			if (HierarchyNode != nullptr)
			{
				HierarchyNode->Deleted -= OnNodeDeleted;
			}

			HierarchyNode = hierarchyNode;

			if (HierarchyNode != nullptr)
			{
				HierarchyNode->Deleted += OnNodeDeleted;
			}
		}

		Core::Ptr<Node> Hierarchy::GetHeirarchyNode() const
		{
			return HierarchyNode;
		}
	}
}