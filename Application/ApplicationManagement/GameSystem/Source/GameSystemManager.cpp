#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

// debug/testing includes
#include "Core/Debugging/Headers/Macros.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/UtilityFunctions.h"

#include "ApplicationManagement/Rendering/Headers/Camera.h"
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

			RenderSystem.ObjectManager.AddRenderObject<Rendering::BoxRenderObject>(testTransform.get(), BLACK, Float2(1.5f));
			RenderSystem.ObjectManager.AddRenderObject<Rendering::CircleRenderObject>(testTransform.get(), WHITE, 2.0f);

			// should not need to set width/height! very dumb!
			RenderSystem.SetCamera(MakeShared<Rendering::Camera>(1024.0f / 800.0f));
		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);

			// something is wrong, objects are not rotating or moving, instead they seem to be getting clipped

			// movement test
			//testTransform->AdjustPosition(Float3(0.0f, 1.0f, 0.0f) * Duration(dt));

			// rotation test
			//FQuaternion quat = LerpQuat(testTransform->GetRotation(), FQuaternion(0.996f, 0.087f, 0.0f, 0.0f) * testTransform->GetRotation(), Duration(dt));
			//testTransform->SetRotation(quat);

			// scale test
			//Float3 newScale = Lerp(testTransform->GetScale(), testTransform->GetScale() * 1.05f, Duration(dt));
			//testTransform->SetScale(newScale);
		}

		void GameSystemManager::End()
		{

		}

		void GameSystemManager::CleanUp()
		{

		}
	}
}