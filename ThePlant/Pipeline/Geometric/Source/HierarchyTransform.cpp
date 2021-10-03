#include "Pipeline/Geometric/Headers/HierarchyTransform.h"

namespace Application {
namespace Geometric {
    HierarchyTransform::HierarchyTransform(Core::Ptr<HierarchyTransform> parent)
    : HierarchyTransform(Core::Geometric::Transform(), parent)
    {}

    HierarchyTransform::HierarchyTransform(Core::Math::Float3 position, Core::Math::FQuaternion rotation, Core::Math::Float3 scale, Core::Ptr<HierarchyTransform> parent, bool settingLocal)
    : HierarchyTransform(Core::Geometric::Transform(position, rotation, scale), parent, settingLocal)
    {}

    HierarchyTransform::HierarchyTransform(const Core::Geometric::Transform& transform, Core::Ptr<HierarchyTransform> parent, bool settingLocal)
    {
        if (settingLocal)
        {
            // Transforms are non-local by default
            SetLocalPosition(transform.GetPosition());
            SetLocalRotation(transform.GetRotation());
            SetLocalScale(transform.GetScale());
        }
        else
        {
            _transform = transform;
        }
        _parent = parent;
    }
    
    // parent-relative
    Core::Math::Float4x4 HierarchyTransform::GetLocalTransformationMatrix();
    Core::Math::Float4x4 HierarchyTransform::GetInverseLocalTransformationMatrix();
    // world-relative
    Core::Math::Float4x4 HierarchyTransform::GetWorldTransformationMatrix();
    Core::Math::Float4x4 HierarchyTransform::GetWorldInverseTransformationMatrix();

    // parent-relative
    void HierarchyTransform::SetLocalPosition(const Core::Math::Float3 &position);
    void HierarchyTransform::AdjustLocalPosition(const Core::Math::Float3 &movement);
    Core::Math::Float3 HierarchyTransform::GetLocalPosition() const;
    // world-relative
    void HierarchyTransform::SetWorldPosition(const Core::Math::Float3 &position);
    void HierarchyTransform::AdjustWorldPosition(const Core::Math::Float3 &movement);
    Core::Math::Float3 HierarchyTransform::GetWorldPosition();

    // parent-relative
    void HierarchyTransform::SetLocalRotation(const Core::Math::FQuaternion &rotation);
    void HierarchyTransform::AdjustLocalRotation(const Core::Math::FQuaternion &rotation);
    Core::Math::FQuaternion HierarchyTransform::GetLocalRotation() const;
    // world-relative
    void HierarchyTransform::SetWorldRotation(const Core::Math::FQuaternion &rotation);
    void HierarchyTransform::AdjustWorldRotation(const Core::Math::FQuaternion &rotation);
    Core::Math::FQuaternion HierarchyTransform::GetWorldRotation();

    // parent-relative
    void HierarchyTransform::SetLocalScale(const float &scale);
    void HierarchyTransform::SetLocalScale(const Core::Math::Float3 &scale) ;
    void HierarchyTransform::AdjustLocalScale(const float &scale);
    void HierarchyTransform::AdjustLocalScale(const Core::Math::Float3 &scale);
    Core::Math::Float3 HierarchyTransform::GetLocalScale() const;
    // world-relative
    void HierarchyTransform::SetWorldScale(const float &scale);
    void HierarchyTransform::SetWorldScale(const Core::Math::Float3 &scale);
    void HierarchyTransform::AdjustWorldScale(const float &scale);
    void HierarchyTransform::AdjustWorldScale(const Core::Math::Float3 &scale);
    Core::Math::Float3 HierarchyTransform::GetWorldScale();

    void HierarchyTransform::SetParent(Core::Ptr<HierarchyTransform> parent);
    Core::Ptr<HierarchyTransform> HierarchyTransform::GetParent() const;

    void HierarchyTransform::Dirty(bool rotation = false);
    bool HierarchyTransform::IsDirty() const;
}
}