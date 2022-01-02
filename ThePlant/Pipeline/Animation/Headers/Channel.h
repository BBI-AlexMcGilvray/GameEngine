#pragma once

#include <stdexcept>
#include <unordered_map>

#include "Materials/Core/Headers/PtrDefs.h"
#include "Materials/Core/IdTypes/RuntimeId.h"

#include "Pipeline/Animation/Headers/AnimationCurve.h"

namespace Application {
namespace Animation {
    template <typename TYPE>
    class Channel
    {
    public:
        Channel(float TYPE::*member, const AnimationCurve& curve)
        : _member(member)
        , _curve(curve)
        {}

        void SetCurve(const AnimationCurve& curve)
        {
            _curve = curve;
        }

        const float TYPE::* Member() const { return _member; }

        bool TargetsMember(const float TYPE::*member) const { return member == _member; }

        void Evaluate(TYPE& target, const Core::Second& time) const
        {
            target.*_member = _curve.Evaluate(time);
        }

    private:
        float TYPE::*_member;
        AnimationCurve _curve;
    };

    template <typename TYPE>
    class ObjectChannel;

    class IObjectChannel
    {
    public:
        IObjectChannel() = default;

        virtual Core::runtimeId_t ObjectType() const = 0;

        template <typename T>
        T Evaluate(const Core::Second& time) const
        {
            return AsObjectChannel<T>().Evaluate(time);
        }

        template <typename T>
        ObjectChannel<T>& AsObjectChannel()
        {
            if (!_IsCorrectType<T>())
            {
                throw std::invalid_argument("type does not match that held by the component list");
            }

            return *(static_cast<Core::Ptr<ObjectChannel<T>>>(this));
        }
        
        template <typename T>
        const ObjectChannel<T>& AsObjectChannel() const
        {
            if (!_IsCorrectType<T>())
            {
                throw std::invalid_argument("type does not match that held by the component list");
            }

            return *(static_cast<Core::Ptr<const ObjectChannel<T>>>(this));
        }

    protected:
        template <typename T>
        bool _IsCorrectType() const { return _IsCorrectType(Core::GetTypeId<T>()); } // could be compiled out when not in debug

        bool _IsCorrectType(const Core::runtimeId_t& type) const { return (type == ObjectType()); }
    };

    template <typename TYPE>
    class ObjectChannel : public IObjectChannel
    {
    public:
        ObjectChannel()
        {}

        Core::runtimeId_t ObjectType() const override { return Core::GetTypeId<TYPE>(); }

        void AddChannel(float TYPE::*member, const AnimationCurve& curve)
        {
            AddChannel(Channel<TYPE>(member, curve));
        }

        void AddChannel(const Channel<TYPE>& channel)
        {
            auto existingChannelIter = _GetMemberChannel(channel.Member());
            if (existingChannelIter != _channels.end())
            {
                throw std::invalid_argument("member is already being targetted by existing channel, set channel curve instead");
            }

            _channels.emplace_back(channel);
        }

        void SetChannelCurve(float TYPE::*member, const AnimationCurve& curve)
        {
            auto existingChannelIter = _GetMemberChannel(member);
            if (existingChannelIter != _channels.end())
            {
                AddChannel(member, curve);
                return;
            }

            _channels[existingChannelIter].SetCurve(curve);
        }

        void RemoveChannel(float TYPE::*member)
        {
            if (auto memberIter = _channels.find(member); memberIter != _channels.end())
            {
                _channels.erase(memberIter);
            }
        }

        TYPE Evaluate(const Core::Second& time) const
        {
            TYPE result;

            for (const auto& channel : _channels)
            {
                channel.Evaluate(result, time);
            }

            return result;
        }

    private:
        std::vector<Channel<TYPE>> _channels;

        auto _GetMemberChannel(const float TYPE::*member) const
        {
           return std::find_if(_channels.begin(), _channels.end(), [member](const Channel<TYPE>& channel)
            {
                return channel.TargetsMember(member);
            }); 
        }
    };
}// namespace Animation
}// namespace Application