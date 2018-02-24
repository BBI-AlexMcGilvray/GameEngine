#pragma once

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct Camera // should make camera inherit from Transform, should make Transform functions be virtual
		{
			const Float3 DefaultDirection = Float3(0.0f, 0.0f, -1.0f);

			Float3 Position; // position of camera
			Float3 Direction; // direction the camera is looking

			FQuaternion Rotation;
			Float3x3 RotationMatrix;

			Float4x4 ProjectionMatrix;

			float AspectRatio;
			float FOVY = 0.785398f; // radian representation of 45 degrees
			int Width;
			int Height;

			float NearPlane = 0.1f;
			float FarPlane = 1000.0f;

			Camera(const int& width, const int& height, const Float3& position = Float3(0.0f, 0.0f, 200.0f), const Float3& direction = Float3(0.0f, 0.0f, -1.0f));

			// additional functions
			Float3 MouseToWorld(const Float2& screenPosition);
			Float2 WorldToMouse(const Float3& worldPosition);

			Float4x4 GetRenderMatrix() const;

			void SetPosition(Float3 position);
			void AdjustPosition(Float3 adjustment);

			void SetRotation(FQuaternion rotation);
			void AdjustRotation(FQuaternion adjustment);

			void LookAt(Float3 position);

		private:
			void RecalculateRotationMatrix();
			void RecalculateProjectionMatrix();
		};
	}
}