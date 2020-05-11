#include "ApplicationManagement\Geometric\Headers\Node.h"
#include "ApplicationManagement/Geometric/Headers/HierarchyComponent.h"
#include "ApplicationManagement/Geometric/Headers/ContentBase.h"

#include "ApplicationManagement/StateSystem/Headers/State.h"

#if _DEBUG
#include "ApplicationManagement/Headers/ApplicationManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"
#include "ApplicationManagement/Rendering/3D/Headers/SphereRenderObject.h"

#include "Resources/Assets.h"
#endif

namespace Application
{
	namespace Geometric
	{
		Node::Node(Ptr<State> parentState, Core::String name)
			:Node(parentState, nullptr, name, Float3(0.0f))
		{}

		Node::Node(Ptr<State> parentState, Ptr<Node> parentNode, Core::String name)
			: Node(parentState, parentNode, name, Float3(0.0f))
		{}

		Node::Node(Ptr<State> parentState, Float3 position, FQuaternion rotation, Float3 scale, bool settingLocal)
			: Node(parentState, DEFAULT_NODE_NAME, position, rotation, scale, settingLocal)
		{}

		Node::Node(Ptr<State> parentState, Ptr<Node> parentNode, Float3 position, FQuaternion rotation, Float3 scale, bool settingLocal)
			: Node(parentState, parentNode, DEFAULT_NODE_NAME, position, rotation, scale, settingLocal)
		{}

		Node::Node(Ptr<State> parentState, Core::String name, Float3 position, FQuaternion rotation, Float3 scale, bool settingLocal)
			: Node(parentState, nullptr, name, position, rotation, scale, settingLocal)
		{}

		Node::Node(Ptr<State> parentState, Ptr<Node> parentNode, Core::String name, Float3 position, FQuaternion rotation, Float3 scale, bool settingLocal)
			: Name(name)
			, Transformation((parentNode == nullptr ? nullptr : &(parentNode->Transformation)), position, rotation, scale, settingLocal)
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

			for (auto& child : Children)
			{
				child->Initialize();
			}
		}

		void Node::Start()
		{
			ContainerBase::Start();

			for (auto& child : Children)
			{
				child->Start();
			}

#if _DEBUG
			Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>());

			ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
			ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

			renderComponent->AddRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLUE, 0.5f);
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

			for (auto& child : Children)
			{
				child->End();
			}
		}

		void Node::CleanUp()
		{
			ContainerBase::CleanUp();

			for (auto& child : Children)
			{
				child->CleanUp();
			}
		}

		Ptr<ContentBase> Node::AddContent(UniquePtr<ContentBase> newContent)
		{
			Ptr<ContentBase> addedContent = ContainerBase::AddContent(move(newContent));

			addedContent->AddComponent<Hierarchy>(this);

			return addedContent;
		}

		Ptr<Node> Node::AddChild(UniquePtr<Node> newChild)
		{
			newChild->Transformation.SetParent(&Transformation);
			newChild->Initialize();
			// need to think about if we want Start to be called like this
			if (ApplicationManager::AppStateManager().GetActiveState() == ParentState)
			{
				newChild->Start();
			}

			Push(Children, move(newChild));

			return Children[Children.size() - 1].get();
		}

		Ptr<Node> Node::GetChild(Core::String name)
		{
			for (Core::size i = 0; i < Children.size(); i++)
			{
				if (Children[i]->Name == name)
				{
					return Children[i].get();
				}

				Ptr<Node> childInChildren = Children[i]->GetChild(name);
				if (childInChildren != nullptr)
				{
					return childInChildren;
				}
			}

			return nullptr;
		}

		// -1 means the child is not contained
		int Node::GetChildDepth(Core::String name)
		{
			int depth = Name == name ? 0 : -1;

			for (Core::size i = 0; i < Children.size(); i++)
			{
				if (Children[i]->Name == name)
				{
					depth++;
					break;
				}

				int childDepth = Children[i]->GetChildDepth(name);
				if (childDepth != -1)
				{
					depth += childDepth;
					break;
				}
			}

			return depth;
		}

		UniquePtr<Node> Node::RemoveChild(Ptr<Node> oldChild)
		{
			oldChild->Transformation.SetParent(nullptr);

			UniquePtr<Node> formerChild = nullptr;

			for (Core::size i = 0; i < Children.size(); i++)
			{
				if (Children[i].get() == oldChild)
				{
					formerChild = move(Children[i]);
					RemoveIndex(Children, i);
					break;
				}
			}

			return formerChild;
		}

		Core::Ptr<State> Node::GetParentState() const
		{
			return ParentState;
		}

		void Node::SetParentState(Core::Ptr<State> parentState)
		{
			ParentState = parentState;
		}

		int Node::GetSubNodeCount() const
		{
			int count = 0;
			for (int i = 0; i < Children.size(); i++)
			{
				count++;
				count += Children[i]->GetSubNodeCount();
			}

			return count;
		}
	}
}