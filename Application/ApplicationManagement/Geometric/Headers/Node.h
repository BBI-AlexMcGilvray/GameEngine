#pragma once

#include "Core/Geometric/Headers/Transform.h"

#include "ApplicationManagement/Geometric/Headers/ContainerBase.h"

using namespace Core::Geometric;

namespace Application
{
	namespace Geometric
	{
		// a recursive struct to hold elements in a scene
		struct Node : ContainerBase
		{
			Transform Transformation;

			Node();
			Node(Float3 position, FQuaternion rotation, Float3 scale);

			virtual ~Node();

			// generic functions that pass calls down to children and contents
			void Update(Second dt) override;

			// set children/parent
			template <typename T, typename ...Ts>
			SharedPtr<T> AddChild(Ts ...args)
			{
				SharedPtr<T> newNode = MakeShared<T>(Forward<Ts>(args)...);

				AddChild(newNode);

				return newNode;
			}

			virtual void AddChild(SharedPtr<Node> newChild);
			virtual void RemoveChild(SharedPtr<Node> oldChild);

		protected:
			List<SharedPtr<Node>> Children;
		};
	}
}