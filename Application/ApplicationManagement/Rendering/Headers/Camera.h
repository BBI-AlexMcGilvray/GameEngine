#pragma once

#include "Core/Geometric/Headers/Transform.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"

#include "Core/Math/Headers/Quaternion.h"

#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core;
using namespace Core::Geometric;
using namespace Core::Math;

namespace Application
{
	namespace Rendering
	{
		// anything needed for camera. should create specifications for perspective and orthographic
		struct Camera : Transform
		{
			static const Float3 DefaultDirection;

			Camera(const int& width, const int& height, const Float3& position = Float3(0.0f, 0.0f, 200.0f), const Float3& direction = Float3(0.0f, 0.0f, -1.0f));

			// these should be moved to being utility functions
			Float3 ScreenToWorld(const Float2& screenPosition);
			Float2 WorldToScreen(const Float3& worldPosition);

			Float4x4 GetTransformationMatrix() const override;

			Float3 SetScale(Float3 const& scale) override
			{
				ALERT("Cannot adjust scale for cameras");
				return Scale;
			}

			void LookAt(Float3 position);

			void SetFOVY(float fovy);

			void SetWidth(const int& width);
			void SetHeight(const int& height);
			void SetWidthHeight(const int& width, const int& height);

			void SetNearPlane(const float& nearPlane);
			void SetFarPlane(const float& farPlane);
			void SetPlanes(const float& nearPlane, const float& farPlane);

			void SetProjectionVariables(const float& fovy, const int& width, const int& height, const float& nearPlane, const float& farPlane);

		protected:
			Float3 Direction; // direction the camera is looking

			Float4x4 ProjectionMatrix;

			float AspectRatio;
			float FOVY = 1.57079f; // radian representation of 90 degrees
			int Width;
			int Height;

			float NearPlane = 0.1f;
			float FarPlane = 1000.0f;

			void RecalculateProjectionMatrix();
		};
	}
}