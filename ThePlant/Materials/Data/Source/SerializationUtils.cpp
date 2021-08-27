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
}