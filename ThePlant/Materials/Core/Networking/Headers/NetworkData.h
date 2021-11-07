#pragma once

#include <vector>

namespace Core {
namespace Networking {
  class NetworkData
  {
    // byte array that is comprised of all data
    std::vector<byte> _data;

  public:
    template<typename... Ts>
    void AddData(std::vector<byte> newData)
    {
      uint newDataSize = newData.size();
      // key representing the size of this block of data
      Push(_data, newDataSize);
      // the actual data
      Push(_data, newData);
    }

    void ClearData()
    {
      _data.clear();
    }

    std::vector<byte> GetData() const
    {
      std::vector<byte> returnedData(_data.size());
      Push(returnedData, _data);

      return returnedData;
    }
  };
}// namespace Networking
}// namespace Core
