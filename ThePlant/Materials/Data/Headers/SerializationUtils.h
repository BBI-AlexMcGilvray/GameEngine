#pragma once

#include "Core/Serialization/Formats/JSON/JSON.h"

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/Hash.h"
#include "Core/Headers/TimeDefs.h"
#include "Core/Math/Headers/Color.h"
#include "Core/Math/Headers/Vector2.h"
#include "Core/Math/Headers/Vector3.h"
#include "Core/Math/Headers/Vector4.h"
#include "Core/Math/Headers/Quaternion.h"
#include "Core/Serialization/Serialization.h"
#include "Core/IO/Headers/IODefs.h"

#include "Data/Headers/AssetName.h"
#include "Data/Rendering/Headers/SkeletonAnimationData.h"

namespace Core::Serialization::Format
{
    void deserialize(Core::Second& time, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::Second& time);

    void deserialize(Core::Hash& hash, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::Hash& hash);

    void deserialize(Core::Math::Color& color, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::Math::Color& color);

    void deserialize(Core::IO::FilePath& filePath, std::shared_ptr<JSONNode> json);
    std::shared_ptr<JSONNode> serialize(const Core::IO::FilePath& filePath);

    template <typename T>
    auto deserialize(T& outputEnum, std::shared_ptr<JSONNode> json)
    -> typename std::enable_if<std::is_enum<T>::value, void>::type
    {
      JSONString* data = dynamic_cast<JSONString*>(json.get());
      if (data == nullptr) {
        throw;
      }

      // namespace may be an issue here. if it is, we may need the macro that creates this function to use the uppermost namespace
      // prefix with :: (<- may be an issue if enum exists within a class)
      from_string(data->GetData(), outputEnum);
    }

    template <typename T>
    auto serialize(const T& inputEnum)
    -> typename std::enable_if<std::is_enum<T>::value, std::shared_ptr<JSONNode>>::type
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONString> json = std::make_shared<JSONString>();

      // namespace may be an issue here. if it is, we may need the macro that creates this function to use the uppermost namespace
      // prefix with :: (<- may be an issue if enum exists within a class)
      json->SetData(to_string(inputEnum));

      return json;
    }

    template <typename T>
    void deserialize(Core::Math::Rad<T>& radians, std::shared_ptr<JSONNode> json)
    {
      JSONNumber* data = dynamic_cast<JSONNumber*>(json.get());
      if (data == nullptr) {
        throw;
      }

      radians.Radians = static_cast<T>(data->GetData());
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Rad<T>& radians)
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONNumber> json = std::make_shared<JSONNumber>();

      json->SetData(radians.Radians);

      return json;
    }
    
    template <typename T>
    void deserialize(Core::Math::Deg<T>& degrees, std::shared_ptr<JSONNode> json)
    {
      JSONNumber* data = dynamic_cast<JSONNumber*>(json.get());
      if (data == nullptr) {
        throw;
      }

      degrees.Degrees = static_cast<T>(data->GetData());
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Deg<T>& degrees)
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONNumber> json = std::make_shared<JSONNumber>();

      json->SetData(degrees.Degrees);

      return json;
    }

    template <typename T>
    inline void deserialize(Data::AssetName<T>& asset, std::shared_ptr<JSONNode> json)
    {
      JSONNumber* data = dynamic_cast<JSONNumber*>(json.get());
      if (data == nullptr) {
        throw;
      }

      asset = AsHash(static_cast<uint>(data->GetData()));
    }

    template <typename T>
    inline std::shared_ptr<JSONNode> serialize(const Data::AssetName<T>& asset)
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONNumber> json = std::make_shared<JSONNumber>();

      json->SetData(static_cast<long long>(static_cast<uint>(Core::Hash(asset))));

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
      Hash type;
      deserialize(name, data->GetElement("name"));
      deserialize(type, data->GetElement("type"));
      asset = Data::AssetName<void>(name, type);
    }

    template <>
    inline std::shared_ptr<JSONNode> serialize<void>(const Data::AssetName<void>& asset)
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();
      
      json->AddElement("name", serialize(asset.getName()));
      json->AddElement("type", serialize(asset.getType()));

      return json;
    }

    // We should probably differentiate between JSONDecimal and JSONNumber based on the type of 'T'
    // that would make it less likely to lose data due to conversions, but we can leave as-is for now
    template <typename T>
    void deserialize(Core::Math::Vector2<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      using object_json_type = typename Core::Serialization::Format::json_type<T>::type;

      vector.X = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("x").get())->GetData());
      vector.Y = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("y").get())->GetData());
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Vector2<T>& vector)
    {
      Core::Serialization::Format::JSON json;

      SerializeTo(json, vector.X, "x");
      SerializeTo(json, vector.Y, "y");

      return static_cast<std::shared_ptr<JSONObject>>(json);
    }

    template <typename T>
    void deserialize(Core::Math::Vector3<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      using object_json_type = typename Core::Serialization::Format::json_type<T>::type;

      vector.X = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("x").get())->GetData());
      vector.Y = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("y").get())->GetData());
      vector.Z = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("z").get())->GetData());
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Vector3<T>& vector)
    {
      Core::Serialization::Format::JSON json;

      SerializeTo(json, vector.X, "x");
      SerializeTo(json, vector.Y, "y");
      SerializeTo(json, vector.Z, "z");

      return static_cast<std::shared_ptr<JSONObject>>(json);
    }

    template <typename T>
    void deserialize(Core::Math::Vector4<T>& vector, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }
      
      using object_json_type = typename Core::Serialization::Format::json_type<T>::type;

      vector.X = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("x").get())->GetData());
      vector.Y = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("y").get())->GetData());
      vector.Z = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("z").get())->GetData());
      vector.W = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("w").get())->GetData());
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Vector4<T>& vector)
    {
      Core::Serialization::Format::JSON json;

      SerializeTo(json, vector.X, "x");
      SerializeTo(json, vector.Y, "y");
      SerializeTo(json, vector.Z, "z");
      SerializeTo(json, vector.W, "w");

      return static_cast<std::shared_ptr<JSONObject>>(json);
    }

    template <typename T>
    void deserialize(Core::Math::Quaternion<T>& quaternion, std::shared_ptr<JSONNode> json)
    {
      JSONObject* data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }

      using object_json_type = typename Core::Serialization::Format::json_type<T>::type;
      
      quaternion.X = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("x").get())->GetData());
      quaternion.Y = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("y").get())->GetData());
      quaternion.Z = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("z").get())->GetData());
      quaternion.W = static_cast<T>(dynamic_cast<object_json_type*>(data->GetElement("w").get())->GetData());
    }

    template <typename T>
    std::shared_ptr<JSONNode> serialize(const Core::Math::Quaternion<T>& quaternion)
    {
      Core::Serialization::Format::JSON json;

      SerializeTo(json, quaternion.X, "x");
      SerializeTo(json, quaternion.Y, "y");
      SerializeTo(json, quaternion.Z, "z");
      SerializeTo(json, quaternion.W, "w");

      return static_cast<std::shared_ptr<JSONObject>>(json);
    }

    // need matrix, and quaternion methods
    // also the serialization equivalents for all of the above
    // also the binary version(?)
    //      maybe only once everything is working, since json will be eaiser to debug until then
}