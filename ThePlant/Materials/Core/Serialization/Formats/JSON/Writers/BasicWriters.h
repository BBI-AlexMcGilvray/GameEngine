#pragma once

#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "Core/Reflection/type_traits.h"
#include "Core/Serialization/type_traits.h"
#include "Core/Serialization/Formats/JSON/JSONTypes.h"

namespace Core::Serialization::Format {
// simple type writer
template<typename Object, typename = void>
struct json_writer
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


struct JSON; // hack to specialize for this type
template <typename Object>
struct json_writer<Object, std::enable_if_t<std::is_same<Object, JSON>::value>> // deserialize to json
{
    std::shared_ptr<JSONNode> Write(const std::shared_ptr<JSONNode>& obj)
    {
        return obj->CreateCopy(); // can't just take another shared_ptr reference, we need to create a copy
    }
};

// custom type writer
// template <typename Object> // WHY IS THIS NOT WORKING?
// struct json_writer<Object, std::void_t<decltype(&Object::serialize)>> // class has serialize method
// {
//   std::shared_ptr<JSONNode> Write(const Object& target)
//   {
//     return target.serialize(node);
//   }
// };

template <typename Object>
struct json_writer<Object, std::void_t<decltype(serialize(std::declval<const Object&>()))>> // if there is a serialize method that takes class reference
{
std::shared_ptr<JSONNode> Write(const Object& obj)
{
    return serialize(obj);
}
};

template <typename Object>
struct json_writer<Object, typename std::enable_if<is_specialization_of<raw_type_t<Object>, std::variant>::value>::type> // if the object is a variant
{
struct variant_writer_visitor
{
    template <typename T>
    std::shared_ptr<JSONNode> operator()(const T& val)
    {
    return json_writer<raw_type_t<T>>().Write(val);
    }
};

std::shared_ptr<JSONNode> Write(const Object& obj)
{
    std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

    json->AddElement("index", json_writer<int>().Write(static_cast<int>(obj.index())));
    json->AddElement("value", std::visit(variant_writer_visitor(), obj));

    return json;
}
};

template <typename Object>
struct json_writer<Object, typename std::enable_if<is_specialization_of<Object, std::pair>::value>::type> // if the object is a pair
{
std::shared_ptr<JSONNode> Write(const Object& obj)
{
    std::shared_ptr<JSONObject> json = std::make_shared<JSONObject>();

    json->AddElement("first", json_writer<raw_type_t<decltype(std::declval<Object>().first)>>().Write(obj.first));
    json->AddElement("second", json_writer<raw_type_t<decltype(std::declval<Object>().second)>>().Write(obj.second));

    return json;
}
};

template <typename Object>
struct json_writer<Object, typename std::enable_if<is_specialization_of<Object, std::tuple>::value>::type> // if the object is a tuple
{
template <int INDEX>
struct tuple_index_writer
{
    static void Write(std::shared_ptr<JSONObject> json, const Object& tuple)
    {
    json->AddElement(json_writer<std::tuple_element<INDEX, Object>>(std::get<INDEX>(tuple)), std::to_string(INDEX));
    tuple_index_writer<INDEX - 1>::Write(json, tuple);
    }
};

template <>
struct tuple_index_writer<0>
{
    static void Write(std::shared_ptr<JSONObject> json, const Object& tuple)
    {
    json->AddElement(json_writer<std::tuple_element<0, Object>>(std::get<0>(tuple)), std::to_string(0));
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
struct json_writer<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
{
struct field_writer
{
    field_writer(std::shared_ptr<JSONObject> json)
    : _json(json)
    {}

    template<typename FieldData>
    void operator()(FieldData f)
    {
    _json->AddElement(f.name(), json_writer<raw_type_t<decltype(f.get())>>().Write(f.get()));
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

// iterable type writer
template<typename Object>
struct json_writer<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value && !(std::is_same<raw_type_t<Object>, std::string>::value)>::type>>
{
    // better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
    // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer
    // ** https://en.cppreference.com/w/cpp/types/std::void_t
    std::shared_ptr<JSONNode> Write(const Object &obj)
    {
        SCOPED_MEMORY_CATEGORY("JSON");
        std::shared_ptr<JSONArray> writtenObj = std::make_shared<JSONArray>();

        for (const auto &elem : obj) {
            writtenObj->AddElement(json_writer<raw_type_t<decltype(*(std::declval<Object>().begin()))>>().Write(elem));
        }

        return writtenObj;
    }
};
}// namespace Core::Serialization::Format