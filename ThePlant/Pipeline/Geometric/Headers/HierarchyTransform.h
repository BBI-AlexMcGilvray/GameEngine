#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"
#include "Core/Geometric/Headers/Transform.h"

namespace Application {
namespace Geometric {
    class HierarchyTransform
    {
    public:
        Core::Functionality::Event<> dirtied;

        HierarchyTransform(Core::Ptr<HierarchyTransform> parent = nullptr);
        HierarchyTransform(Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(II{}), Core::Math::Float3 scale = Core::Math::Float3(1.0f), Core::Ptr<HierarchyTransform> parent = nullptr, bool settingLocal = false);
        
        HierarchyTransform(const Core::Geometric::Transform& transform, Core::Ptr<HierarchyTransform> parent = nullptr, bool settingLocal = false);

        // can't do this - how do we handle persisting the reference to the parent and when children are referencing the other as the parent, we can't ensure those references are not lost
        HierarchyTransform(const HierarchyTransform& other) = delete;
        HierarchyTransform(HierarchyTransform&& other) = delete;
        HierarchyTransform& operator=(const HierarchyTransform& other) = delete;
        HierarchyTransform& operator=(HierarchyTransform&& other) = delete;
        
        // parent-relative
        Core::Math::Float4x4 GetLocalTransformationMatrix();
        Core::Math::Float4x4 GetInverseLocalTransformationMatrix();
        // world-relative
        Core::Math::Float4x4 GetWorldTransformationMatrix();
        Core::Math::Float4x4 GetWorldInverseTransformationMatrix();

        // parent-relative
        void SetLocalPosition(const Core::Math::Float3 &position);
        void AdjustLocalPosition(const Core::Math::Float3 &movement);
        Core::Math::Float3 GetLocalPosition() const;
        // world-relative
        void SetWorldPosition(const Core::Math::Float3 &position);
        void AdjustWorldPosition(const Core::Math::Float3 &movement);
        Core::Math::Float3 GetWorldPosition();

        // parent-relative
        void SetLocalRotation(const Core::Math::FQuaternion &rotation);
        void AdjustLocalRotation(const Core::Math::FQuaternion &rotation);
        Core::Math::FQuaternion GetLocalRotation() const;
        // world-relative
        void SetWorldRotation(const Core::Math::FQuaternion &rotation);
        void AdjustWorldRotation(const Core::Math::FQuaternion &rotation);
        Core::Math::FQuaternion GetWorldRotation();

        // parent-relative
        void SetLocalScale(const float &scale);
        void SetLocalScale(const Core::Math::Float3 &scale) ;
        void AdjustLocalScale(const float &scale);
        void AdjustLocalScale(const Core::Math::Float3 &scale);
        Core::Math::Float3 GetLocalScale() const;
        // world-relative
        void SetWorldScale(const float &scale);
        void SetWorldScale(const Core::Math::Float3 &scale);
        void AdjustWorldScale(const float &scale);
        void AdjustWorldScale(const Core::Math::Float3 &scale);
        Core::Math::Float3 GetWorldScale();

        void SetParent(Core::Ptr<HierarchyTransform> parent);
        Core::Ptr<HierarchyTransform> GetParent() const;

        void Dirty(bool rotation = false);
        bool IsDirty() const;

    private:
        Core::Ptr<HierarchyTransform> _parent = nullptr;
        Core::Functionality::Delegate<> _parentDirtied;
        // everything should redirect to affecting the transform, which should be a much simpler class with no concept of a parent
        Core::Geometric::Transform _transform;
        bool _dirty;
    };
}
}