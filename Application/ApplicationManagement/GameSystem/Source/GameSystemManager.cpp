#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

// debug/testing includes
#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"
#include "ApplicationManagement/Rendering/2D/Headers/BoxRenderObject.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

namespace Application
{
	namespace GameSystem
	{
		GameSystemManager::GameSystemManager(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
			: RenderSystem(renderSystem), InputSystem(inputSystem)
		{

		}

		void GameSystemManager::Initialize()
		{

		}

		void GameSystemManager::Start()
		{
			// Debug test for rendering a model
			testTransform = MakeShared<Transform>();
			RenderSystem.ObjectManager.AddRenderObject<Rendering::ModelBase>(testTransform.get(), "MI");

			//RenderSystem.ObjectManager.AddRenderObject<Rendering::BoxRenderObject>(testTransform.get(), BLACK, Float2(1.5f));
			RenderSystem.ObjectManager.AddRenderObject<Rendering::CircleRenderObject>(testTransform.get(), WHITE, 1.5f);
		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);
		}

		void GameSystemManager::End()
		{

		}

		void GameSystemManager::CleanUp()
		{

		}
	}
}