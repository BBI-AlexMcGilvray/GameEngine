#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(RenderManager& manager, SharedPtr<const Transform> renderTransform, Color color)
			: ObjectColor(color)
			, Manager(manager), RenderTransform(renderTransform)
		{

		}

		RenderObjectBase::~RenderObjectBase()
		{

		}

		void RenderObjectBase::Update(Second dt)
		{
			// this will be used to handle animations and the like
		}

		void RenderObjectBase::Render(const Float4x4& mvp, const Color& color) const
		{
			auto renderMVP = mvp * RenderTransform->GetTransformationMatrix();

			Prepare(renderMVP, color);
			Draw();
			CleanUp();
		}

		void RenderObjectBase::Draw() const
		{
			Manager.ObjectRenderer.Draw(this);
		}
	}
}