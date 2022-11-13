#include "Pipeline/Utils/SerializationUtils.h"

namespace Core::Serialization::Format
{
    void deserialize(Application::Rendering::Camera& camera, std::shared_ptr<JSONNode> json)
    {
        std::shared_ptr<JSONObject> data = std::static_pointer_cast<JSONObject>(json);
        if (data == nullptr) {
            throw;
        }

        Core::Serialization::Format::JSON asJson;
        asJson.FromJSON(data);

        DeserializeTo(camera.GetAspectRatio(), asJson, "aspect_ratio");
        DeserializeTo(camera.GetFOVY(), asJson, "fovy");
        DeserializeTo(camera.GetNearPlane(), asJson, "near_plane");
        DeserializeTo(camera.GetFarPlane(), asJson, "far_plane");
    }

    std::shared_ptr<JSONNode> serialize(const Application::Rendering::Camera& camera)
    {
        SCOPED_MEMORY_CATEGORY("JSON");
        Core::Serialization::Format::JSON json;

        SerializeTo(json, camera.GetAspectRatio(), "aspect_ratio");
        SerializeTo(json, camera.GetFOVY(), "fovy");
        SerializeTo(json, camera.GetNearPlane(), "near_plane");
        SerializeTo(json, camera.GetFarPlane(), "far_plane");

        return static_cast<std::shared_ptr<JSONObject>>(json);
    }
}