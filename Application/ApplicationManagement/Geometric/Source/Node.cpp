#include "ApplicationManagement\Geometric\Headers\Node.h"
#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

// debug
#include "ApplicationManagement/Headers/ApplicationManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

#include "Resources/Assets.h"

namespace Application
{
	namespace Geometric
	{
		Node::Node()
		{

		}

		Node::Node(Float3 position, FQuaternion rotation, Float3 scale)
			: Transformation(position, rotation, scale)
		{

		}

		Node::~Node()
		{
			Deleted();
		}

		void Node::Initialize()
		{
			// NEED TO SORT OUT THE ORDERING, SINCE AT THIS POINT THE RENDER SYSTEM DOES NOT EXIST
		}

		void Node::Start()
		{
			// NEED TO SORT OUT THE ORDERING, SINCE AT THIS POINT THE OBJECT MANAGER OF THE RENDER SYSTEM HAS NOT BEEN SET
		}

		// generic functions that pass calls down to children and contents
		void Node::Update(Second dt)
		{
			// we really need to implement a DEBUG macro
			if (!firstUpdate)
			{
				firstUpdate = true;

				// debug
				Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>());

				ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
				ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderSystem().ObjectManager);

				renderComponent->AddRenderObject<Rendering::ModelBase>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), Data::Ast.spmdl.MI_0);
				renderComponent->AddRenderObject<Rendering::CircleRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLUE, 1.0f);
			}
			ContainerBase::Update(dt);
			
			for (auto& child : Children)
			{
				child->Update(dt);
			}
		}

		void Node::End()
		{

		}

		void Node::CleanUp()
		{

		}

		Ptr<ContentBase> Node::AddContent(UniquePtr<ContentBase> newContent)
		{
			Ptr<ContentBase> addedContent = ContainerBase::AddContent(move(newContent));

			addedContent->AddComponent<Hierarchy>(this);

			return addedContent;
		}

		void Node::AddChild(UniquePtr<Node> newChild)
		{
			Push(Children, move(newChild));
		}

		void Node::RemoveChild(UniquePtr<Node> oldChild)
		{
			Remove(Children, move(oldChild));
		}
	}
}