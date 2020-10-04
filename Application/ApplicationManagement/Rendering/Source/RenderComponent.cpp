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

		Core::Ptr<RenderObjectBase> Render::AddRenderObject(Core::UniquePtr<RenderObjectBase> renderObject)
		{
			return AddRenderObject(RObjectManager->AddRenderObject(move(renderObject)));
		}

		Ptr<RenderObjectBase> Render::AddRenderObject(Ptr<RenderObjectBase> renderObject)
		{
			Push(RenderObjects, move(renderObject));

			return RenderObjects[RenderObjects.size() - 1];
		}

		void Render::RemoveRenderObject(Core::Ptr<RenderObjectBase> renderObject)
		{
			Remove(RenderObjects, renderObject);
			RObjectManager->RemoveRenderObject(renderObject);
		}
	}
}