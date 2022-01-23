#pragma once

#include "Core/Math/Headers/Quaternion.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Matrix3x3.h"
#include "Core/Math/Headers/Matrix4x4.h"

namespace Core {
namespace Geometric {
  // should we just get rid of the interfaces? what else would really use them? probably best to remove for now - seems like an overengineered solution
  // Transform should only ever refer to 'world' relative data, and should not allow for 'local' variants. Extra methods should be removed, keep this class bare-bones
  //    - Perhaps include static functions to set 'relative to' another transform (that would need to be included in the function)
  struct Transform
  {
    // create constructor for each variation of data (position, rotation, scale)
    Transform();
    Transform(Core::Math::FQuaternion rotation, Core::Math::Float3 scale = Core::Math::Float3(1.0f));
    Transform(Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(), Core::Math::Float3 scale = Core::Math::Float3(1.0f));
    Transform::Transform(const Core::Math::Float4x4& transformationMatrix);

    Transform(const Transform &other);
    Transform &operator=(const Transform &other);
    Transform& operator=(const Core::Math::Float4x4& transformationMatrix);

    void Reset();

    // world-relative
    Core::Math::Float4x4 GetTransformationMatrix();
    Core::Math::Float4x4 GetInverseTransformationMatrix();

    // world-relative
    void SetPosition(const Core::Math::Float3 &position);
    void AdjustPosition(const Core::Math::Float3 &movement);
    Core::Math::Float3 GetPosition() const;

    // world-relative
    void SetRotation(const Core::Math::FQuaternion &rotation);
    void AdjustRotation(const Core::Math::FQuaternion &rotation);
    Core::Math::FQuaternion GetRotation() const;

    // world-relative
    void SetScale(const float &scale);
    void SetScale(const Core::Math::Float3 &scale);
    void AdjustScale(const float &scale);
    void AdjustScale(const Core::Math::Float3 &scale);
    Core::Math::Float3 GetScale() const;

    bool IsDirty() const;

    bool operator==(const Transform& other) const;
    bool operator!=(const Transform& other) const;

  protected:
    bool _dirty;
    bool _rotationDirty;

    // world-relative
    Core::Math::Float3 _position;
    Core::Math::FQuaternion _rotation;
    Core::Math::Float3 _scale;

    Core::Math::Float3x3 _rotationMatrix;
    Core::Math::Float4x4 _transformationMatrix;

    void _Dirty(bool rotation = false);

    void _SetFromTransformationMatrix(const Core::Math::Float4x4& transformationMatrix);

    Core::Math::Float3x3 _GetRotationMatrix();
    void _RecalculateRotationMatrix();
    void _RecalculateTransformationMatrix();
  };
}// namespace Geometric
}// namespace Core