#pragma once

#include <cstddef>
#include <vector>
#include "type_traits.h"

namespace Core
{
    namespace Serialization
    {
        template <typename Format, typename Object, typename ...Args>
        void InternalSerialize(Format& target, const Object& obj, Args ...args)
        {
            target.template Write<Object>(obj, args...);
        }

        template <typename Format, typename Object, typename ...Args>
        void InternalDeserialize(Object& target, Format& data, Args ...args)
        {
            target = data.template Read<Object>(args...);
        }
    }

    template <typename Format, typename Object, typename ...Args>
    void SerializeTo(Format& target, const Object& obj, Args ...args)
    {
        return Serialization::InternalSerialize<Format, Object, Args...>(target, obj, args...);
    }

    template <typename Format, typename Object, typename ...Args>
    Format Serialize(const Object& obj, Args ...args)
    {
        Format target;
        // issue with determining what is being returned bue to templates - don't know which is being called
        SerializeTo<Format, Object, Args...>(target, obj, args...);
        return target;
    }

    template <typename Object, typename Format, typename ...Args>
    void DeserializeTo(Object& target, Format& data, Args ...args)
    {
        return Serialization::InternalDeserialize<Format, Object, Args...>(target, data, args...);
    }

    template <typename Object, typename Format, typename ...Args>
    Object Deserialize(Format& data, Args ...args)
    {
        Object target;
        DeserializeTo<Object, Format, Args...>(target, data, args...);
        return target;
    }
}