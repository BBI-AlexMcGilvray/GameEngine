#pragma once

#include "Core/Geometric/Headers/Transform.h"
#include "Core/Functionality/Headers/Event.h"

#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

using namespace Core::Geometric;

namespace Application
{
	struct State;

	namespace Geometric
	{
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

		// a recursive struct to hold elements in a scene
		#define DEFAULT_NODE_NAME "Unnamed"
		struct Node : ContainerBase
		{
			Event<> Deleted;

			Core::String Name;
			Transform Transformation;

			Node(Core::Ptr<State> parentState, Core::String name = DEFAULT_NODE_NAME);
			Node(Core::Ptr<State> parentState, Ptr<Node> parentNode, Core::String name = DEFAULT_NODE_NAME);
			Node(Core::Ptr<State> parentState, Float3 position, FQuaternion rotation = FQuaternion(), Float3 scale = Float3(1.0f), bool settingLocal = false);
			Node(Core::Ptr<State> parentState, Ptr<Node> parentNode, Float3 position, FQuaternion rotation = FQuaternion(), Float3 scale = Float3(1.0f), bool settingLocal = false);
			Node(Core::Ptr<State> parentState, Core::String name, Float3 position, FQuaternion rotation = FQuaternion(), Float3 scale = Float3(1.0f), bool settingLocal = false);
			Node(Core::Ptr<State> parentState, Ptr<Node> parentNode, Core::String name, Float3 position, FQuaternion rotation = FQuaternion(), Float3 scale = Float3(1.0f), bool settingLocal = false);

			virtual ~Node();

			Ptr<ContentBase> AddContent(UniquePtr<ContentBase> newContent) override;

			// generic functions that pass calls down to children and contents
			void Initialize() override;
			void Start() override;

			void Update(Second dt) override;

			void End() override;
			void CleanUp() override;

			// set children/parent
			template <typename T, typename ...Ts>
			Ptr<T> AddChild(Ts&& ...args)
			{
				UniquePtr<T> newNode = MakeUnique<T>(ParentState, this, Forward<Ts>(args)...);

				return static_cast<Ptr<T>>(AddChild(move(newNode)));
			}

			virtual Ptr<Node> AddChild(UniquePtr<Node> newChild);
			virtual Ptr<Node> GetChild(Core::String name);
			virtual int GetChildDepth(Core::String name);
			virtual UniquePtr<Node> RemoveChild(Ptr<Node> oldChild);

			Core::Ptr<State> GetParentState() const;
			void SetParentState(Core::Ptr<State> parentState);

			int GetSubNodeCount() const;

		protected:
			List<UniquePtr<Node>> Children;
			Core::Ptr<State> ParentState = nullptr;
		};
	}
}