#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		struct RenderObjectBase;

		// holds all render objects, handles updating them and passing them in to be rendered
		struct RenderObjectManager
		{
			virtual void Initialize();

			virtual void Update(Second dt);
			virtual void Render(const Float4x4& mvp, const Color& color);

			virtual void CleanUp();

			template <typename T, typename ...Ts>
			SharedPtr<T> AddRenderObject(Ts ...args)
			{
				T newRenderObject = MakeShared<T>(Forward<Ts>(args)...);

				AddRenderObject(newRenderObject);

				return newRenderObject;
			}

			virtual void AddRenderObject(SharedPtr<RenderObjectBase> renderObject);
			virtual void RemoveRenderObject(SharedPtr<RenderObjectBase> renderObject);

		private:
			List<SharedPtr<RenderObjectBase>> RenderObjects;
		};
	}
}