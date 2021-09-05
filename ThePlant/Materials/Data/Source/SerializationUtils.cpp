#include "Data/Headers/SerializationUtils.h"

namespace Core::Serialization::Format
{
    void deserialize(Core::Second& time, std::shared_ptr<JSONNode> json)
    {
      JSONData<Core::Second::rep> *data = dynamic_cast<JSONData<Core::Second::rep> *>(json.get());
      if (data == nullptr) {
        throw;
      }
      Core::Second::rep timeCount = data->GetData();
      time = Core::Second(timeCount);
    }

    std::shared_ptr<JSONNode> serialize(const Core::Second& time)
    {
      std::shared_ptr<JSONData<Core::Second::rep>> json = std::make_shared<JSONData<Core::Second::rep>>();

      json->SetData(time.count());

      return json;
    }

    void deserialize(Core::Hash& hash, std::shared_ptr<JSONNode> json)
    {
      JSONData<uint> *data = dynamic_cast<JSONData<uint> *>(json.get());
      if (data == nullptr) {
        throw;
      }

      hash = data->GetData();
    }

    std::shared_ptr<JSONNode> serialize(const Core::Hash& hash)
    {
      std::shared_ptr<JSONData<uint>> json = std::make_shared<JSONData<uint>>();

      json->SetData(hash);

      return json;
    }

    void deserialize(Core::runtimeId_t& runtimeId, std::shared_ptr<JSONNode> json)
    {
      JSONData<uint> *data = dynamic_cast<JSONData<uint> *>(json.get());
      if (data == nullptr) {
        throw;
      }

      runtimeId = MakeTypeId(data->GetData());
    }

    std::shared_ptr<JSONNode> serialize(const Core::runtimeId_t& runtimeId)
    {
      std::shared_ptr<JSONData<uint>> json = std::make_shared<JSONData<uint>>();

      json->SetData(runtimeId);

      return json;
    }
}