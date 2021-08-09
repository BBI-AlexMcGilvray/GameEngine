#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Headers/TemplateDefs.h"
#include "Core/IO/Headers/IODefs.h"
#include "Core/TypeId/TypeId.h"

#include "Data/Headers/AssetType.h"

using namespace Core;
using namespace Core::IO;

namespace Data {
template<typename T>
struct AssetName
{
  static const AssetName<T> VOID;
  friend struct AssetName<void>;

  AssetName() = delete;

  AssetName(const AssetName<T>& other)
    : _name(other._name)
  {}

  AssetName(const Hash &hash)
    : _name(hash)
  {
  }

  AssetName<T> &operator=(const AssetName<T>& other)
  {
    _name = other._name;

    return (*this);
  }

  AssetName<T> &operator=(const Hash &hash)
  {
    _name = hash;

    return (*this);
  }
  
  bool isValid() { return (*this == VOID); }

  bool operator==(const AssetName<T>& other)
  {
    return (_name == other._name);
  }

  template <typename OT>
  bool operator==(const AssetName<OT>& other)
  {
    return false;
  }

  bool operator!=(const AssetName<T>& other)
  {
    return !(*this == other);
  }

  template <typename OT>
  bool operator!=(const AssetName<OT>& other)
  {
    return !(*this == other);
  }

  private:
    Hash _name;
};
template <typename T>
const AssetName<T> AssetName<T>::VOID = Hash::VOID;

template<>
struct AssetName<void>
{
  static const AssetName<void> VOID;

  AssetName() = delete;

  AssetName(const AssetName<void>& other)
  : _name(other._name)
  , _type(other._type)
  {}

  template <typename T>
  AssetName(const AssetName<T>& other)
    : _name(other._name)
    , _type(GetTypeId<T>())
  {}

  AssetName<void>& operator=(const AssetName<void>& other)
  {
    _name = other._name;
    _type = other._type;

    return *this;
  }

  template <typename T>
  AssetName<void>& operator=(const AssetName<T>& other)
  {
    _name = other._name;
    _type = GetTypeId<T>();

    return (*this);
  }

  bool isValid() { return (*this == VOID); }

  template <typename T>
  operator AssetName<T>()
  {
    if (!_sameType<T>())
    {
      return AssetName<T>::VOID;
    }

    return AssetName<T>(_name);
  }

  bool operator==(const AssetName<void>& other)
  {
    return (_type == other._type && _name == other._name);
  }

  template <typename T>
  bool operator==(const AssetName<T>& other)
  {
    return (_sameType<T>() && _name == other._name);
  }

  bool operator!=(const AssetName<void>& other)
  {
    return !(*this == other);
  }

  template <typename T>
  bool operator!=(const AssetName<T>& other)
  {
    return !(*this == other);
  }

  private:
    Hash _name;
    runtimeId_t _type;

    template <typename T>
    bool _sameType()
    {
      return (_type == GetTypeId<T>());
    }
};
const AssetName<void> AssetName<void>::VOID = AssetName<int>::VOID; // any type would do, just need a void value
}// namespace Data