#pragma once

#include "Core/Reflection/type_traits.h"
#include "Core/Serialization/type_traits.h"
#include <cstddef>
#include <cstring>
#include <vector>

namespace Core::Serialization::Format {
struct Binary
{
  // simple type writer
  template<typename Object, typename = void>
  struct object_writer_visitor
  {
    void Write(Binary &data, const Object &obj)
    {
      size_t objSize = sizeof(Object);

      std::vector<std::byte> newData(objSize);
      std::memcpy(&(newData[0]), &obj, objSize);// copy to first array element to not destroy vector object

      data._data.insert(data._data.end(), newData.begin(), newData.end());
    }
  };

  // object type writer
  template<typename Object>
  struct object_writer_visitor<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
  {
    struct field_writer
    {
      field_writer(Binary &data)
        : _data(data)
      {}

      template<typename FieldData>
      void operator()(FieldData f)
      {
        _data.Write<raw_type_t<decltype(f.get())>>(f.get());
      }

    private:
      Binary &_data;
    };

    void Write(Binary &data, const Object &obj)
    {
      reflector::visit_all(obj, field_writer(data));
    }
  };

  // array type writer, needs to handle strings in binary
  template<typename Object>
  struct object_writer_visitor<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value>::type>>
  {
    void Write(Binary &data, const Object &obj)
    {
      uint32_t numElements = obj.end() - obj.begin();
      data.Write<uint32_t>(numElements);

      for (int i = 0; i < numElements; i++) {
        data.Write<raw_type_t<decltype(std::declval<Object>()[0])>>(obj[i]);
      }
    }
  };

  // simple type writer
  template<typename Object, typename = void>
  struct object_reader_visitor
  {
    Object Read(Binary &data) const
    {
      Object instance;

      std::memcpy(&instance, &(data._data[data._currentOffset]), sizeof(Object));
      data._currentOffset += sizeof(Object);

      return instance;
    }
  };

  // object type writer
  template<typename Object>
  struct object_reader_visitor<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
  {
    struct field_reader
    {
      field_reader(Binary &data, Object &instance)
        : _data(data), _instance(instance)
      {}

      template<typename FieldData>
      void operator()(FieldData f)
      {
        f.set(_data.Read<raw_type_t<decltype(f.get())>>());
      }

    private:
      Binary &_data;
      Object &_instance;
    };

    Object Read(Binary &data) const
    {
      Object instance;

      reflector::visit_all(instance, field_reader(data, instance));

      return instance;
    }
  };

  // array type writer, needs to handle strings in binary
  template<typename Object>
  struct object_reader_visitor<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value>::type>>
  {
    Object Read(Binary &data) const
    {
      uint32_t numElements = data.Read<uint32_t>();

      Object instance;
      instance.resize(numElements);
      for (int i = 0; i < numElements; i++) {
        instance[i] = data.Read<raw_type_t<decltype(std::declval<Object>()[0])>>();
      }
      return instance;
    }
  };

  template<typename Object>
  void Write(const Object &obj)
  {
    object_writer_visitor<Object>().Write(*this, obj);
  }

  template<typename Object>
  Object Read()
  {
    if (_data.begin() + _currentOffset > _data.end()) {
      throw;// reading out of bounds
    }

    return object_reader_visitor<Object>().Read(*this);
  }

  template<typename Object>
  Object Read(int offset)
  {
    _currentOffset = offset;
    return Read<Object>();
  }

private:
  int _currentOffset = 0;
  std::vector<std::byte> _data;
};
}// namespace Core::Serialization::Format