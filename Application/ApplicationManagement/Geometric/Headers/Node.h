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
			void Render(Renderer& renderer, Float4x4 transformationMatrix) const override;

			// set children/parent
			template <typename T, typename ...Ts>
			void AddChild(Ts ...args)
			{
				AddChild(MakeShared<T>(Forward<Ts>(args)...));
			}

			virtual void AddChild(SharedPtr<Node> newChild);
			virtual void RemoveChild(SharedPtr<Node> oldChild);

		protected:
			List<SharedPtr<Node>> Children;
		};
	}
}