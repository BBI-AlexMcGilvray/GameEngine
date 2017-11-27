#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/ListDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Geometric/Headers/Transform.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "ApplicationManagement/Geometric/Headers/Container.h"
#include "ApplicationManagement/Rendering/Headers/Renderer.h"

using namespace Core;
using namespace Core::Geometric;

using namespace Application::Rendering;

namespace Application
{
	namespace Geometric
	{
		// a recursive struct to hold elements in a scene
		struct Node : Container
		{
			Node();
			Node(Float3 position, FQuaternion rotation, Float3 scale);

			virtual ~Node();

			// generic functions that pass calls down to children and contents
			void Update(Second dt) override;
			void Render(const Renderer& renderer, Float4x4 transformationMatrix) override;

			// set children/parent
			void AddChild(Ptr<Node> newChild);
			void RemoveChild(Ptr<Node> oldChild);

		protected:
			Ptr<Node> Parent;
			List<Ptr<Node>> Children;
		};
	}
}