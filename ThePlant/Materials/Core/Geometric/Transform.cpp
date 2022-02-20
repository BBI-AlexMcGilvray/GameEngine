#pragma once

#include "Core/Geometric/Transform.h"

#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

using namespace Core::Math;

namespace Core {
namespace Geometric {
  Transform::Transform()
  : Transform(Float3(0.0f))
  {}
  
  Transform::Transform(FQuaternion rotation, Float3 scale)
  : Transform(Float3(0.0f), rotation, scale)
  {}

  Transform::Transform(Float3 position, FQuaternion rotation, Float3 scale)
  {
    SetPosition(position);
    SetRotation(rotation);
    SetScale(scale);
    _Dirty(true);
  }

  Transform::Transform(const Orientation& orientation)
  : _orientation(orientation)
  {
    _Dirty(true);
  }

  Transform::Transform(const Float4x4& transformationMatrix)
  {
    _SetFromTransformationMatrix(transformationMatrix);
  }

  Transform::Transform(const Transform &other)
  {
    SetPosition(other.GetPosition());
    SetRotation(other.GetRotation());
    SetScale(other.GetScale());
    _Dirty(true);
  }

  Transform &Transform::operator=(const Transform &other)
  {
    SetPosition(other.GetPosition());
    SetRotation(other.GetRotation());
    SetScale(other.GetScale());
    _Dirty(true);

    return *this;
  }

  Transform& Transform::operator=(const Orientation& orientation)
  {
    _orientation = orientation;
    _Dirty(true);

    return *this;
  }

  Transform& Transform::operator=(const Float4x4& transformationMatrix)
  {
    _SetFromTransformationMatrix(transformationMatrix);
    
    return *this;
  }

  void Transform::Reset()
  {
    SetPosition(Float3(0.0f));
    SetScale(Float3(1.0f));
    SetRotation(II());
  }

  Float4x4 Transform::GetTransformationMatrix()
  {
    _RecalculateTransformationMatrix();

    return _transformationMatrix;
  }

  Float4x4 Transform::GetInverseTransformationMatrix()
  {
    return Math::Inverse(GetTransformationMatrix());
  }

  void Transform::SetOrientation(const Orientation& orientation)
  {
    _orientation = orientation;
  }

  Orientation& Transform::GetOrientation()
  {
    return _orientation;
  }
    
  void Transform::SetPosition(const Float3 &position)
  {
    if (_orientation.position == position)
    {
      return;
    }

    _orientation.position = position;
    _Dirty();
  }

  void Transform::AdjustPosition(const Float3 &movement)
  {
    SetPosition(_orientation.position + movement);
  }

  Float3 Transform::GetPosition() const
  {
    return _orientation.position;
  }

  void Transform::SetRotation(const FQuaternion &rotation)
  {
    if (_orientation.rotation == rotation)
    {
      return;
    }

    _orientation.rotation = rotation;
    _Dirty(true);
  }

  void Transform::AdjustRotation(const FQuaternion &rotation)
  {
    SetRotation(rotation * _orientation.rotation);
  }

  FQuaternion Transform::GetRotation() const
  {
    return _orientation.rotation;
  }

  void Transform::SetScale(const float &scale)
  {
    SetScale(Float3(scale));
  }

  void Transform::SetScale(const Float3 &scale)
  {
    if (_orientation.scale == scale)
    {
      return;
    }

    _orientation.scale = scale;
    _Dirty();
  }

  void Transform::AdjustScale(const float &scale)
  {
    SetScale(_orientation.scale * scale);
  }

  void Transform::AdjustScale(const Float3 &scale)
  {
    SetScale(_orientation.scale * scale);
  }

  Float3 Transform::GetScale() const
  {
    return _orientation.scale;
  }

  bool Transform::IsDirty() const { return (_dirty || _rotationDirty); }

  bool Transform::operator==(const Transform& other) const
  {
    return _orientation == other._orientation;
  }
  
  bool Transform::operator!=(const Transform& other) const
  {
    return !(*this == other);
  }

  void Transform::_Dirty(bool rotation)
  {
    _dirty = true;
    _rotationDirty |= rotation;
  }

  void Transform::_SetFromTransformationMatrix(const Core::Math::Float4x4& transformationMatrix)
  {
    Float3 position;
    Float3 scale;
    FQuaternion rotation;

    TransformationMatrixDecomposition(transformationMatrix, position, scale, rotation);
    
    SetPosition(position);
    SetScale(scale);
    SetRotation(rotation);
    _Dirty(true);
  }

  Float3x3 Transform::_GetRotationMatrix()
  {
    _RecalculateRotationMatrix();

    return _rotationMatrix;
  }

  void Transform::_RecalculateRotationMatrix()
  {
    if (!_rotationDirty) {
      return;
    }

    _rotationMatrix = CalculateRotationMatrix(_orientation.rotation);
    _rotationDirty = false;
  }

  void Transform::_RecalculateTransformationMatrix()
  {
    if (!IsDirty()) {
      return;
    }

    _transformationMatrix = Float4x4(II{});

    // scale
    _transformationMatrix.E1.X = _orientation.scale.X;
    _transformationMatrix.E2.Y = _orientation.scale.Y;
    _transformationMatrix.E3.Z = _orientation.scale.Z;

    // rotation
    _transformationMatrix = Float4x4(_GetRotationMatrix(), Float4(0.0f, 0.0f, 0.0f, 1.0f)) * _transformationMatrix;

    // position
    _transformationMatrix.E4.X = _orientation.position.X;
    _transformationMatrix.E4.Y = _orientation.position.Y;
    _transformationMatrix.E4.Z = _orientation.position.Z;

    _dirty = false;
  }
}// namespace Geometric
}// namespace Core