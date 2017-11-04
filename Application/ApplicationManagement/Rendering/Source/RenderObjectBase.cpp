#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(SharedPtr<Transform> renderTransform)
			: RenderTransform(renderTransform)
		{
			SubscribeToRenderer();
		}

		RenderObjectBase::~RenderObjectBase()
		{
			UnsubscribeFromRenderer();
		}

		void RenderObjectBase::Update(Second dt)
		{
			// this will be used to handle animations and the like
		}

		void RenderObjectBase::SubscribeToRenderer()
		{

		}

		void RenderObjectBase::UnsubscribeFromRenderer()
		{

		}
	}
}