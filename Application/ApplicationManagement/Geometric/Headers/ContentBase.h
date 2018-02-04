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
		struct ContainerBase;

		// generic class that can be inherited from for anything that needs to be stored inside a node
		struct ContentBase
		{
			ContentBase() = default;
			virtual ~ContentBase() = default;

			// generic functions
			virtual void Update(Second dt) = 0;
			virtual void Render(const Renderer& renderer, Float4x4 transformationMatrix) = 0;

			virtual void OnContainerSet(Ptr<ContainerBase> parentContainer);
			virtual void OnContainerDeletion();
		};
	}
}