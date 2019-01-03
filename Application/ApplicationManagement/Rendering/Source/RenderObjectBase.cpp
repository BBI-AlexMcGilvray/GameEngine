#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "Core/Math/Headers/MatrixFunctions.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Functionality;

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(RenderManager& manager, Ptr<const Transform> renderTransform, Color color)
			: ObjectColor(color)
			, Manager(manager)
			, RenderTransform(renderTransform)
		{
		}

		RenderObjectBase::~RenderObjectBase()
		{
			Delete();
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