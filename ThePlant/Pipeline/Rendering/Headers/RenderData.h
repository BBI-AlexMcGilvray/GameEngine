#pragma once

#include "Core/IdTypes/InstanceId.h"
#include "Core/IdTypes/RuntimeId.h"
#include "Core/Logging/LogFunctions.h"

#include "Pipeline/Rendering/Headers/RenderDataCreator.h"

namespace Application {
namespace Rendering {
/*
* All render types (mesh, material, shader, texture, ...) should have an associated manager
* The render types should be split into gameplay data (implicit in the render type) and render data (explicit type inheriting from RenderData)
* Loading an asset should create and return the gameplay data but leave the render data uninitialized
    * To be initialized by the render thread when we first try to render the object
    * Or initialized on the first render frame after the request (to know when it occurs)
    * Should probably be an optional swap for the two
* When the object is rendered, we should check for if the RenderData is created
    * If not, we run the manager's RenderData construction method (via RenderDataCreator)
        * If we initialize immediately, this would iterate over a list of RenderDatas to create
    * Once it is created, we then render it properly

OPEN QUESTIONS:
* Does the RenderData only exist in one place to minimize memory?
    * This means we only need to create a mesh once if it is re-used
        * This would also help performance as we need to run the creation code way less often
    * This means the RenderData base class should also have a reference counter?
        * Would just a shared ptr work? This would need to be automatically updated based on each RenderDataHandle instance that points to it
    * Also means we should have a RenderDataHandle that allows for getting the associated render data while storing it in only one place?
* Could be worse for perf (since each object being rendered would need to get the relevant data), but should be fine if we use an appropriate container
    * The alternative is to have the gameplay data keep a reference to the render data
        * But then we would never know how many references/instances there are (could be random floating copies and the like)
    * To get around this, we could have the render contexts provide a direct reference to their render data (probably would need to be an actual reference?)
        * But this isn't possible if the data hasn't been initialized yet
            * If it is a direct reference, we would know what to initialize
            * Or we have the uses register their handles as 'needs to be initialized' (though what's the difference between this and the above?)

SUMMARY:
* We should have a RenderDataHandle
    * that can _only_ be gotten from the RenderData - incrementing the reference count - and _must_ be returned to the RenderData - decrementing the reference count
    * this should be doable as the various managers should be easily accessible
* RenderContexts now provide a RenderDataHandle
* Renderer now gets the appropriate RenderData from the manager
* We have _one_ instance of the RenderData
    * at least for each loaded asset, they can be created as unique instances at runtime
    * we should also support a creation argument for if it should be a unique instance or use an existing one (can be used in editor and such to make and save edits from a starting point)
* The implicit gameplay data would always be unique based on instance
*/
    struct RenderData;

    struct RenderDataHandle
    {
        RenderDataHandle() = default;
        ~RenderDataHandle() = default;
        RenderDataHandle(RenderDataHandle&&) = default;
        RenderDataHandle& operator=(RenderDataHandle&&) = default;

        // to keep the reference count correct, only one instances of a 'gotten' handle can exist (i.e. move only)
        // ideally the above would be the case, maybe we can ignore it? kinda need to cause msvc seems to not work properly/as expected
        RenderDataHandle(const RenderDataHandle&) = default;
        RenderDataHandle& operator=(const RenderDataHandle&) = default;

        Core::instanceId<RenderData> GetRenderDataID() const { return _renderDataID; }
        Core::runtimeId_t GetRenderTypeID() const { return _typeId; }
        bool IsValid() const { return _renderDataID.IsValid(); }

        bool operator==(const RenderDataHandle& other) const
        {
            return other._renderDataID == _renderDataID && other._typeId == _typeId;
        }
        bool operator!=(const RenderDataHandle& other) const
        {
            return !(*this == other);
        }

    private:
        friend struct RenderData;
        Core::instanceId<RenderData> _renderDataID;
        Core::runtimeId_t _typeId;

        RenderDataHandle(Core::instanceId<RenderData> renderDataID, Core::runtimeId_t typeId)
        : _renderDataID(renderDataID)
        , _typeId(typeId)
        {}
    };

    struct RenderData
    {
        RenderData(Core::runtimeId_t typeId)
        : _id(Core::GetInstanceId<RenderData>())
        , _typeId(typeId)
        {}

        ~RenderData() = default;
        // {
        //     DEBUG_ASSERT(_references == 0, "Deleting referenced RenderData!");
        // }

        RenderData(RenderData&&) = default;
        RenderData& operator=(RenderData&&) = default;

        // handles should only refer to a single object, not multiple -> move only
        // ideally the above would be the case, maybe we can ignore it? kinda need to cause msvc seems to not work properly/as expected
        RenderData(const RenderData&) = default;
        RenderData& operator=(const RenderData&) = default;

        Core::instanceId<RenderData> GetID() const { return _id; }
        bool IsValid() const { return _initialized; }
        bool IsReferenced() const { return _references > 0; }

        RenderDataHandle GetHandle()
        {
            ++_references;
            return RenderDataHandle(GetID(), _typeId);
        }

        bool IsHeldBy(const RenderDataHandle& handle) const
        {
            return handle.GetRenderDataID() == GetID();
        }

        void ReturnHandle(RenderDataHandle&& handle)
        {
            VERIFY(IsHeldBy(handle), "Can only return an applicable handle");
            --_references;
        }

    private:
    // maybe we don't need a class to friend, and we just friend the templated functions? although a class may make it syntactically nicer
        friend struct RenderDataCreator;
        bool _initialized; // this should only ever be modified by render thread, so shouldn't need to be atomic (need it to not be cause msvc compilation not really supporting move only types in vectors)
        // we _should_ have some way to enforce what thread funcions are called from

        Core::instanceId<RenderData> _id;
        Core::runtimeId_t _typeId;
        uint32_t _references = 0; // without move-only, this doesn't work -> we need some form of shared_ptrs esque reference counting to handle copying of handles

        void _Initialize()
        {
            _initialized = true;
        }

        void _Uninitialize()
        {
            _initialized = false;
        }
    };

    // all render types must inherit from this so we can also store the type ids (without having to do it all the time)
    template <typename RENDER_DATA>
    struct TRenderData : public RenderData
    {
        TRenderData()
        : RenderData(Core::GetTypeId<RENDER_DATA>())
        {}
        ~TRenderData() = default;
        TRenderData(TRenderData&&) = default;
        TRenderData& operator=(TRenderData&&) = default;

        // handles should only refer to a single object, not multiple -> move only
        TRenderData(const TRenderData&) = default;
        TRenderData& operator=(const TRenderData&) = default;
    };
}// namespace Rendering
}// namespace Application