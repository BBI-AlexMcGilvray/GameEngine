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

  AssetData(const AssetName<T>& asset, const SharedPtr<const T>& data)
    : _data(data)
    , _asset(asset)
  {}

  AssetData& operator=(const AssetData<T>& other)
  {
    _data = other._data;
    _asset = other._asset;

    return *this;
  }

  Ptr<const T> operator->() const
  {
    return _data.get();
  }

  const T& operator*() const
  {
    return &_data;
  }

  bool operator==(const AssetName<T>& asset) const
  {
    return _asset == asset;
  }

  bool operator==(const AssetData<T>& other) const
  {
    return (_data == other._data && _asset == other._asset);
  }

  bool operator!=(const AssetName<T>& asset) const
  {
    return !(*this == asset);
  }

  bool operator!=(const AssetData<T>& other) const
  {
    return !(*this == other);
  }

  operator AssetName<T>() const
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