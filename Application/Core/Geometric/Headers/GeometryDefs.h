#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"

#include "Core/Math/Headers/MathDefs.h"

#include "Core/Math/Headers/Matrix2x2.h"
#include "Core/Math/Headers/Matrix3x3.h"

#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"

#include "Core/Math/Headers/Quaternion.h"

using namespace Core::Math;

namespace Core
{
	namespace Geometric
	{
		struct Geometry
		{};

		// 2D

		struct ITranslatable2D
		{
			virtual void SetPosition(const Float2& position) = 0;
			virtual void AdjustPosition(const Float2& adjustment) = 0;

			virtual Float2 GetPosition() const = 0;
		};

		struct IRotatable2D
		{
			virtual void SetRotation(const FQuaternion& rotation) = 0;
			virtual void AdjustRotation(const FQuaternion& adjustment) = 0;

			virtual FQuaternion GetRotation() const = 0;
		};

		struct IScalable2D
		{
			virtual void SetScale(const float& scale) = 0;
			virtual void SetScale(const Float2& scale) = 0;
			virtual void AdjustScale(const float& adjustment) = 0;
			virtual void AdjustScale(const Float2& adjustment) = 0;

			virtual Float2 GetScale() const = 0;
		};

		// 3D

		struct ITranslatable3D
		{
			virtual void SetPosition(const Float3& position) = 0;
			virtual void AdjustPosition(const Float3& adjustment) = 0;

			virtual Float3 GetPosition() const = 0;
		};

		struct IRotatable3D
		{
			virtual void SetRotation(const FQuaternion& rotation) = 0;
			virtual void AdjustRotation(const FQuaternion& adjustment) = 0;

			virtual FQuaternion GetRotation() const = 0;
		};

		struct IScalable3D
		{
			virtual void SetScale(const float& scale) = 0;
			virtual void SetScale(const Float3& scale) = 0;
			virtual void AdjustScale(const float& adjustment) = 0;
			virtual void AdjustScale(const Float3& adjustment) = 0;

			virtual Float3 GetScale() const = 0;
		};

		struct Geometry3D : Geometry, ITranslatable3D, IRotatable3D, IScalable3D
		{

		};
	}
}