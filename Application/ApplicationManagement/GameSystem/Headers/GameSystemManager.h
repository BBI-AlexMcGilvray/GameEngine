#pragma once

#include "Core/Headers/ListDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TimeDefs.h"

#include "Core/Functionality/Headers/Scheduler.h"

#include "ApplicationManagement/GameSystem/Headers/GameObjectManager.h"

#include "ApplicationManagement/Input/Headers/InputManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderObjectManager.h"
#include "ApplicationManagement/Collision/Headers/CollisionManager.h"

using namespace Core;
using namespace Core::Functionality;

using namespace Application::GameSystem::Collision;

namespace Application
{
	struct State;

	// debug
	struct Rendering::Camera;

	namespace GameSystem
	{
		struct GameSystemManager
		{
			const Ptr<State> ParentState;

			SchedulerBase Scheduler;
			GameObjectManager ObjectManager;
			Rendering::RenderObjectManager RObjectManager;
			//CollisionManager CollisionSystem;

			// the game system manager should hold onto the current 'scene' and be able to switch between scenes (in order to load different game states)

			GameSystemManager(Ptr<State> parentState, Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem);

			void Initialize();
			void Start();
			void Update(Second dt);
			void End();
			void CleanUp();

		private:
			// needs the render system to make changes on a game level. Ex: setting dead screen to red and the like
			Rendering::RenderManager& RenderSystem;
			Input::InputManager& InputSystem;

			// debug/testing
			UniquePtr<Rendering::Camera> testCamera;
		};
	}
}