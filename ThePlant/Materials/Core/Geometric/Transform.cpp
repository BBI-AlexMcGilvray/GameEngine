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
  }

  Transform &Transform::operator=(const Transform &other)
  {
    SetPosition(other.GetPosition());
    SetRotation(other.GetRotation());
    SetScale(other.GetScale());

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

  void Transform::SetPosition(const Float3 &position)
  {
    if (_position == position)
    {
      return;
    }

    _position = position;
    _Dirty();
  }

  void Transform::AdjustPosition(const Float3 &movement)
  {
    SetPosition(_position + movement);
  }

  Float3 Transform::GetPosition() const
  {
    return _position;
  }

  void Transform::SetRotation(const FQuaternion &rotation)
  {
    if (_rotation == rotation)
    {
      return;
    }

    _rotation = rotation;
    _Dirty(true);
  }

  void Transform::AdjustRotation(const FQuaternion &rotation)
  {
    SetRotation(rotation * _rotation);
  }

  FQuaternion Transform::GetRotation() const
  {
    return _rotation;
  }

  void Transform::SetScale(const float &scale)
  {
    SetScale(Float3(scale));
  }

  void Transform::SetScale(const Float3 &scale)
  {
    if (_scale == scale)
    {
      return;
    }

    _scale = scale;
    _Dirty();
  }

  void Transform::AdjustScale(const float &scale)
  {
    SetScale(_scale * scale);
  }

  void Transform::AdjustScale(const Float3 &scale)
  {
    SetScale(_scale * scale);
  }

  Float3 Transform::GetScale() const
  {
    return _scale;
  }

  bool Transform::IsDirty() const { return (_dirty || _rotationDirty); }

  bool Transform::operator==(const Transform& other) const
  {
    return (_position == other._position
          && _rotation == other._rotation
          && _scale == other._scale);
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

    _rotationMatrix = CalculateRotationMatrix(_rotation);
    _rotationDirty = false;
  }

  void Transform::_RecalculateTransformationMatrix()
  {
    if (!IsDirty()) {
      return;
    }

    _transformationMatrix = Float4x4(II{});

    // scale
    _transformationMatrix.E1.X = _scale.X;
    _transformationMatrix.E2.Y = _scale.Y;
    _transformationMatrix.E3.Z = _scale.Z;

    // rotation
    _transformationMatrix = Float4x4(_GetRotationMatrix(), Float4(0.0f, 0.0f, 0.0f, 1.0f)) * _transformationMatrix;

    // position
    _transformationMatrix.E4.X = _position.X;
    _transformationMatrix.E4.Y = _position.Y;
    _transformationMatrix.E4.Z = _position.Z;

    _dirty = false;
  }
}// namespace Geometric
}// namespace Core