#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

namespace Application
{
	namespace Rendering
	{
		RenderObjectBase::RenderObjectBase(RenderManager& manager, Ptr<ObjectShaderBase> objectShader, SharedPtr<const Transform> renderTransform)
			: Manager(manager), RenderTransform(renderTransform), ObjectShader(objectShader)
		{

		}

		RenderObjectBase::~RenderObjectBase()
		{

		}

		void RenderObjectBase::Update(Second dt)
		{
			// this will be used to handle animations and the like
		}

		void RenderObjectBase::Render()
		{
			Prepare();
			Draw();
			CleanUp();
		}

		void RenderObjectBase::Prepare()
		{
			ObjectShader->Prepare();
		}

		void RenderObjectBase::Draw()
		{
			Manager.ObjectRenderer.Draw(this);
		}

		void RenderObjectBase::CleanUp()
		{
			ObjectShader->CleanUp();
		}
	}
}