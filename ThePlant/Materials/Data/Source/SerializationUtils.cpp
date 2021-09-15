#include "Data/Headers/SerializationUtils.h"

namespace Core::Serialization::Format
{
    void deserialize(Core::Second& time, std::shared_ptr<JSONNode> json)
    {
      JSONDecimal *data = dynamic_cast<JSONDecimal *>(json.get());
      if (data == nullptr) {
        throw;
      }
      Core::Second::rep timeCount = static_cast<float>(data->GetData());
      time = Core::Second(timeCount);
    }

    std::shared_ptr<JSONNode> serialize(const Core::Second& time)
    {
      std::shared_ptr<JSONDecimal> json = std::make_shared<JSONDecimal>();

      json->SetData(time.count());

      return json;
    }

    void deserialize(Core::Hash& hash, std::shared_ptr<JSONNode> json)
    {
      JSONNumber *data = dynamic_cast<JSONNumber *>(json.get());
      if (data == nullptr) {
        throw;
      }

      hash = static_cast<uint>(data->GetData());
    }

    std::shared_ptr<JSONNode> serialize(const Core::Hash& hash)
    {
      std::shared_ptr<JSONNumber> json = std::make_shared<JSONNumber>();

      json->SetData(static_cast<long long>(static_cast<uint>(hash)));

      return json;
    }

    void deserialize(Core::runtimeId_t& runtimeId, std::shared_ptr<JSONNode> json)
    {
      JSONNumber *data = dynamic_cast<JSONNumber *>(json.get());
      if (data == nullptr) {
        throw;
      }

      runtimeId = MakeTypeId(static_cast<uint32_t>(data->GetData()));
    }

    std::shared_ptr<JSONNode> serialize(const Core::runtimeId_t& runtimeId)
    {
      std::shared_ptr<JSONNumber> json = std::make_shared<JSONNumber>();

      json->SetData(runtimeId);

      return json;
    }

    void deserialize(Core::Math::Color& color, std::shared_ptr<JSONNode> json)
    {
      JSONObject *data = dynamic_cast<JSONObject*>(json.get());
      if (data == nullptr) {
        throw;
      }

      color.R = static_cast<float>(dynamic_cast<JSONDecimal*>(data->GetElement("r").get())->GetData());
      color.G = static_cast<float>(dynamic_cast<JSONDecimal*>(data->GetElement("g").get())->GetData());
      color.B = static_cast<float>(dynamic_cast<JSONDecimal*>(data->GetElement("b").get())->GetData());
      color.A = static_cast<float>(dynamic_cast<JSONDecimal*>(data->GetElement("a").get())->GetData());
    }

    std::shared_ptr<JSONNode> serialize(const Core::Math::Color& color)
    {
      Core::Serialization::Format::JSON json;

      SerializeTo(json, color.R, "r");
      SerializeTo(json, color.G, "g");
      SerializeTo(json, color.B, "b");
      SerializeTo(json, color.A, "a");

      return static_cast<std::shared_ptr<JSONObject>>(json);
    }
}