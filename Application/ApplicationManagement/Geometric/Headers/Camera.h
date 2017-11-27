#pragma once

#include "Core/Math/Headers/Vector2.h"

#include "ApplicationManagement/Geometric/Headers/Node.h"

namespace Application
{
	namespace Geometric
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct Camera : Node // inherits from node to have a transform, and to be able to be listed in the children of a scene (if needed?)
		{
			const Float3 DefaultDirection = Float3(0.0f, 0.0f, -1.0f);

			Float3 Position; // position of camera
			Float3 Direction; // direction the camera is looking

			FQuaternion Rotation;
			Float4x4 RotationMatrix;

			Float4x4 ProjectionMatrix;

			float AspectRatio;
			float FOVY = 0.785398f; // radian representation of 45 degrees
			int Width;
			int Height;

			float NearPlane = 0.1f;
			float FarPlane = 100.0f;

			Camera(const int& width, const int& height, const Float3& position = Float3(0.0f, 0.0f, 0.0f), const Float3& direction =Float3(0.0f, 0.0f, -1.0f));

			void Update(Second dt) override;
			void Render(const Renderer& renderer, Float4x4 transformationMatrix) override;

			// additional functions
			Float3 MouseToWorld(const Float2& screenPosition);
			Float2 WorldToMouse(const Float3& worldPosition);

			Float4x4 GetRenderMatrix();

		private:
			void RecalculateRotationMatrix();
			void RecalculateProjectionMatrix();
		};
	}
}