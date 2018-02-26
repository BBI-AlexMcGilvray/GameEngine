#include "ApplicationManagement/Rendering/Headers/Camera.h"

#include "ApplicationManagement/Rendering/Headers/CameraUtils.h"

#include "Core/Math/Headers/MathUtils.h"
#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/VectorFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

#include "Core/Debugging/Headers/Macros.h"

namespace Application
{
	namespace Rendering
	{
		const Float3 Camera::DefaultDirection = Float3(0.0f, 0.0f, -1.0f);

		Camera::Camera(const int& width, const int& height, const Float3& position, const Float3& direction)
			: Transform(position, RotationBetweenVectors(DefaultDirection, direction))
		{
			Direction = Normalize(direction);

			SetProjectionVariables(FOVY, width, height, NearPlane, FarPlane);
		}

		Float3 Camera::ScreenToWorld(const Float2& screenPosition)
		{
			float worldX = screenPosition.X / Width * 2.0f - 1.0f;
			float worldY = 1.0f - screenPosition.Y / Height * 2.0f;

			Float4x4 inverseMVP = GetTransformationMatrix();

			Float4 worldPosition = inverseMVP * Float4(worldX, worldY, 0.0f, 1.0f);

			return Float3(worldPosition.X, worldPosition.Y, worldPosition.Z) / worldPosition.W;
			
			// This gives the world coordinate of clicked area. Using the vector of camera->this (given by: this - camera) you
			// can calculate the coordinates that would be found at y = 0.

			// Note: Create a ray class that has a direction and origin and can test for intersection & find the values when an axis (typically y) is 0
		}

		Float2 Camera::WorldToScreen(const Float3& worldPosition)
		{
			Float4x4 MVP = GetTransformationMatrix();
			Float4 transformedPosition = MVP * Float4(worldPosition, 1.0f);

			float screenX = transformedPosition.X / transformedPosition.Z; // scaled down based on distance from 0 x
			float screenY = transformedPosition.Y / transformedPosition.Z; // scaled down based on distance from 0 y

			screenX = (screenX + 1.f) * 0.5f * Width;
			screenY = (1.0f - screenY) * 0.5f * Height; // y goes from top to bottom in screen space

			return Float2(screenX, screenY);
		}

		Float4x4 Camera::GetTransformationMatrix() const
		{
			// Reference: http://www.ntu.edu.sg/home/ehchua/programming/opengl/cg_basicstheory.html
			Float4x4 transformationMatrix(II{});

			// rotation
			Float4x4 inverseRotationMatrix = Float4x4(Inverse(RotationMatrix), Float4(0.0f, 0.0f, 0.0f, 1.0f));
			transformationMatrix = inverseRotationMatrix * transformationMatrix;

			// position
			Float4 rotatedPosition = inverseRotationMatrix * Float4(Position, 1.0f);
			transformationMatrix.E4.X = -Position.X;
			transformationMatrix.E4.Y = -Position.Y;
			transformationMatrix.E4.Z = -Position.Z;
			transformationMatrix.E4.W = 1.0f;

			// projection
			transformationMatrix = ProjectionMatrix * transformationMatrix;

			return transformationMatrix;
		}

		void Camera::LookAt(Float3 position)
		{
			Direction = Normalize(position - Position);

			SetRotation(RotationBetweenVectors(DefaultDirection, Direction));
		}

		void Camera::SetFOVY(float fovy)
		{
			FOVY = fovy;

			RecalculateProjectionMatrix();
		}

		void Camera::SetWidth(const int& width)
		{
			SetWidthHeight(width, Height);
		}

		void Camera::SetHeight(const int& height)
		{
			SetWidthHeight(Width, height);
		}

		void Camera::SetWidthHeight(const int& width, const int& height)
		{
			Width = width;
			Height = height;

			AspectRatio = (float(Width) / float(Height));

			RecalculateProjectionMatrix();
		}

		void Camera::SetNearPlane(const float& nearPlane)
		{
			SetPlanes(nearPlane, FarPlane);
		}

		void Camera::SetFarPlane(const float& farPlane)
		{
			SetPlanes(NearPlane, farPlane);
		}

		void Camera::SetPlanes(const float& nearPlane, const float& farPlane)
		{
			NearPlane = nearPlane;
			FarPlane = farPlane;

			RecalculateProjectionMatrix();
		}

		void Camera::SetProjectionVariables(const float& fovy, const int& width, const int& height, const float& nearPlane, const float& farPlane)
		{
			FOVY = fovy;

			Width = width;
			Height = height;

			AspectRatio = (float(Width) / float(Height));

			NearPlane = nearPlane;
			FarPlane = farPlane;

			RecalculateProjectionMatrix();
		}

		void Camera::RecalculateProjectionMatrix()
		{
			ProjectionMatrix = CalculatePerspectiveMatrix(FOVY, AspectRatio, NearPlane, FarPlane);
		}
	}
}