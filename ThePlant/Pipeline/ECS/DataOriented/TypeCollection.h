#pragma once

#include <algorithm>
#include <stdexcept>
#include <vector>

#include "../TypeId/TypeId.h"

struct TypeCollection;

template <typename ...Ts>
TypeCollection CollectTypes();
template <typename ...Ts>
TypeCollection AddToCollection(const TypeCollection& collection);
template <typename ...Ts>
TypeCollection RemoveFromCollection(const TypeCollection& collection);

struct TypeCollection
{
    template <typename ...Ts>
    friend TypeCollection CollectTypes();
    template <typename ...Ts>
    friend TypeCollection AddToCollection(const TypeCollection& collection);
    template <typename ...Ts>
    friend TypeCollection RemoveFromCollection(const TypeCollection& collection);

    TypeCollection() = delete;

    TypeCollection(const TypeCollection& other)
    : _types(other._types)
    {}

    TypeCollection(TypeCollection&& other)
    : _types(std::move(other._types))
    {}

    TypeCollection& operator=(const TypeCollection& other)
    {
        _types = other._types;

        return *this;
    }

    TypeCollection& operator=(TypeCollection&& other)
    {
        _types = other._types;

        return *this;
    }

    const std::vector<runtimeId_t>& Types() const
    {
        return _types;
    }

    bool operator==(const TypeCollection& other) const
    {
        if (_types.size() != other._types.size())
        {
            return false;
        }

        for (auto& type : _types)
        {
            if (std::find(other._types.begin(), other._types.end(), type) == other._types.end())
            {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const TypeCollection& other) const
    {
        return !(*this == other);
    }

private:
    std::vector<runtimeId_t> _types;

    enum class Constructor : int { TAG };
    TypeCollection(Constructor tag, std::vector<runtimeId_t>&& types)
    {
        _types = std::move(types);

        // should be debug only
        for (auto iter = _types.begin(); iter != _types.end(); ++iter)
        {
            if (std::find(iter + 1, _types.end(), *iter) != _types.end())
            {
                throw std::invalid_argument("all component types in a collection must be unique!");
            }
        }
    }
};

template <typename ...Ts>
TypeCollection CollectTypes()
{
    return TypeCollection(TypeCollection::Constructor::TAG, std::vector<runtimeId_t>{ GetTypeId<Ts>()... });
}

template <typename ...Ts>
TypeCollection AddToCollection(const TypeCollection& collection)
{
    std::vector<runtimeId_t> existing = collection.Types();
    std::vector<runtimeId_t> toAdd = std::vector<runtimeId_t>{ GetTypeId<Ts>()... };
    
    std::vector<runtimeId_t> all;
    all.insert(all.end(), existing.begin(), existing.end());
    all.insert(all.end(), toAdd.begin(), toAdd.end());

    return TypeCollection(TypeCollection::Constructor::TAG, std::move(all));
}

template <typename ...Ts>
TypeCollection RemoveFromCollection(const TypeCollection& collection)
{
    std::vector<runtimeId_t> existing = collection.Types();
    std::vector<runtimeId_t> toRemove = std::vector<runtimeId_t>{ GetTypeId<Ts>()... };
    
    existing.erase(std::remove_if(existing.begin(), existing.end(), [toRemove](const auto& x)
    {
        return std::find(toRemove.begin(), toRemove.end(), x) != toRemove.end();
    }));

    return TypeCollection(TypeCollection::Constructor::TAG, std::move(existing));
}