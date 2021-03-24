#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		Render::Render(Core::Ptr<EntityBase> entity, Ptr<RenderObjectManager> renderManager)
			: Component<Render>(entity, this)
			, RObjectManager(renderManager)
		{

		}

		const Core::Ptr<RenderObjectBase> Render::GetRenderObject() const
		{
			return RenderObject;
		}

		Core::Ptr<RenderObjectBase> Render::SetRenderObject(Core::UniquePtr<RenderObjectBase> renderObject)
		{
			return SetRenderObject(RObjectManager->AddRenderObject(move(renderObject)));
		}

		Ptr<RenderObjectBase> Render::SetRenderObject(Ptr<RenderObjectBase> renderObject)
		{
			RenderObject = move(renderObject);

			return RenderObject;
		}

		void Render::RemoveRenderObject()
		{
			// RObjectManager->RemoveRenderObject(RenderObject)
			// should be changed to point to a reference (optionally?) so that we can reduce copies
			RObjectManager->RemoveRenderObject(RenderObject);
			RenderObject = nullptr;
		}
	}
}