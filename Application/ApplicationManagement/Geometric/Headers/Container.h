#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Matrix4x4.h"

#include "ApplicationManagement/Rendering/Headers/Renderer.h"

using namespace Core;
using namespace Core::Math;

using namespace Application;
using namespace Application::Rendering;

namespace Application
{
	namespace Geometric
	{
		struct Content;

		// generic class that can be inherited from for anything that needs to be stored inside a node
		struct Container
		{
			Container();

			virtual ~Container();

			virtual void Update(Second dt);
			virtual void Render(Renderer& renderer, Float4x4 transformationMatrix);

			void AddContent(SharedPtr<Content> newContent);
			void RemoveContent(SharedPtr<Content> oldContent);

		protected:
			List<SharedPtr<Content>> ContainerContents;
		};
	}
}