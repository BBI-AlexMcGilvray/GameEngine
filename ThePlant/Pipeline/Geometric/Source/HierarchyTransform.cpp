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
    : _parentDirtied([this]()
    {
        _Dirty();
        return false;
    })
    {
        SetParent(parent); // must set parent before being able to set the local state
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
    }
    
    // parent-relative
    Core::Math::Float4x4 HierarchyTransform::GetLocalTransformationMatrix()
    {
        // possible to just do parent->GetInverseWorld * GetWorld ?
    }

    Core::Math::Float4x4 HierarchyTransform::GetInverseLocalTransformationMatrix()
    {

    }

    // world-relative
    Core::Math::Float4x4 HierarchyTransform::GetWorldTransformationMatrix()
    {
        return _transform.GetTransformationMatrix();
    }

    Core::Math::Float4x4 HierarchyTransform::GetWorldInverseTransformationMatrix()
    {
        return _transform.GetInverseTransformationMatrix();
    }

    // parent-relative
    void HierarchyTransform::SetLocalPosition(const Core::Math::Float3 &position)
    {
        Core::Math::Float3 worldPosition = _HasParent() ? _parent->GetWorldPosition() + position : position;
        SetWorldPosition(worldPosition);
        // dirtied in SetWorldPosition
    }

    void HierarchyTransform::AdjustLocalPosition(const Core::Math::Float3 &movement)
    {
        AdjustWorldPosition(movement);
        // dirtied in AdjustWorldPosition
    }

    Core::Math::Float3 HierarchyTransform::GetLocalPosition() const
    {
        return _HasParent() ? GetWorldPosition()- _parent->GetWorldPosition() : GetWorldPosition();
    }

    // world-relative
    void HierarchyTransform::SetWorldPosition(const Core::Math::Float3 &position)
    {
        _transform.SetPosition(position);
        _Dirty();
    }

    void HierarchyTransform::AdjustWorldPosition(const Core::Math::Float3 &movement)
    {
        _transform.AdjustPosition(movement);
        _Dirty();
    }

    Core::Math::Float3 HierarchyTransform::GetWorldPosition() const
    {
        return _transform.GetPosition();
    }

    // parent-relative
    void HierarchyTransform::SetLocalRotation(const Core::Math::FQuaternion &rotation)
    {
        // VERIFY MATH IS RIGHT
        Core::Math::FQuaternion worldRotation = _HasParent() ? rotation * _parent->GetWorldRotation() : rotation;
        SetWorldRotation(worldRotation);
        // dirtied in SetWorldRotation
    }

    void HierarchyTransform::AdjustLocalRotation(const Core::Math::FQuaternion &rotation)
    {
        AdjustWorldRotation(rotation);
        // dirtied in AdjustWorldRotation
    }

    // NOT SURE IF MATH IS RIGHT, TEST
    Core::Math::FQuaternion HierarchyTransform::GetLocalRotation() const
    {
        return _HasParent() ? GetWorldRotation() / _parent->GetWorldRotation() : GetWorldRotation();
    }

    // world-relative
    void HierarchyTransform::SetWorldRotation(const Core::Math::FQuaternion &rotation)
    {
        _transform.SetRotation(rotation);
        _Dirty();
    }

    void HierarchyTransform::AdjustWorldRotation(const Core::Math::FQuaternion &rotation)
    {
        _transform.AdjustRotation(rotation);
        _Dirty();
    }
    
    Core::Math::FQuaternion HierarchyTransform::GetWorldRotation() const
    {
        return _transform.GetRotation();
    }

    // parent-relative
    void HierarchyTransform::SetLocalScale(const float &scale)
    {
        SetLocalScale(Core::Math::Float3(scale));
    }
    
    void HierarchyTransform::SetLocalScale(const Core::Math::Float3 &scale)
    {
        Core::Math::Float3 worldScale = _HasParent() ? _parent->GetWorldScale() * scale : scale;
        SetWorldScale(worldScale);
        // dirtied in SetWorldScale
    }
    
    void HierarchyTransform::AdjustLocalScale(const float &scale)
    {
        AdjustLocalScale(Core::Math::Float3(scale));
    }
    
    void HierarchyTransform::AdjustLocalScale(const Core::Math::Float3 &scale)
    {
        AdjustWorldScale(scale);
        // dirtied in AdjustWorldScale
    }
    
    Core::Math::Float3 HierarchyTransform::GetLocalScale() const
    {
        return _HasParent() ? GetWorldScale() / _parent->GetWorldScale() : GetWorldScale();
    }
    
    // world-relative
    void HierarchyTransform::SetWorldScale(const float &scale)
    {
        _transform.SetScale(scale);
        _Dirty();
    }
    
    void HierarchyTransform::SetWorldScale(const Core::Math::Float3 &scale)
    {
        _transform.SetScale(scale);
        _Dirty();
    }
    
    void HierarchyTransform::AdjustWorldScale(const float &scale)
    {
        _transform.AdjustScale(scale);
        _Dirty();
    }
    
    void HierarchyTransform::AdjustWorldScale(const Core::Math::Float3 &scale)
    {
        _transform.AdjustScale(scale);
        _Dirty();
    }

    Core::Math::Float3 HierarchyTransform::GetWorldScale() const
    {
        return _transform.GetScale();
    }

    void HierarchyTransform::SetParent(Core::Ptr<HierarchyTransform> parent)
    {
        if (_parent == parent)
        {
            CORE_WARNING("HierarchyTransform", "Setting parent of hierarchy transform to what it already is, why is this being done?");
            return;
        }

        // want to persist world-position when changing parent
        Float3 oldWorldPosition = GetWorldPosition();
        FQuaternion oldWorldRotation = GetWorldRotation();
        Float3 oldWorldScale = GetWorldScale();

        if (_HasParent()) {
            _parent->dirtied -= _parentDirtied;
        }

        _parent = parent;

        if (_HasParent()) {
            _parent->dirtied += _parentDirtied;
        }

        SetWorldPosition(oldWorldPosition);
        SetWorldRotation(oldWorldRotation);
        SetWorldScale(oldWorldScale);
        
        if (_HasParent() && _parent->IsDirty())
        {
            _Dirty(); // because if there is a new parent that is dirtied, it will need to be recalculated
        }
    }

    Core::Ptr<HierarchyTransform> HierarchyTransform::GetParent() const { return _parent; }

    void HierarchyTransform::_Dirty()
    {
        _dirty = true;
        dirtied();
    }

    bool HierarchyTransform::IsDirty() const { return _dirty || _transform.IsDirty(); }
    bool HierarchyTransform::_HasParent() const { return (_parent != nullptr); }
}
}