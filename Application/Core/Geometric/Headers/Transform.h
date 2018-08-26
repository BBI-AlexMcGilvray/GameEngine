#pragma once

#include "Core/Math/Headers/MathDefs.h"

#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Core/Math/Headers/Quaternion.h"

using namespace Core::Math;

namespace Core
{
	namespace Geometric
	{
		struct Transform
		{
			Transform();

			Transform(Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f));

			Float4x4 GetTransformationMatrix() const;

			Float3 AdjustPosition(Float3 const& movement);

			Float3 SetPosition(Float3 const& position);

			Float3 GetPosition() const;

			FQuaternion AdjustRotatation(FQuaternion const& rotation);

			FQuaternion SetRotation(FQuaternion const& rotation);

			FQuaternion GetRotation() const;
			Float3x3 GetRotationMatrix() const;

			Float3 AdjustScale(Float3 const& scale);

			Float3 SetScale(Float3 const& scale);

			Float3 GetScale() const;

		protected:
			Float3 Position;
			FQuaternion Rotation;
			Float3 Scale;

			Float3x3 RotationMatrix;

			void RecalculateRotationMatrix();
		};
	}
}