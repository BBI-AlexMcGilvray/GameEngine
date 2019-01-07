#include "ApplicationManagement/GameSystem/Headers/GameSystemManager.h"

// debug/testing includes
#include "Core/Debugging/Headers/Macros.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/UtilityFunctions.h"

#include "ApplicationManagement/Rendering/Headers/Camera.h"
#include "ApplicationManagement/Rendering/3D/Headers/ModelBase.h"
#include "ApplicationManagement/Rendering/2D/Headers/BoxRenderObject.h"
#include "ApplicationManagement/Rendering/2D/Headers/CircleRenderObject.h"

#include "Resources/Assets.h"

namespace Application
{
	namespace GameSystem
	{
		GameSystemManager::GameSystemManager(Rendering::RenderManager& renderSystem, Input::InputManager& inputSystem)
			: RObjectManager(&renderSystem), RenderSystem(renderSystem), InputSystem(inputSystem)
		{

		}

		void GameSystemManager::Initialize()
		{
			RObjectManager.Initialize();

			testCamera = MakeUnique<Rendering::Camera>(1024.0f / 800.0f);
			RenderSystem.SetCamera(testCamera.get());

			// Debug test for rendering a model
			testTransform = MakeShared<Transform>();
			RObjectManager.AddRenderObject<Rendering::ModelBase>(testTransform.get(), Data::Ast.spmdl.MI_0);

			RObjectManager.AddRenderObject<Rendering::BoxRenderObject>(testTransform.get(), BLACK, Float2(1.5f));
			RObjectManager.AddRenderObject<Rendering::CircleRenderObject>(testTransform.get(), WHITE, 2.0f);
		}

		void GameSystemManager::Start()
		{
			RObjectManager.Start();
			RenderSystem.AttachRenderObjectManager(&RObjectManager);
		}

		void GameSystemManager::Update(Second dt)
		{
			Scheduler.Update(dt);
			ObjectManager.Update(dt);

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
			RenderSystem.DettachRenderObjectManager(&RObjectManager);
			RObjectManager.End();
		}

		void GameSystemManager::CleanUp()
		{
			RObjectManager.CleanUp();
		}
	}
}