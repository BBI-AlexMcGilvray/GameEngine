#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Matrix4x4.h"

#include "ApplicationManagement/Rendering/Headers/Renderer.h"

using namespace Core;
using namespace Core::Math;

using namespace Application::Rendering;

namespace Application
{
	namespace Geometric
	{
		struct Container;

		// generic class that can be inherited from for anything that needs to be stored inside a node
		struct Content
		{
			Content() = default;
			virtual ~Content() = default;

			// generic functions
			virtual void Update(Second dt) = 0;
			virtual void Render(const Renderer& renderer, Float4x4 transformationMatrix) = 0;

			virtual void OnContainerSet(Ptr<Container> parentContainer);
			virtual void OnContainerDeletion();

		protected:
			Ptr<Container> ParentContainer;
		};
	}
}