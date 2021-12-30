#pragma once

#include <memory>

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/TimeDefs.h"

#include "Pipeline/Animation/Headers/Channel.h"

namespace Application {
namespace Animation {
  class Animation
  {
  public:
    Animation() = default;
    Animation(Animation&&) = default;
    Animation& operator=(Animation&&) = default;
    
    Animation(const Animation&) = delete;
    Animation& operator=(const Animation&) = delete;

    Animation(const std::string& name, const Core::Second& duration)
    : Animation(Core::HashValue(name), duration)
    {}

    Animation(const Core::Hash& name, const Core::Second& duration)
    : _name(name)
    , _duration(duration)
    {}

    Core::Hash GetName() const { return _name; }
    Core::Second GetDuration() const { return _duration; }

    template <typename T, typename ATTRIBUTE>
    void AddObjectChannel(const Core::Hash& target, const std::vector<Channel<T>>& channels)
    {
      std::unique_ptr<ObjectChannel<T>> newObjectChannel = std::make_unique<ObjectChannel<T>>();
      for (auto& channel : channels)
      {
        newObjectChannel->AddChannel(channel);
      }
      _channels[std::make_pair(target, Core::GetTypeId<ATTRIBUTE>())] = std::move(newObjectChannel);
    }

    template <typename T, typename ATTRIBUTE>
    T Evaluate(const Core::Hash& target, const Core::Second& time)
    {
      return _channels[{target, Core::GetTypeId<ATTRIBUTE>()}].Evaluate(time);
    }

  private:
    Core::Hash _name;
    Core::Second _duration;
    // std::pair<Target (name), Attribute>, ex: 'std::pair<LeftShoulder, Rotation>'
    std::unordered_map<std::pair<Core::Hash, Core::runtimeId_t>, std::unique_ptr<IObjectChannel>, Core::pair_hasher<Core::Hash, Core::runtimeId_t>> _channels;
  };
}// namespace Animation
}// namespace Application