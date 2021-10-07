#pragma once

#include "Core/Functionality/Headers/Event.h"
#include "Core/Geometric/Headers/GeometryDefs.h"
#include "Core/Math/Headers/Matrix4x4.h"

using namespace Core::Math;

namespace Core {
namespace Geometric {
  // should we just get rid of the interfaces? what else would really use them? probably best to remove for now - seems like an overengineered solution
  // Transform should only ever refer to 'world' relative data, and should not allow for 'local' variants. Extra methods should be removed, keep this class bare-bones
  //    - Perhaps include one function to set 'relative to' another transform (that would need to be included in the function)
  struct Transform : public ITranslatable3D
    , public IRotatable3D
    , public IScalable3D
  {
    // create constructor for each variation of data (position, rotation, scale)
    Transform();
    Transform(FQuaternion rotation, Float3 scale = Float3(1.0f));
    Transform(Float3 position, FQuaternion rotation = FQuaternion(II{}), Float3 scale = Float3(1.0f));

    Transform(const Transform &other);
    Transform &operator=(const Transform &other);

    // world-relative
    Float4x4 GetTransformationMatrix();
    Float4x4 GetInverseTransformationMatrix();

    // world-relative
    void SetPositionRelativeTo(const Transform& other, const Float3& relativePosition); // needed?
    void SetPosition(const Float3 &position);
    void AdjustPosition(const Float3 &movement);
    Float3 GetPosition() const;

    // world-relative
    void SetRotationRelativeTo(const Transform& other, const FQuaternion& relativeRotation); // needed?
    void SetRotation(const FQuaternion &rotation);
    void AdjustRotation(const FQuaternion &rotation);
    FQuaternion GetRotation() const;

    // world-relative
    void SetScaleRelativeTo(const Transform& other, const Float3& relativeScale); // needed?
    void SetScale(const float &scale);
    void SetScale(const Float3 &scale);
    void AdjustScale(const float &scale);
    void AdjustScale(const Float3 &scale);
    Float3 GetScale() const;

    // needed? meant to automatically adjust everything to a new 'origin'
    // should probably be a static method and return a Transform
    void MakeRelativeTo(const Transform& other);
    // need a variation of the below to match the various constructors
    static Transform MakeRelativeTransform(const Transform& base, const Float3& relativePosition);

    bool IsDirty() const;

  protected:
    bool _dirty;
    bool _rotationDirty;

    // world-relative
    Float3 _position;
    FQuaternion _rotation;
    Float3 _scale;

    Float3x3 _rotationMatrix;
    Float4x4 _transformationMatrix;

    void _Dirty(bool rotation = false);

    Float3x3 _GetRotationMatrix();
    void _RecalculateRotationMatrix();
    void _RecalculateTransformationMatrix();
  };
}// namespace Geometric
}// namespace Core