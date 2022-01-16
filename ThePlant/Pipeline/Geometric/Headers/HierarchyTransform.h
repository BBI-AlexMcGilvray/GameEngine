#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/Functionality/Headers/Event.h"
#include "Core/Geometric/Transform.h"

namespace Application {
namespace Geometric {
    class HierarchyTransform
    {
    public:
        Core::Functionality::Event<> dirtied;

        HierarchyTransform(Core::Ptr<HierarchyTransform> parent = nullptr);
        HierarchyTransform(Core::Math::Float3 position, Core::Math::FQuaternion rotation = Core::Math::FQuaternion(Core::Math::II{}), Core::Math::Float3 scale = Core::Math::Float3(1.0f), Core::Ptr<HierarchyTransform> parent = nullptr, bool settingLocal = false);
        
        HierarchyTransform(const Core::Geometric::Transform& transform, Core::Ptr<HierarchyTransform> parent = nullptr, bool settingLocal = false);

        // can't do this - how do we handle persisting the reference to the parent and when children are referencing the other as the parent, we can't ensure those references are not lost
        HierarchyTransform(const HierarchyTransform& other) = delete;
        HierarchyTransform(HierarchyTransform&& other) = delete;
        HierarchyTransform& operator=(const HierarchyTransform& other) = delete;
        HierarchyTransform& operator=(HierarchyTransform&& other) = delete;

        // parent-relative
        const Core::Geometric::Transform& GetLocalTransform() const;
        Core::Geometric::Transform GetLocalTransform();
        // world-relative
        const Core::Geometric::Transform& GetWorldTransform();
        
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

        bool IsDirty() const;

    private:
        Core::Ptr<HierarchyTransform> _parent = nullptr;
        Core::Functionality::Delegate<> _parentDirtied;

        // doing it this way should make it much easier for getting data
        // but we need to make sure the data is synced
        // alternative is to only store one and constantly translate (which would be slower)
        //      - if that is done probably easier for that to be the local, but when we did this before we ended up caching anyways
        Core::Geometric::Transform _localTransform; // NEED BOTH. If we just have world, then recalculating with parents becomes much more difficult. If we just have local then the recalculation for getting world data will be too expensive so we need the world to act as a cache
        Core::Geometric::Transform _worldTransform;

        // may not need?
        bool _dirty;

        void _Dirty();
        bool _HasParent() const;

        void _UpdateWorldInformation();
    };
}
}