#pragma once

#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

namespace Core::Serialization::Format
{
    void deserialize(Core::Second& time, std::shared_ptr<JSONNode> json);

    template <typename T>
    void deserialize(Core::Math::Vector2<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject *data = dynamic_cast<JSONObject>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      vector.X = dynamic_cast<JSONData<T>*>(data->GetElement("x").get())->GetData();
      vector.Y = dynamic_cast<JSONData<T>*>(data->GetElement("y").get())->GetData();
    }

    template <typename T>
    void deserialize(Core::Math::Vector3<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject *data = dynamic_cast<JSONObject>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      vector.X = dynamic_cast<JSONData<T>*>(data->GetElement("x").get())->GetData();
      vector.Y = dynamic_cast<JSONData<T>*>(data->GetElement("y").get())->GetData();
      vector.Z = dynamic_cast<JSONData<T>*>(data->GetElement("z").get())->GetData();
    }

    template <typename T>
    void deserialize(Core::Math::Vector4<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject *data = dynamic_cast<JSONObject>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      vector.X = dynamic_cast<JSONData<T>*>(data->GetElement("x").get())->GetData();
      vector.Y = dynamic_cast<JSONData<T>*>(data->GetElement("y").get())->GetData();
      vector.Z = dynamic_cast<JSONData<T>*>(data->GetElement("z").get())->GetData();
      vector.W = dynamic_cast<JSONData<T>*>(data->GetElement("w").get())->GetData();
    }
    // need matrix, and quaternion methods
    // also the serialization equivalents for all of the above
    // also the binary version(?)
    //      maybe only once everything is working, since json will be eaiser to debug until then
}