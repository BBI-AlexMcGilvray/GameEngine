#include "ApplicationManagement/Geometric/Headers/Camera.h"

namespace Application
{
	namespace Geometric
	{
		Camera::Camera(const int& width, const int& height, const Float3& position, const Float3& direction)
		{
			Position = position;
			Direction = direction;
			//Direction.Normalize(); // this is breaking for some reason

			FQuaternion newRotation;// = glm::rotation(DefaultDirection, Direction); // rotation takes normalized vectors
		}

		void Camera::Update(Second dt)
		{
			Node::Update(dt);
		}

		void Camera::Render(const Renderer& renderer, Float4x4 transformationMatrix)
		{
			// make this the currently used camera
			//auto previousCamera = renderer->GetCamera();
			//renderer->SetCamera(this);

			Node::Render(renderer, transformationMatrix);

			// switch back to previous camera
			//renderer->SetCamera(previousCamera);
		}

		Float3 Camera::MouseToWorld(const Float2& screenPosition)
		{
			float worldX = screenPosition.X / Width * 2.0f - 1.0f;
			float worldY = 1.0f - screenPosition.Y / Height * 2.0f;

			Float4x4 inverseMVP;// = glm::inverse(GetRenderMatrix());

			Float4 worldPosition;// = inverseMVP * Float4(worldX, worldY, 0.0f, 1.0f);

			return Float3();// (worldPosition.X, worldPosition.Y, worldPosition.Z) / worldPosition.W;
			
			// This gives the world coordinate of clicked area. Using the vector of camera->this (given by: this - camera) you
			// can calculate the coordinates that would be found at y = 0.

			// Note: Create a ray class that has a direction and origin and can test for intersection & find the values when an axis (typically y) is 0=
		}

		Float2 Camera::WorldToMouse(const Float3& worldPosition)
		{
			Float4x4 MVP = GetRenderMatrix();
			Float3 transformedPosition;// = MVP * Float4(worldPosition, 1.0f);

			float screenX = transformedPosition.X / transformedPosition.Z; // scaled down based on distance from 0 x
			float screenY = transformedPosition.Y / transformedPosition.Z; // scaled down based on distance from 0 y

			screenX = (screenX + 1.f) * 0.5f * Width;
			screenY = (1.0f - screenY) * 0.5f * Height; // y goes from top to bottom in screen space

			return Float2(screenX, screenY);
		}

		Float4x4 Camera::GetRenderMatrix()
		{
			// Reference: http://www.ntu.edu.sg/home/ehchua/programming/opengl/cg_basicstheory.html
			Float4x4 transformationMatrix(1.0f);
			// set translation portion
			{
				transformationMatrix[3][0] = -Position.X;
				transformationMatrix[3][1] = -Position.Y;
				transformationMatrix[3][2] = -Position.Z;
			}
			transformationMatrix = RotationMatrix * transformationMatrix; // rotate it

			return /*ProjectionMatrix * */transformationMatrix;
		}

		void Camera::RecalculateRotationMatrix()
		{
			//RotationMatrix = glm::toMat4(glm::conjugate(Rotation));
		}

		void Camera::RecalculateProjectionMatrix()
		{
			//ProjectionMatrix = glm::perspective(FOVY, AspectRatio, NearPlane, FarPlane);
		}
	}
}