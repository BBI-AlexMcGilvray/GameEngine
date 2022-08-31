#pragma once

#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Data/Headers/SerializationUtils.h"

#include "Pipeline/ECSSystems/TransformComponents.h"

namespace Application {
// serializer/deserializer for component, call to this need to be registered with the EntityFactory elsewhere
// but where? in state? it needs to be extensible by products for their custom components

void deserialize(PositionComponent& positionComponent, std::shared_ptr<Core::Serialization::Format::JSONNode> json)
{
    Core::Serialization::Format::JSONObject* data = dynamic_cast<Core::Serialization::Format::JSONObject*>(json.get());
    if (data == nullptr)
    {
        throw;
    }

    Core::Serialization::Format::deserialize(positionComponent.position, data->GetElement("position"));
}

std::shared_ptr<Core::Serialization::Format::JSONNode> serialize(const PositionComponent& positionComponent)
{
    std::shared_ptr<Core::Serialization::Format::JSONObject> serialized = std::make_shared<Core::Serialization::Format::JSONObject>();

    serialized->AddElement("position", Core::Serialization::Format::serialize(positionComponent.position));

    return serialized;
}

void deserialize(WorldTransformComponent& worldTransformComponent, std::shared_ptr<Core::Serialization::Format::JSONNode> json)
{
    return; // no need to do anything, transforms get made later - this data is irrelevant
}

std::shared_ptr<Core::Serialization::Format::JSONNode> serialize(const WorldTransformComponent& worldTransformComponent)
{
    std::shared_ptr<Core::Serialization::Format::JSONObject> serialized = std::make_shared<Core::Serialization::Format::JSONObject>();

    // nothing to deserialize (per above) means nothing to serialize

    return serialized;
}
}// namespace Application