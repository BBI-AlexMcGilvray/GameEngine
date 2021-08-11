#pragma once

#include "Core/Headers/Hash.h"
#include "Core/Headers/TemplateDefs.h"
#include "Core/IO/Headers/IODefs.h"
#include "Core/TypeId/TypeId.h"

#include "Data/Headers/AssetType.h"

using namespace Core;
using namespace Core::IO;

namespace Data {

template <typename T>
struct AssetName;

template <typename T>
std::string ToString(const AssetName<T>& asset);

template <typename T>
struct AssetNameHasher;

template<typename T>
struct AssetName
{
  friend struct AssetName<void>;
  template <typename T>
  friend std::string ToString(const AssetName<T>& asset);
  friend struct AssetNameHasher<T>;

  static const AssetName<T> VOID;

  AssetName()
  : _name(Hash::VOID)
  {}

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
  
  bool isValid() const { return (*this == VOID); }

  bool operator==(const AssetName<T>& other) const
  {
    return (_name == other._name);
  }

  template <typename OT>
  bool operator==(const AssetName<OT>& other) const
  {
    return false;
  }

  bool operator!=(const AssetName<T>& other) const
  {
    return !(*this == other);
  }

  template <typename OT>
  bool operator!=(const AssetName<OT>& other) const
  {
    return !(*this == other);
  }

  private:
    Hash _name;
};

template<>
struct AssetName<void>
{
  template<typename T>
  friend std::string ToString(const AssetName<T>& asset);
  friend struct AssetNameHasher<void>;

  static const AssetName<void> VOID;

  AssetName()
  : _name(Hash::VOID)
  , _type(runtimeId_t())
  {}

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

  bool isValid() const { return (*this == VOID); }

  template <typename T>
  operator AssetName<T>() const
  {
    if (!_sameType<T>())
    {
      return AssetName<T>::VOID;
    }

    return AssetName<T>(_name);
  }

  bool operator==(const AssetName<void>& other) const
  {
    return (_type == other._type && _name == other._name);
  }

  template <typename T>
  bool operator==(const AssetName<T>& other) const
  {
    return (_sameType<T>() && _name == other._name);
  }

  bool operator!=(const AssetName<void>& other) const
  {
    return !(*this == other);
  }

  template <typename T>
  bool operator!=(const AssetName<T>& other) const
  {
    return !(*this == other);
  }

  private:
    Hash _name;
    runtimeId_t _type;

    template <typename T>
    bool _sameType() const
    {
      return (_type == GetTypeId<T>());
    }
};

// Used to assist with AssetName<T> being a key in maps
template <typename T>
struct AssetNameHasher
{
  AssetNameHasher() = default;

  std::size_t operator()(const AssetName<T>& asset) const
  {
    return asset._name;
  }
};

template <typename T>
std::string ToString(const AssetName<T>& asset)
{
  return ToString(asset._name);
}
}// namespace Data