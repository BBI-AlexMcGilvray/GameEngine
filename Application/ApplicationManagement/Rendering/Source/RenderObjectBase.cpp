#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

#include "ApplicationManagement/Rendering/Headers/RenderManager.h"

#include "Core/Math/Headers/MatrixFunctions.h"

using namespace Core;
using namespace Core::Math;
using namespace Core::Geometric;
using namespace Core::Functionality;

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(Core::Ptr<RenderManager> manager, Ptr<const Transform> renderTransform, Color color)
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
			// this will be used to handle (mesh/texture) animations and the like
		}

		void RenderObjectBase::Render(Ptr<RenderManager> manager, const Float4x4& mvp, const Color& color) const
		{
			auto renderMVP = mvp * RenderTransform->GetTransformationMatrix();
			
			Prepare(renderMVP, color * ObjectColor);
			Draw(manager);
			CleanUp();
		}

		void RenderObjectBase::Draw(Ptr<RenderManager> manager) const
		{
			manager->ObjectRenderer.Draw(this);
		}
	}
}