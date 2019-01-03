#include "ApplicationManagement/Rendering/Headers/RenderComponent.h"

using namespace Core;

namespace Application
{
	namespace Rendering
	{
		Render::Render(Core::Ptr<EntityBase> entity, RenderObjectManager& renderManager)
			: Component<Render>(entity)
			, RObjectManager(renderManager)
		{

		}

		void Render::RemoveRenderObject(Core::Ptr<RenderObjectBase> renderObject)
		{
			RObjectManager.RemoveRenderObject(renderObject);
		}
	}
}