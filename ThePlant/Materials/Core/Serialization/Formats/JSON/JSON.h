#pragma once

#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/UtilityMacros.h"
#include "Core/Logging/LogFunctions.h"
#include "Core/Reflection/type_traits.h"
#include "Core/Serialization/type_traits.h"

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

struct JSON
{
  // simple type writer
  template<typename Object, typename = void>
  struct object_writer_visitor
  {
    using object_json_type = typename json_type<Object>::type;

    std::shared_ptr<JSONNode> Write(const Object &obj)
    { // may need to make this only use the 'approved' json data types (JSONNumber, JSONDecimal, JSONString) - but can be handled later
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<object_json_type> writtenObj = std::make_shared<object_json_type>();
      writtenObj->SetData(obj);
      return writtenObj;
    }
  };

  // custom type writer
  // template <typename Object> // WHY IS THIS NOT WORKING?
  // struct object_writer_visitor<Object, std::void_t<decltype(&Object::serialize)>> // class has serialize method
  // {
  //   std::shared_ptr<JSONNode> Write(const Object& target)
  //   {
  //     return target.serialize(node);
  //   }
  // };
  
  template <typename Object>
  struct object_writer_visitor<Object, std::void_t<decltype(serialize(std::declval<const Object&>()))>> // if there is a serialize method that takes class reference
  {
    std::shared_ptr<JSONNode> Write(const Object& obj)
    {
      return serialize(obj);
    }
  };
  
  template <typename Object>
  struct object_writer_visitor<Object, typename std::enable_if<is_specialization_of<raw_type_t<Object>, std::variant>::value>::type> // if the object is a variant
  {
    struct variant_writer_visitor
    {
      template <typename T>
      std::shared_ptr<JSONNode> operator()(const T& val)
      {
        return object_writer_visitor<raw_type_t<T>>().Write(val);
      }
    };

    std::shared_ptr<JSONNode> Write(const Object& obj)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

      json->AddElement("index", object_writer_visitor<int>().Write(static_cast<int>(obj.index())));
      json->AddElement("value", std::visit(variant_writer_visitor(), obj));

      return json;
    }
  };
  
  template <typename Object>
  struct object_writer_visitor<Object, typename std::enable_if<is_specialization_of<Object, std::pair>::value>::type> // if the object is a pair
  {
    std::shared_ptr<JSONNode> Write(const Object& obj)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

      json->AddElement("first", object_writer_visitor<raw_type_t<decltype(std::declval<Object>().first)>>().Write(obj.first));
      json->AddElement("second", object_writer_visitor<raw_type_t<decltype(std::declval<Object>().second)>>().Write(obj.second));

      return json;
    }
  };
  
  template <typename Object>
  struct object_writer_visitor<Object, typename std::enable_if<is_specialization_of<Object, std::tuple>::value>::type> // if the object is a tuple
  {
    template <int INDEX>
    struct tuple_index_writer
    {
      static void Write(std::shared_ptr<JSONObject> json, const Object& tuple)
      {
        json->AddElement(object_writer_visitor<std::tuple_element<INDEX, Object>>(std::get<INDEX>(tuple)), std::to_string(INDEX));
        tuple_index_writer<INDEX - 1>::Write(json, tuple);
      }
    };
    
    template <>
    struct tuple_index_writer<0>
    {
      static void Write(std::shared_ptr<JSONObject> json, const Object& tuple)
      {
        json->AddElement(object_writer_visitor<std::tuple_element<0, Object>>(std::get<0>(tuple)), std::to_string(0));
      }
    };

    std::shared_ptr<JSONNode> Write(const Object& obj)
    {
      std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

      tuple_index_writer<std::tuple_size<Object> - 1>::Write(json, obj);

      return json;
    }
  };

  // object type writer
  template<typename Object>
  struct object_writer_visitor<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
  {
    struct field_writer
    {
      field_writer(std::shared_ptr<JSONObject> json)
        : _json(json)
      {}

      template<typename FieldData>
      void operator()(FieldData f)
      {
        _json->AddElement(f.name(), object_writer_visitor<raw_type_t<decltype(f.get())>>().Write(f.get()));
      }

    private:
      std::shared_ptr<JSONObject> _json;
    };

    std::shared_ptr<JSONNode> Write(const Object &obj)
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONObject> writtenObj = std::make_shared<JSONObject>();

      reflector::visit_all(obj, field_writer(writtenObj));

      return writtenObj;
    }
  };

  // array type writer
  template<typename Object>
  struct object_writer_visitor<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value && !(std::is_same<raw_type_t<Object>, std::string>::value)>::type>>
  // struct object_writer_visitor<Object, std::void_t<std::enable_if<is_iterable<Object>::value && !std::is_same<Object, std::string>::value>>::type>
  {// better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
    // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer
    // ** https://en.cppreference.com/w/cpp/types/std::void_t
    std::shared_ptr<JSONNode> Write(const Object &obj)
    {
      SCOPED_MEMORY_CATEGORY("JSON");
      std::shared_ptr<JSONArray> writtenObj = std::make_shared<JSONArray>();

      for (const auto &elem : obj) {
        writtenObj->AddElement(object_writer_visitor<raw_type_t<decltype(*(std::declval<Object>().begin()))>>().Write(elem));
      }

      return writtenObj;
    }
  };

  // simple type writer
  template<typename Object, typename = void>
  struct object_reader_visitor
  {
    using object_json_type = typename json_type<Object>::type;

    void Read(Object& target, std::shared_ptr<JSONNode> node)
    { // issue reading since we only parse data into JSONNumber and JSONDecimal for numbers now...
      object_json_type *data = dynamic_cast<object_json_type *>(node.get());
      if (data == nullptr) {
        throw;
      }
      target = static_cast<raw_type_t<Object>>(data->GetData());
    }
  };

  // custom type writer
  // template <typename Object> // WHY IS THIS NOT WORKING?
  // struct object_reader_visitor<Object, std::void_t<decltype(&Object::deserialize)>> // class has deserialize method
  // {
  //   void Read(Object& target, std::shared_ptr<JSONNode> node)
  //   {
  //     target.deserialize(node);
  //   }
  // };
  
  template <typename Object>
  struct object_reader_visitor<Object, std::void_t<decltype(deserialize(std::declval<Object&>(), std::declval<std::shared_ptr<JSONNode>>()))>> // if there is a deserialize method that takes class reference
  {
    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
      deserialize(target, node);
    }
  };
  
  template <typename Object>
  struct object_reader_visitor<Object, typename std::enable_if<is_specialization_of<Object, std::variant>::value>::type> // if the object is a variant
  {
    template <typename VARIANT, int INDEX>
    struct variant_reader_by_index
    {
      static void ReadIndex(VARIANT& variant, int index, std::shared_ptr<JSONNode> node)
      {
        if (index == INDEX)
        {
          using used_alternative = std::variant_alternative<INDEX, VARIANT>::type;
          used_alternative usedValue;
          object_reader_visitor<used_alternative>().Read(usedValue, node);

          variant = usedValue;
          return;
        }
        
        return variant_reader_by_index<VARIANT, INDEX - 1>::ReadIndex(variant, index, node);
      }
    };

    template <typename VARIANT>
    struct variant_reader_by_index<VARIANT, 0>
    {
      static void ReadIndex(VARIANT& variant, int index, std::shared_ptr<JSONNode> node)
      {
        if (index == 0)
        {
          using used_alternative = std::variant_alternative<0, VARIANT>::type;
          used_alternative usedValue;
          object_reader_visitor<used_alternative>().Read(usedValue, node);

          variant = usedValue;
          return;
        }
        
        throw;
      }
    };

    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
      JSONObject *obj = dynamic_cast<JSONObject *>(node.get());
      if (obj == nullptr) {
        throw;
      }

      int index;
      object_reader_visitor<int>().Read(index, obj->GetElement("index"));

      variant_reader_by_index<Object, std::variant_size_v<Object> - 1>::ReadIndex(target, index, obj->GetElement("value"));
    }
  };

  template <typename Object>
  struct object_reader_visitor<Object, typename std::enable_if<is_specialization_of<Object, std::pair>::value>::type> // if the object is a pair
  {
    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
      JSONObject *obj = dynamic_cast<JSONObject *>(node.get());
      if (obj == nullptr) {
        throw;
      }
      
      // HACK: when using pairs in things like maps, the first element is const - and we cant have that
      typedef raw_type_t<decltype(std::declval<Object>().first)> first_type;
      object_reader_visitor<first_type>().Read(const_cast<first_type&>(target.first), obj->GetElement("first"));
      object_reader_visitor<raw_type_t<decltype(std::declval<Object>().second)>>().Read(target.second, obj->GetElement("second"));
    }
  };
  
  template <typename Object>
  struct object_reader_visitor<Object, typename std::enable_if<is_specialization_of<Object, std::tuple>::value>::type> // if the object is a tuple
  {
    template <int INDEX>
    struct tuple_index_reader
    {
      static void Read(const Object& tuple, std::shared_ptr<JSONObject> json)
      {
        object_reader_visitor<raw_type_t<std::tuple_element<INDEX, Object>>>().Read(std::get<INDEX>(tuple), std::to_string(INDEX));
        tuple_index_reader<INDEX - 1>::Read(tuple, json);
      }
    };
    
    template <>
    struct tuple_index_reader<0>
    {
      static void Read(const Object& tuple, std::shared_ptr<JSONObject> json)
      {
        object_reader_visitor<raw_type_t<std::tuple_element<0, Object>>>().Read(std::get<0>(tuple), std::to_string(0));
      }
    };

    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
      JSONObject *obj = dynamic_cast<JSONObject *>(node.get());
      if (obj == nullptr) {
        throw;
      }

      tuple_index_writer<std::tuple_size<Object> - 1>::Read(target, obj);
    }
  };

  // object type writer
  template<typename Object>
  struct object_reader_visitor<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
  {
    struct field_reader
    {
      field_reader(JSONObject *json)
        : _json(json)
      {}

      template<typename FieldData>
      void operator()(FieldData f)
      {
        object_reader_visitor<raw_type_t<decltype(f.get())>>().Read(f.get(), _json->GetElement(f.name()));
      }

    private:
      JSONObject *_json;
    };

    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
      JSONObject *obj = dynamic_cast<JSONObject *>(node.get());
      if (obj == nullptr) {
        throw;
      }

      reflector::visit_all(target, field_reader(obj));
    }
  };

  // array type writer
  template<typename Object>
  struct object_reader_visitor<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value && !(std::is_same<raw_type_t<Object>, std::string>::value)>::type>>
  {// better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
    // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer

  private:
    // template <typename RESERVABLE>
    // void reserve(RESERVABLE& reservable, size_t newSize)
    // {
    //   if constexpr (std::is_void<std::enable_if<decltype(std::declval<RESERVABLE>().reserve(size_t))>::type>::value)
    //   {
    //     reservable.reserve(newSize);
    //   }
    // }

    // // std::arrays can't be resized
    // template <typename T, size_t SIZE>
    // void reserve(std::array<T, SIZE>& nonreservable, size_t newSize) { assert(SIZE >= newSize); /*, "expected size and actual size must match");*/ } // need a DEBUG_ASSERT (and others) macro

  public:
    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
      JSONArray *arr = dynamic_cast<JSONArray *>(node.get());
      if (arr == nullptr) {
        throw;
      }

      // this would be a nice optimization, but not working at the moment
      // reserve(target, arr->Count());

      typedef raw_type_t<decltype(std::declval<Object>())>::value_type index_type;
      for (int i = 0; i < arr->Count(); i++) {
        auto newElement = index_type{};
        object_reader_visitor<index_type>().Read(newElement, arr->GetElement(i));
        target.insert(target.end(), newElement); // this makes it work for vectors and maps, but likely makes maps less performant
      }
    }
  };

  template<typename Object>
  void Write(const Object &obj, std::string key)
  {
    _data->AddElement(key, object_writer_visitor<Object>().Write(obj));
  }

  template <typename Object>
  void Write(const Object& obj)
  {
    if (std::shared_ptr<JSONObject> asObject = std::dynamic_pointer_cast<JSONObject>(object_writer_visitor<Object>().Write(obj)))
    {
      _data = asObject;
      return;
    }
    throw; // this should only ever get called if it will result in a JSONObject, otherwise a key must be provided
  }

  template<typename Object>
  void Read(Object& target, const std::string &key) const
  {
    return object_reader_visitor<Object>().Read(target, _data->GetElement(key));
  }

  template <typename Object>
  void Read(Object& target) const
  {
    return object_reader_visitor<Object>().Read(target, _data);
  }

  std::string ToString(Style style) const
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    return _data->ToString(style, 0);
  }

  /* parsing taken from: https://wiki.unity3d.com/index.php/SimpleJSON */
  // could likely be cleaned up
  void Parse(const std::string &json)
  {
    SCOPED_MEMORY_CATEGORY("JSON");

    std::vector<std::shared_ptr<JSONNode>> activeStack;
    std::shared_ptr<JSONNode> active = nullptr;
    bool inQuotes = false;
    std::string tokenKey;
    std::string token;

    auto consumeTokens = [&token, &tokenKey]() {
      tokenKey.clear();
      token.clear();
    };

    int i = 0;
    while (i < json.length()) {
      char c = json[i];

      switch (c) {
      case '{': {
        if (inQuotes) {
          token += c;
          break;
        }

        activeStack.push_back(std::make_shared<JSONObject>());
        if (active != nullptr) {
          AddElementToNode(active, tokenKey, activeStack[activeStack.size() - 1]);
        }
        active = activeStack[activeStack.size() - 1];
        tokenKey.clear();
        token.clear();
        break;
      }
      case '[': {
        if (inQuotes) {
          token += c;
          break;
        }

        activeStack.push_back(std::make_shared<JSONArray>());
        if (active != nullptr) {
          AddElementToNode(active, tokenKey, activeStack[activeStack.size() - 1]);
        }
        active = activeStack[activeStack.size() - 1];
        tokenKey.clear();
        token.clear();
        break;
      }
      case '}':
      case ']': {
        if (inQuotes) {
          token += c;
          break;
        }

        if (!active) {
          throw;// too many brackets
        }
        activeStack.pop_back();

        if (token.size() > 0) {
          AddElementToNode(active, tokenKey, token);
        }
        consumeTokens();
        if (activeStack.size() > 0) {
          active = activeStack[activeStack.size() - 1];
        }
        break;
      }
      case ':': {
        if (inQuotes) {
          token += c;
          break;
        }

        tokenKey = token;
        token.clear();
        break;
      }
      case '"': {
        inQuotes ^= true;
        break;
      }
      case ',': {
        if (inQuotes) {
          token += c;
          break;
        }

        if (token.size() > 0) {
          AddElementToNode(active, tokenKey, token);
        }
        consumeTokens();
        break;
      }
      case '\r':
      case '\n': {
        if (inQuotes) {
          token += c;
        }
        break;
      }
      case ' ':
      case '\t': {
        if (inQuotes) {
          token += c;
        }
        break;
      }
      case '\\': {
        ++i;
        if (inQuotes) {
          char nestedC = json[i];
          switch (nestedC) {
          case 't':
            token += '\t';
            break;
          case 'r':
            token += '\r';
            break;
          case 'n':
            token += '\n';
            break;
          case 'b':
            token += '\b';
            break;
          case 'f':
            token += '\f';
            break;
          case 'u': {
            // figure out
            // string s = aJSON.Substring(i + 1, 4);
            // Token.Append((char)int.Parse(
            //     s,
            //     System.Globalization.NumberStyles.AllowHexSpecifier));
            // i += 4;
            break;
          }
          default:
            token += nestedC;
            break;
          }
        }
        break;
      }
      default: {
        token += c;
        break;
      }
      }

      i++;
    }

    if (inQuotes) {
      // specify exception
      throw;
    }

    _data = std::dynamic_pointer_cast<JSONObject>(active);
    if (_data.get() == nullptr) {
      throw;// json parsed was not wrapped in an object, not acceptable
    }
  }

  // to allow for adding elements through the serialization API
  operator std::shared_ptr<JSONObject>()
  {
    return _data;
  }

private:
  std::shared_ptr<JSONObject> _data = std::make_shared<JSONObject>();// ideally created in constructor? or when accessed initially

  void AddElementToNode(std::shared_ptr<JSONNode> node, const std::string &tokenKey, const std::string &token)
  {
    JSONObject *asObject = dynamic_cast<JSONObject *>(node.get());
    if (asObject != nullptr) {
      asObject->AddElement(tokenKey, TokenToJSONNode(token));
      return;
    }

    JSONArray *asArray = dynamic_cast<JSONArray *>(node.get());
    if (asArray != nullptr) {
      asArray->AddElement(TokenToJSONNode(token));
      return;
    }
  }

  void AddElementToNode(std::shared_ptr<JSONNode> node, const std::string &tokenKey, std::shared_ptr<JSONNode> childNode)
  {
    JSONObject *asObject = dynamic_cast<JSONObject *>(node.get());
    if (asObject != nullptr) {
      asObject->AddElement(tokenKey, childNode);
      return;
    }

    JSONArray *asArray = dynamic_cast<JSONArray *>(node.get());
    if (asArray != nullptr) {
      asArray->AddElement(childNode);
      return;
    }
  }

  std::shared_ptr<JSONNode> TokenToJSONNode(const std::string &token)
  {
    SCOPED_MEMORY_CATEGORY("JSON");

    size_t readCharCount = 0;

    try
    {
      long long asLongLong = stoll(token, &readCharCount);
      if (readCharCount == token.size()) {
        return std::make_shared<JSONNumber>(asLongLong);
      }
    }
    catch(const std::invalid_argument& e)
    {
      UNUSED(e);
    }

    try
    {
      long double asLongDouble = stold(token, &readCharCount);
      if (readCharCount == token.size()) {
        return std::make_shared<JSONDecimal>(asLongDouble);
      }
    }
    catch(const std::invalid_argument& e)
    {
      UNUSED(e);
    }

    return std::make_shared<JSONString>(token);
  }
};
}// namespace Core::Serialization::Format