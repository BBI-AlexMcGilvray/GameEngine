#include "Pipeline/Geometric/Headers/HierarchyTransform.h"

#include "Core/Math/Headers/MatrixFunctions.h"
#include "Core/Math/Headers/QuaternionFunctions.h"

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
            SetWorldPosition(transform.GetPosition());
            SetWorldRotation(transform.GetRotation());
            SetWorldScale(transform.GetScale());
        }
    }

    // parent-relative
    const Core::Geometric::Transform& HierarchyTransform::GetLocalTransform() const { return _localTransform; }
    Core::Geometric::Transform HierarchyTransform::GetLocalTransform() { return _localTransform; }
    // world-relative
    const Core::Geometric::Transform& HierarchyTransform::GetWorldTransform()
    {
        _UpdateWorldInformation();
        return _worldTransform;
    }
    
    // parent-relative
    Core::Math::Float4x4 HierarchyTransform::GetLocalTransformationMatrix()
    {
        return _localTransform.GetTransformationMatrix();
    }

    Core::Math::Float4x4 HierarchyTransform::GetInverseLocalTransformationMatrix()
    {
        return _localTransform.GetInverseTransformationMatrix();
    }

    // world-relative
    Core::Math::Float4x4 HierarchyTransform::GetWorldTransformationMatrix()
    {
        _UpdateWorldInformation();

        return _worldTransform.GetTransformationMatrix();
    }

    Core::Math::Float4x4 HierarchyTransform::GetWorldInverseTransformationMatrix()
    {
        _UpdateWorldInformation();

        return _worldTransform.GetInverseTransformationMatrix();
    }

    // parent-relative
    void HierarchyTransform::SetLocalPosition(const Core::Math::Float3 &position)
    {
        _localTransform.SetPosition(position);
        _Dirty();
    }

    void HierarchyTransform::AdjustLocalPosition(const Core::Math::Float3 &movement)
    {
        _localTransform.AdjustPosition(movement);
        _Dirty();
    }

    Core::Math::Float3 HierarchyTransform::GetLocalPosition() const
    {
        return _localTransform.GetPosition();
    }

    // world-relative
    void HierarchyTransform::SetWorldPosition(const Core::Math::Float3 &position)
    {
        Core::Math::Float3 localPosition = _HasParent() ? _parent->GetWorldInverseTransformationMatrix() * Core::Math::Float4(position, 1.0f) : position;
        SetLocalPosition(localPosition);
        // dirtied in SetLocalPosition(...)
    }

    void HierarchyTransform::AdjustWorldPosition(const Core::Math::Float3 &movement)
    {
        AdjustLocalPosition(movement);
        // dirtied in AdjustLocalPosition(...)
    }

    Core::Math::Float3 HierarchyTransform::GetWorldPosition()
    {
        _UpdateWorldInformation();
        return _worldTransform.GetPosition();
    }

    // parent-relative
    void HierarchyTransform::SetLocalRotation(const Core::Math::FQuaternion &rotation)
    {
        _localTransform.SetRotation(rotation);
        _Dirty();
    }

    void HierarchyTransform::AdjustLocalRotation(const Core::Math::FQuaternion &rotation)
    {
        _localTransform.AdjustRotation(rotation);
        _Dirty();
    }

    // NOT SURE IF MATH IS RIGHT, TEST
    Core::Math::FQuaternion HierarchyTransform::GetLocalRotation() const
    {
        return _localTransform.GetRotation();
    }

    // world-relative
    void HierarchyTransform::SetWorldRotation(const Core::Math::FQuaternion &rotation)
    {
        // VERIFY MATH IS RIGHT
        Core::Math::FQuaternion localRotation = _HasParent() ? rotation / _parent->GetWorldRotation() : rotation;
        SetLocalRotation(localRotation);
        // dirtied in SetWorldRotation
    }

    void HierarchyTransform::AdjustWorldRotation(const Core::Math::FQuaternion &rotation)
    {
        AdjustLocalRotation(rotation);
        // dirtied in AdjustLocalRotation(...)
    }
    
    Core::Math::FQuaternion HierarchyTransform::GetWorldRotation()
    {
        _UpdateWorldInformation();
        return _worldTransform.GetRotation();
    }

    // parent-relative
    void HierarchyTransform::SetLocalScale(const float &scale)
    {
        _localTransform.SetScale(scale);
        _Dirty();
    }
    
    void HierarchyTransform::SetLocalScale(const Core::Math::Float3 &scale)
    {
        _localTransform.SetScale(scale);
        _Dirty();
    }
    
    void HierarchyTransform::AdjustLocalScale(const float &scale)
    {
        _localTransform.AdjustScale(scale);
        _Dirty();
    }
    
    void HierarchyTransform::AdjustLocalScale(const Core::Math::Float3 &scale)
    {
        _localTransform.AdjustScale(scale);
        _Dirty();
    }
    
    Core::Math::Float3 HierarchyTransform::GetLocalScale() const
    {
        return _localTransform.GetScale();
    }
    
    // world-relative
    void HierarchyTransform::SetWorldScale(const float &scale)
    {
        SetWorldScale(Core::Math::Float3(scale));
    }
    
    void HierarchyTransform::SetWorldScale(const Core::Math::Float3 &scale)
    {
        Core::Math::Float3 localScale = _HasParent() ? scale / _parent->GetWorldScale() : scale;
        SetLocalScale(localScale);
        // dirtied in SetLocalScale(...)
    }
    
    void HierarchyTransform::AdjustWorldScale(const float &scale)
    {
        AdjustWorldScale(Core::Math::Float3(scale));
    }
    
    void HierarchyTransform::AdjustWorldScale(const Core::Math::Float3 &scale)
    {
        AdjustLocalScale(scale);
        // dirtied in AdjustLocalScale(...)
    }

    Core::Math::Float3 HierarchyTransform::GetWorldScale()
    {
        _UpdateWorldInformation();
        return _worldTransform.GetScale();
    }

    void HierarchyTransform::SetParent(Core::Ptr<HierarchyTransform> parent)
    {
        if (_parent == parent)
        {
            CORE_WARNING("HierarchyTransform", "Setting parent of hierarchy transform to what it already is, why is this being done?");
            return;
        }

        // want to persist world-position when changing parent
        Core::Math::Float3 oldWorldPosition = GetWorldPosition();
        Core::Math::FQuaternion oldWorldRotation = GetWorldRotation();
        Core::Math::Float3 oldWorldScale = GetWorldScale();

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

    bool HierarchyTransform::IsDirty() const { return (_dirty || _localTransform.IsDirty()); } // don't need to care if _worldTransform is dirty, since it handles its own state
    bool HierarchyTransform::_HasParent() const { return (_parent != nullptr); }
    

    void HierarchyTransform::_UpdateWorldInformation()
    {
        if (!IsDirty()) {
            return;
        }
        
        if (!_HasParent())
        {
            _worldTransform = _localTransform;
            return;
        }

        _worldTransform = _parent->GetWorldTransformationMatrix() * GetLocalTransformationMatrix();
    }
}
}