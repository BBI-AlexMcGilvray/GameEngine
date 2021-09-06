#pragma once

#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Core/Headers/Hash.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"

#include "Data/Headers/AssetName.h"

namespace Core::Serialization::Format
{
    void deserialize(Core::Second& time, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::Second& time);

    void deserialize(Core::Hash& hash, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::Hash& hash);

    void deserialize(Core::runtimeId_t& runtimeId, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::runtimeId_t& runtimeId);

    template <typename T>
    inline void deserialize(Data::AssetName<T>& asset, std::shared_ptr<JSONNode> json)
    {
      JSONData<uint>* data = dynamic_cast<JSONData<uint>*>(json.get());
      if (data == nullptr) {
        throw;
      }

      asset = data->GetData();
    }

    template <typename T>
    inline std::shared_ptr<JSONNode> serialize(const Data::AssetName<T>& asset)
    {
      std::shared_ptr<JSONData<uint>> json = std::make_shared<JSONData<uint>>();

      json->SetData(uint((Core::Hash(asset))));

      return json;
    }

    template <>
    inline void deserialize<void>(Data::AssetName<void>& asset, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }

      Hash name;
      runtimeId_t type;
      deserialize(name, data->GetElement("name"));
      deserialize(type, data->GetElement("type"));
      asset = Data::AssetName<void>(name, type);
    }

    template <>
    inline std::shared_ptr<JSONNode> serialize<void>(const Data::AssetName<void>& asset)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();
      
      json->AddElement("name", serialize(asset.getName()));
      json->AddElement("type", serialize(asset.getType()));

      return json;
    }

    template <typename T>
    void deserialize(Core::Math::Vector2<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      vector.X = dynamic_cast<JSONData<T>*>(data->GetElement("x").get())->GetData();
      vector.Y = dynamic_cast<JSONData<T>*>(data->GetElement("y").get())->GetData();
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Vector2<T>& vector)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

      json->AddElement("x", vector.X);
      json->AddElement("y", vector.Y);

      return json;
    }

    template <typename T>
    void deserialize(Core::Math::Vector3<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      vector.X = dynamic_cast<JSONData<T>*>(data->GetElement("x").get())->GetData();
      vector.Y = dynamic_cast<JSONData<T>*>(data->GetElement("y").get())->GetData();
      vector.Z = dynamic_cast<JSONData<T>*>(data->GetElement("z").get())->GetData();
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Vector3<T>& vector)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

      json->AddElement("x", vector.X);
      json->AddElement("y", vector.Y);
      json->AddElement("z", vector.Z);

      return json;
    }

    template <typename T>
    void deserialize(Core::Math::Vector4<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      vector.X = dynamic_cast<JSONData<T>*>(data->GetElement("x").get())->GetData();
      vector.Y = dynamic_cast<JSONData<T>*>(data->GetElement("y").get())->GetData();
      vector.Z = dynamic_cast<JSONData<T>*>(data->GetElement("z").get())->GetData();
      vector.W = dynamic_cast<JSONData<T>*>(data->GetElement("w").get())->GetData();
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Vector4<T>& vector)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

      json->AddElement("x", vector.X);
      json->AddElement("y", vector.Y);
      json->AddElement("z", vector.Z);
      json->AddElement("w", vector.W);

      return json;
    }
    // need matrix, and quaternion methods
    // also the serialization equivalents for all of the above
    // also the binary version(?)
    //      maybe only once everything is working, since json will be eaiser to debug until then
}