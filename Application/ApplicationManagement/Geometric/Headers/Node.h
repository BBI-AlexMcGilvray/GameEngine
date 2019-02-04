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
		// a recursive struct to hold elements in a scene
		struct Node : ContainerBase
		{
			Event<> Deleted;
			Transform Transformation;

			Node(Core::Ptr<State> parentState);
			Node(Core::Ptr<State> parentState, Float3 position, FQuaternion rotation = FQuaternion(), Float3 scale = Float3(1.0f));

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
			Ptr<Node> AddChild(Ts&& ...args)
			{
				UniquePtr<T> newNode = MakeUnique<T>(ParentState, Forward<Ts>(args)...);

				return AddChild(move(newNode));
			}

			virtual Ptr<Node> AddChild(UniquePtr<Node> newChild);
			virtual void RemoveChild(UniquePtr<Node> oldChild);

			Core::Ptr<State> GetParentState() const;
			void SetParentState(Core::Ptr<State> parentState);

		protected:
			List<UniquePtr<Node>> Children;
			Core::Ptr<State> ParentState = nullptr;
		};
	}
}