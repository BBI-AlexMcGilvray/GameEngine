#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"

#include "ApplicationManagement/Rendering/Headers/RenderObjectBase.h"

// debug includes
#include "Core/Math/Headers/MatrixFunctions.h"

namespace Application
{
	namespace Rendering
	{
		RenderObjectManager::RenderObjectManager(Ptr<RenderManager> manager)
			: Manager(manager)
		{

		}

		void RenderObjectManager::Initialize()
		{

		}

		void RenderObjectManager::Update(Second dt)
		{
			for (auto& renderObject : RenderObjects)
			{
				renderObject->Update(dt);
			}
		}

		void RenderObjectManager::Render(const Float4x4& mvp, const Color& color)
		{
			// as noted in AddRenderObject, we will need to update this to having multiple lists and render them accordingly
			std::cout << "MVP Matrix: " << MatrixString(mvp) << std::endl;
			for (auto& renderObject : RenderObjects)
			{
				renderObject->Render(mvp, color);
			}
		}

		void RenderObjectManager::CleanUp()
		{

		}

		void RenderObjectManager::AddRenderObject(SharedPtr<RenderObjectBase> renderObject)
		{
			// we will need some handling here for render objects to have types (animated, stagnant, alpha, solid) to be able to put them into different lists
			// for efficiency and general handling (ex: only update animated, alpha has to be rendered last IN Z ORDER to ensure correct rendering)

			Push(RenderObjects, renderObject);
		}

		void RenderObjectManager::RemoveRenderObject(SharedPtr<RenderObjectBase> renderObject)
		{
			Remove(RenderObjects, renderObject);
		}
	}
}