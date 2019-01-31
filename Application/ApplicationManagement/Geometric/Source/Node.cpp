#include "ApplicationManagement\Geometric\Headers\Node.h"
#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#include "ApplicationManagement/StateSystem/Headers/State.h"

#if _DEBUG
#include "ApplicationManagement/Headers/ApplicationManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

#include "Resources/Assets.h"
#endif

namespace Application
{
	namespace Geometric
	{
		Node::Node(Ptr<State> parentState)
		{
			SetParentState(parentState);
		}

		Node::Node(Ptr<State> parentState, Float3 position, FQuaternion rotation, Float3 scale)
			: Transformation(position, rotation, scale)
		{
			SetParentState(parentState);
		}

		Node::~Node()
		{
			Deleted();
		}

		void Node::Initialize()
		{
			ContainerBase::Initialize();
		}

		void Node::Start()
		{
			ContainerBase::Start();

#if _DEBUG
			// debug
			Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>());

			ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderSystem().GetObjectManagerForState(ParentState));

			renderComponent->AddRenderObject<Rendering::ModelBase>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), Data::Ast.spmdl.MI_0);
			renderComponent->AddRenderObject<Rendering::CircleRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLUE, 0.25f);
#endif
		}

		void Node::Update(Second dt)
		{
			ContainerBase::Update(dt);
			
			for (auto& child : Children)
			{
				child->Update(dt);
			}
		}

		void Node::End()
		{
			ContainerBase::End();
		}

		void Node::CleanUp()
		{
			ContainerBase::CleanUp();
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

		Core::Ptr<State> Node::GetParentState() const
		{
			return ParentState;
		}

		void Node::SetParentState(Core::Ptr<State> parentState)
		{
			ParentState = parentState;
		}
	}
}