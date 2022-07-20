#pragma once

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <type_traits>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Reflection/type_traits.h"

namespace Core::Serialization::Format {
    // references:
// - json: https://wiki.unity3d.com/index.php/SimpleJSON
// - function template specialization: https://www.fluentcpp.com/2017/08/15/function-templates-partial-specialization-cpp/
// - could potentially use: https://www.codingame.com/playgrounds/2205/7-features-of-c17-that-will-simplify-your-code/constexpr-if
//      - for specializing function body without relying on the work arounds mentioned above
// - for determining iterable containers: http://www.shital.com/p/writing-generic-container-function-in-c11/
//      - essentially it looks like it would be required to know more of the underlying structure of the standard to know what type traits can be used and when

enum Style {
  Compact,
  Readable
};

/*
* NOTE: Split this up into files!
*         - one file for base JSONNode
*         - one file for each json type (maybe)
*         - folder for writers
*            - one file for each writer
*         - folder for readers
*            - one file for each reader
*/

namespace {
  std::string NodeSpace(Style style)
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    std::string result;

    switch (style) {
    case Style::Compact: {
      break;
    }
    case Style::Readable: {
      result += "\n";
    }
    }

    return result;
  }

  std::string ElementSpace(Style style, int depth)
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    std::string result;

    switch (style) {
    case Style::Compact: {
      break;
    }
    case Style::Readable: {
      for (int i = 0; i < depth; i++) {
        result += "\t";
      }
    }
    }

    return result;
  }

  std::string WrapString(const std::string &str)
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    return "\"" + str + "\"";
  }
}// namespace

struct JSONNode
{
  virtual ~JSONNode() = default;

  virtual std::string ToString(Style style, int depth) const = 0;
};

// when there is no data
template<typename T, typename = void>
struct JSONData : public JSONNode
{
  JSONData()
  {
    // creating invalid JSONData type
    throw;
  }

  T GetData() const
  {
    // getting from invalid JSONData type
    throw;
  }

  void SetData(const T &data)
  {
    // setting on invalid JSONData type
    throw;
  }

  std::string ToString(Style style, int depth) const override
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    return "null";
  }
};

//**
// Can't be used because we can't have a unique_ptr<void>
//**
// when the data exists, but is not known
/*template <>
    struct JSONData<std::unique_ptr<void>, void> : public JSONNode
    {
        template <typename T>
        JSONData<T> SetType()
        {
            JSONData<T> knownType;
            knownType.SetData(static_cast<T>(*_data));
            return knownType;
        }

        template <typename T>
        T GetData() const
        {
            return static_cast<T>(*_data);
        }

        void* GetData() const
        {
            return _data.get();
        }

        template <typename T>
        void SetData(const T& data)
        {
            _data = std::make_unique<T>(data);
        }

        void SetData(std::unique_ptr<void> data)
        {
            _data = move(data);
        }

        std::string ToString() const
        {
            // type is not known, can't make it a string
            throw;
        }

        private:
            std::unique_ptr<void> _data;
    };*/

template<>
struct JSONData<std::string, void> : public JSONNode
{
  JSONData()
  {}

  JSONData(const std::string &str)
    : _data(str)
  {}

  std::string GetData() const
  {
    return _data;
  }

  void SetData(const std::string &data)
  {
    _data = data;
  }

  std::string ToString(Style style, int depth) const override
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    return WrapString(_data);
  }

private:
  std::string _data;
};

template<typename T>// declval is needed to create a 'fake instance of a type' to get the result of to_string (https://en.cppreference.com/w/cpp/utility/declval)
struct JSONData<T, std::void_t<decltype(std::to_string(std::declval<T>()))>> : public JSONNode
{
  JSONData()
  {}

  JSONData(const T &data)
    : _data(data)
  {}

  // runtimeId_t would only help with serialization, not deserialization (which is when we need it most)
  T GetData() const
  {
    return _data;
  }

  void SetData(const T &data)
  {
    _data = data;
  }

  std::string ToString(Style style, int depth) const override
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    return std::to_string(_data);
  }

private:
  T _data;
};

// use these instead of custom JSONData's
// reason being: we can only deserialize into specific types based on knowledge when deserializing (if float or int)
// this way we default to large values to hopefully not lose data
using JSONDecimal = JSONData<long double>;
using JSONNumber = JSONData<long long>;
using JSONString = JSONData<std::string>;

template <typename T, typename = void>
struct json_type
{};

template <typename T>
struct json_type<T, std::void_t<std::enable_if_t<std::is_arithmetic_v<T> && !std::is_floating_point_v<T>>>>
{
  using type = JSONNumber;
};

template <typename T>
struct json_type<T, std::void_t<std::enable_if_t<std::is_arithmetic_v<T> && std::is_floating_point_v<T>>>>
{
  using type = JSONDecimal;
};

template <typename T>
struct json_type<T, std::void_t<std::enable_if_t<std::is_same<raw_type_t<T>, std::string>::value>>>
{
  using type = JSONString;
};

struct JSONObject : public JSONNode
{
  size_t Count() const
  {
    return _elements.size();
  }

  void AddElement(const std::string &key, std::shared_ptr<JSONNode> element)
  {
    _elements[key] = move(element);
  }

  void RemoveKey(const std::string &key)
  {
    _elements.erase(key);
  }

  std::shared_ptr<JSONNode> GetElement(const std::string &key) const
  {
    return _elements.at(key);
  }

  std::string ToString(Style style, int depth) const override
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    std::string str = NodeSpace(style) + ElementSpace(style, depth) + "{" + NodeSpace(style);

    depth += 1;

    bool first = true;
    for (std::pair<std::string, std::shared_ptr<JSONNode>> pair : _elements) {
      if (!first) {
        str += ",";
        str += NodeSpace(style);
      }

      str += ElementSpace(style, depth);

      str += WrapString(pair.first) + " : ";
      str += pair.second->ToString(style, depth + 1);

      first = false;
    }

    str += NodeSpace(style) + ElementSpace(style, depth - 1) + "}";

    return str;
  }

private:
  std::map<std::string, std::shared_ptr<JSONNode>> _elements;
};

struct JSONArray : public JSONNode
{
  size_t Count() const
  {
    return _elements.size();
  }

  void AddElement(std::shared_ptr<JSONNode> element)
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    _elements.push_back(move(element));
  }

  std::shared_ptr<JSONNode> GetElement(const int &index) const
  {
    return _elements[index];
  }

  void RemoveIndex(const uint32_t &index)
  {
    _elements.erase(_elements.begin() + index);
  }

  std::string ToString(Style style, int depth) const override
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    std::string str = NodeSpace(style) + ElementSpace(style, depth) + "[" + NodeSpace(style);

    depth += 1;

    for (auto node : _elements) {
      str += ElementSpace(style, depth);
      str += node->ToString(style, depth + 1);
      if (node != _elements[_elements.size() - 1]) {
        str += ",";
        str += NodeSpace(style);
      }
    }

    str += NodeSpace(style) + ElementSpace(style, depth - 1) + "]";

    return str;
  }

private:
  std::vector<std::shared_ptr<JSONNode>> _elements;
};
}// namespace Core::Serialization::Format