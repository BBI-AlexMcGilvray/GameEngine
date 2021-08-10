#pragma once

#include "Core/Headers/Hash.h"
#include "Data/Headers/AssetName.h"

using namespace Core;

namespace Data {
template<typename T>
struct AssetData
{
  AssetData(const AssetData<T>& other)
    : _data(assetData.data)
    , _asset(assetData.asset)
  {}

  AssetData(const AssetName<T>& other, const SharedPtr<const T>& data)
    : _data(data)
    , _asset(assetName)
  {}

  AssetData& operator=(const AssetData<T>& other)
  {
    _data = other._data;
    _asset = other._asset;

    return *this;
  }

  Ptr<const T> operator->()
  {
    return _data.get();
  }

  const T& operator*()
  {
    return &_data;
  }

  operator AssetName<T>()
  {
    return _asset;
  }

private:
// do we need a specific 'DataPtr<T>' type?
// wouldn't that just be this type?
//  - means we would just want a 'ControlBlock' type for the ptr?
  SharedPtr<const T> _data;
  AssetName<T> _asset;
};
}// namespace Data