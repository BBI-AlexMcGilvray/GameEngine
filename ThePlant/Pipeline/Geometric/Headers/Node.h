#pragma once

#include <string>
#include <vector>

#include "Core/Functionality/Headers/Event.h"

#include "Pipeline/Geometric/Headers/ContainerBase.h"
#include "Pipeline/Geometric/Headers/HierarchyTransform.h"

namespace Application {
struct State;

namespace Geometric {
/* / *********************************
		NOTE: Need to determine how we are going to have it set up so that moving one node moves all child nodes
		And, if this is something that we actually want.

		* Need to keep in mind that (for example) two changes in rotation should only change the rotation of the child by the delta
			(since it would already have applied the fist change)

		Options:
		- Update child nodes on Update
			- Pros:
				- Update done a single time
			- Const:
				- Multiple updates will cause over-transforming
				- REQUIRES update call to work

		- Have events that proc and are listened to for when parent transform has updated
			- Pros:
				- Updates handled automatically
				- Requires no update call, anything that changes parent will be taken into account
			- Cons:
				- Multiple changes will result in multiple calculations and over-transforming
		// *********************************/

// NOTE: We should remove the use of 'string' in here, should hash the names instead?
// a recursive struct to hold elements in a scene
#define DEFAULT_NODE_NAME "Unnamed"
  struct Node : ContainerBase
  {
    Event<> Deleted;

    std::string Name;
    Geometric::HierarchyTransform Transformation;

    Node(Core::Ptr<State> parentState, std::string name = DEFAULT_NODE_NAME);
    Node(Core::Ptr<State> parentState, Ptr<Node> parentNode, std::string name = DEFAULT_NODE_NAME);
    Node(Core::Ptr<State> parentState, Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(1.0f), bool settingLocal = false);
    Node(Core::Ptr<State> parentState, Ptr<Node> parentNode, Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(1.0f), bool settingLocal = false);
    Node(Core::Ptr<State> parentState, std::string name, Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(1.0f), bool settingLocal = false);
    Node(Core::Ptr<State> parentState, Ptr<Node> parentNode, std::string name, Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(1.0f), bool settingLocal = false);

    virtual ~Node();

    // add content
    template<typename T, typename... Ts>
    Ptr<T> AddContent(Ts &&...args)
    {
      UniquePtr<T> newNode = MakeUnique<T>(ParentState, std::forward<Ts>(args)...);

      return static_cast<Ptr<T>>(AddContent(move(newNode)));
    }
    Ptr<ContentBase> AddContent(UniquePtr<ContentBase> newContent) override;

    // generic functions that pass calls down to children and contents
    void Initialize() override;
    void Start() override;

    void Update(Second dt) override;

    void End() override;
    void CleanUp() override;

    // set children/parent
    template<typename T, typename... Ts>
    Ptr<T> AddChild(Ts &&...args)
    {
      UniquePtr<T> newNode = MakeUnique<T>(ParentState, this, std::forward<Ts>(args)...);

      Ptr<T> newChild = static_cast<Ptr<T>>(AddChild(move(newNode)));

      // should probably be called here?
      // newChild->Initialize();

      return newChild;
    }

    virtual Ptr<Node> AddChild(UniquePtr<Node> newChild);
    virtual Ptr<Node> GetChild(std::string name);
    std::vector<Ptr<Node>> GetChildren();
    virtual UniquePtr<Node> RemoveChild(Ptr<Node> oldChild);

    Core::Ptr<State> GetParentState() const;
    void SetParentState(Core::Ptr<State> parentState);

    int GetSubNodeCount() const;

  protected:
    std::vector<UniquePtr<Node>> Children;
    Core::Ptr<State> ParentState = nullptr;
  };
}// namespace Geometric
}// namespace Application