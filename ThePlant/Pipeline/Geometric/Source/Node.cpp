#include "Pipeline\Geometric\Headers\Node.h"
#include "Pipeline/Geometric/Headers/HierarchyComponent.h"
#include "Pipeline/Geometric/Headers/ContentBase.h"

#include "Pipeline/StateSystem/Headers/State.h"

#if _DEBUG
#include "Pipeline/Headers/ApplicationManager.h"
#endif

namespace Application {
namespace Geometric {
  Node::Node(Ptr<State> parentState, std::string name)
    : Node(parentState, nullptr, name, Core::Math::Float3(0.0f))
  {}

  Node::Node(Ptr<State> parentState, Ptr<Node> parentNode, std::string name)
    : Node(parentState, parentNode, name, Core::Math::Float3(0.0f))
  {}

  Node::Node(Ptr<State> parentState, Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale, bool settingLocal)
    : Node(parentState, DEFAULT_NODE_NAME, position, rotation, scale, settingLocal)
  {}

  Node::Node(Ptr<State> parentState, Ptr<Node> parentNode, Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale, bool settingLocal)
    : Node(parentState, parentNode, DEFAULT_NODE_NAME, position, rotation, scale, settingLocal)
  {}

  Node::Node(Ptr<State> parentState, std::string name, Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale, bool settingLocal)
    : Node(parentState, nullptr, name, position, rotation, scale, settingLocal)
  {}

  Node::Node(Ptr<State> parentState, Ptr<Node> parentNode, std::string name, Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale, bool settingLocal)
    : Name(name), Transformation(position, rotation, scale, (parentNode == nullptr ? nullptr : &(parentNode->Transformation)), settingLocal)
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

    for (auto &child : Children) {
      child->Initialize();
    }
  }

  void Node::Start()
  {
    ContainerBase::Start();

    for (auto &child : Children) {
      child->Start();
    }

#if _DEBUG
    // Ptr<ContentBase> debugContent = AddContent(MakeUnique<ContentBase>(ParentState));

    // ComponentPtr<Hierarchy> hierarchyComponent = debugContent->GetComponent<Hierarchy>();
    // ComponentPtr<Rendering::Render> renderComponent = debugContent->AddComponent<Rendering::Render>(ApplicationManager::AppRenderManager().GetObjectManagerForState(ParentState));

    // renderComponent->SetRenderObject<Rendering::SphereRenderObject>(&(hierarchyComponent->GetHeirarchyNode()->Transformation), BLUE, 0.5f);
#endif
  }

  void Node::Update(Second dt)
  {
    ContainerBase::Update(dt);

    for (auto &child : Children) {
      child->Update(dt);
    }
  }

  void Node::End()
  {
    ContainerBase::End();

    for (auto &child : Children) {
      child->End();
    }
  }

  void Node::CleanUp()
  {
    ContainerBase::CleanUp();

    for (auto &child : Children) {
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
    // should not be called here, unless called through templated version since that guarantees creation
    newChild->Initialize();
    // need to think about if we want Start to be called like this - likely should NOT be
    auto &test = ApplicationManager::AppStateManager();
    if (&(ApplicationManager::AppStateManager().GetActiveState()) == ParentState) // ParentState should be a REFERENCE, since it MUST exist and we will need a comparison operator
    {
      newChild->Start();
    }

    Children.push_back(move(newChild));

    return Children[Children.size() - 1].get();
  }

  Ptr<Node> Node::GetChild(std::string name)
  {
    for (Core::size i = 0; i < Children.size(); i++) {
      if (Children[i]->Name == name) {
        return Children[i].get();
      }

      Ptr<Node> childInChildren = Children[i]->GetChild(name);
      if (childInChildren != nullptr) {
        return childInChildren;
      }
    }

    return nullptr;
  }

  std::vector<Ptr<Node>> Node::GetChildren()
  {
    std::vector<Ptr<Node>> children(Children.size());

    for (int i = 0; i < Children.size(); i++) {
      children[i] = Children[i].get();
    }

    return children;
  }

  UniquePtr<Node> Node::RemoveChild(Ptr<Node> oldChild)
  {
    oldChild->Transformation.SetParent(nullptr);

    UniquePtr<Node> formerChild = nullptr;

    for (Core::size i = 0; i < Children.size(); i++) {
      if (Children[i].get() == oldChild) {
        formerChild = move(Children[i]);
        Children.erase(Children.begin() + i);
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
    for (int i = 0; i < Children.size(); i++) {
      count++;
      count += Children[i]->GetSubNodeCount();
    }

    return count;
  }
}// namespace Geometric
}// namespace Application