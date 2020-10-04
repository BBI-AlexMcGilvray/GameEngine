#pragma once

#include "SDL2Manager.h"

#include "ApplicationManagement/Animation/Headers/AnimationManager.h"
#include "ApplicationManagement/StateSystem/Headers/StateManager.h"
#include "ApplicationManagement/Input/Headers/InputManager.h"
#include "ApplicationManagement/Rendering/Headers/RenderManager.h"
#include "ApplicationManagement/Time/Headers/TimeManager.h"

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

using namespace Application::Animation;
using namespace Application::Input;
using namespace Application::Rendering;
using namespace Application::Time;

using namespace Core::Functionality;

namespace Application
{
	struct ApplicationManager
	{
		static Core::Ptr<ApplicationManager> Application();

		static FixedStepTimeManager& AppTimeManager();
		static AnimationManager& AppAnimationManager();
		static RenderManager& AppRenderManager();
		static InputManager& AppInputManager();
		static StateManager& AppStateManager();

	private:
		// to make sure that constructor can't be called except through static Application() method to get instance
		struct ConstructorTag { ConstructorTag() = default; };
	public:
		ApplicationManager(ConstructorTag tag);

		void Run();

	private:
		// Note: the below are in an order such that they should only _possibly_ know about what is above them (as it would need to be for constructors...)
		SDL2Manager SDL;
		FixedStepTimeManager Time;
		AnimationManager AnimationSystem;
		RenderManager RenderSystem;
		InputManager InputSystem;
		StateManager StateSystem;

		Delegate<> OnQuit;
		bool Quit = false;

		static Core::UniquePtr<ApplicationManager> Instance;

		bool Initialize();
		void Start();
		bool Update();
		void End();
		void CleanUp();
	};
}