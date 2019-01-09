#pragma once

#include "Core/Geometric/Headers/Transform.h"
#include "Core/Functionality/Headers/Event.h"

#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

using namespace Core::Geometric;

namespace Application
{
	namespace Geometric
	{
		// a recursive struct to hold elements in a scene
		struct Node : ContainerBase
		{
			Event<> Deleted;
			Transform Transformation;

			Node();
			Node(Float3 position, FQuaternion rotation = FQuaternion(), Float3 scale = Float3(1.0f));

			virtual ~Node();

			Ptr<ContentBase> AddContent(UniquePtr<ContentBase> newContent) override;

			// generic functions that pass calls down to children and contents
			void Initialize() override;
			void Start() override;
			bool firstUpdate = false; // THIS IS ONLY FOR DEBUGGING
			void Update(Second dt) override;
			void End() override;
			void CleanUp() override;

			// set children/parent
			template <typename T, typename ...Ts>
			UniquePtr<T> AddChild(Ts ...args)
			{
				UniquePtr<T> newNode = MakeUnique<T>(Forward<Ts>(args)...);

				AddChild(newNode);

				return newNode;
			}

			virtual void AddChild(UniquePtr<Node> newChild);
			virtual void RemoveChild(UniquePtr<Node> oldChild);

		protected:
			List<UniquePtr<Node>> Children;
		};
	}
}