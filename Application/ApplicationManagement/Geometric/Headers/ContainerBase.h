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
		struct ContentBase;

		// generic class that can be inherited from for anything that needs to be stored inside a node
		struct ContainerBase
		{
			ContainerBase();

			virtual ~ContainerBase();

			virtual void Update(Second dt);
			// if rendering is going to be handled as a UniquePtr in the RenderObjectManager, then we may not even need this render call?
			virtual void Render(Renderer& renderer, Float4x4 transformationMatrix) const;

			template <typename T, typename ...Ts>
			void SetContent(Ts ...args)
			{
				SetContent(MakeUnique<T>(Forward<Ts>(args)...));
			}

			void SetContent(UniquePtr<ContentBase> newContent);
			void RemoveContent();

		protected:
			UniquePtr<ContentBase> Content;
		};
	}
}