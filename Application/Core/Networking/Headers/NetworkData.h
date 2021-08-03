#pragma once

#include "Core/Headers/ListDefs.h"

namespace Core {
namespace Networking {
  class NetworkData
  {
    // byte array that is comprised of all data
    List<byte> _data;

  public:
    template<typename... Ts>
    void AddData(List<byte> newData)
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

    List<byte> GetData() const
    {
      List<byte> returnedData(_data.size());
      Push(returnedData, _data);

      return returnedData;
    }
  };
}// namespace Networking
}// namespace Core
