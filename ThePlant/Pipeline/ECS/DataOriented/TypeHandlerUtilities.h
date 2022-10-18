#pragma once

#include "Core/Headers/PtrDefs.h"
#include "Core/IdTypes/RuntimeId.h"

namespace Application {
// this set up doesn't work because there is no way to combine the awareness of the handler with the awareness of the type

template <typename HANDLER>
struct StaticTypeHandler
{
    template <typename T>
    void Handle(T& holder)
    {
        HANDLER::Handle(holder);
    }

    template <typename T>
    void Handle(const T& holder)
    {
        HANDLER::Handle(holder);
    }
};

struct ITypeHolder
{
    virtual ~ITypeHolder() = default;

    virtual Core::runtimeId_t GetValueType() const { return Core::runtimeId_t(); };
    virtual void CopyValue(Core::Ptr<const ITypeHolder> other) {}
};

template <typename T>
struct TTypeHolder : public virtual ITypeHolder
{
    T& GetValue() const
    {
        return *_value;
    }

    virtual Core::runtimeId_t GetValueType() const override { return Core::GetTypeId<T>(); };
    virtual void CopyValue(Core::Ptr<const ITypeHolder> other) override
    {
        if (GetValueType() == other->GetValueType())
        {
            _value = &(static_cast<Core::Ptr<const TTypeHolder<T>>(other)->GetValue());
        }
    }

private:
    T* _value = nullptr;
};

template <typename HANDLER>
struct HTypeHolder : public virtual ITypeHolder
{
    virtual void Handle(HANDLER& handler) = 0;
};

template <typename T, typename HANDLER>
struct TypeHolder : public HTypeHolder<HANDLER>, public TTypeHolder<T>
{
    TypeHolder(T& value)
    : _value(&value)
    {}

    TypeHolder() = default;

    virtual void Handle(HANDLER& handler)
    {
        handler.Handle(*this);
    }
};
}// namespace Application
