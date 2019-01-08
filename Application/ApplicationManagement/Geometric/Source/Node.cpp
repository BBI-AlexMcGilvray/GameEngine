#include "ApplicationManagement\Geometric\Headers\Node.h"
#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

// debug
#include "ApplicationManagement/Headers/ApplicationManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

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
			// debug
			Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>());
			// figure out why these break
			ComponentPtr<Rendering::Render> debugComponent = debugContent->AddComponent<Rendering::Render>(*(ApplicationManager::AppRenderSystem().ObjectManager));
			//debugComponent->AddRenderObject<Rendering::CircleRenderObject>(&(debugContent->GetComponent<Hierarchy>()->GetHeirarchyNode()->Transformation), BLUE);
		}

		// generic functions that pass calls down to children and contents
		void Node::Update(Second dt)
		{
			ContainerBase::Update(dt);
			
			for (auto& child : Children)
			{
				child->Update(dt);
			}
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