#pragma once

#include <memory>
#include <string>
#include <vector>

#include "Core/Debugging/Memory/MemoryTrackerUtils.h"
#include "Core/Headers/UtilityMacros.h"
#include "Core/Serialization/Formats/JSON/JSONTypes.h"
#include "Core/Serialization/Formats/JSON/Readers/BasicReaders.h"
#include "Core/Serialization/Formats/JSON/Writers/BasicWriters.h"

namespace Core::Serialization::Format {
struct JSON
{
  template<typename Object>
  void Write(const Object &obj, std::string key)
  {
    _data->AddElement(key, json_writer<Object>().Write(obj));
  }

  template <typename Object>
  void Write(const Object& obj)
  {
    if (std::shared_ptr<JSONObject> asObject = std::dynamic_pointer_cast<JSONObject>(json_writer<Object>().Write(obj)))
    {
      _data = asObject;
      return;
    }
    throw; // this should only ever get called if it will result in a JSONObject, otherwise a key must be provided
  }

  template<typename Object>
  void Read(Object& target, const std::string &key) const
  {
    return json_reader<Object>().Read(target, _data->GetElement(key));
  }

  template <typename Object>
  void Read(Object& target) const
  {
    return json_reader<Object>().Read(target, _data);
  }

  std::string ToString(Style style) const
  {
    SCOPED_MEMORY_CATEGORY("JSON");
    return _data->ToString(style, 0);
  }

  void FromJSON(const std::shared_ptr<JSONNode>& json)
  {
    Core::Ptr<JSONObject> jsonObject = dynamic_cast<Core::Ptr<JSONObject>>(json.get());
    if (jsonObject)
    {
      _data = std::unique_ptr<JSONObject>(static_cast<Core::Ptr<JSONObject>>(jsonObject->CreateCopy().release()));
      return;
    }

    throw; // JSON can only be a JSONObject
  }

  std::shared_ptr<JSONObject> Data() const
  {
    return _data;
  }

  std::unique_ptr<JSONNode> CreateCopy() const
  {
    return _data->CreateCopy();
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