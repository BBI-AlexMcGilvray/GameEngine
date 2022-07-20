#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "Core/Reflection/type_traits.h"
#include "Core/Serialization/type_traits.h"
#include "Core/Serialization/Formats/JSON/JSONTypes.h"

namespace Core::Serialization::Format {
// simple type reader
template<typename Object, typename = void>
struct json_reader
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
// struct json_reader<Object, std::void_t<decltype(&Object::deserialize)>> // class has deserialize method
// {
//   void Read(Object& target, std::shared_ptr<JSONNode> node)
//   {
//     target.deserialize(node);
//   }
// };

template <typename Object>
struct json_reader<Object, std::void_t<decltype(deserialize(std::declval<Object&>(), std::declval<std::shared_ptr<JSONNode>>()))>> // if there is a deserialize method that takes class reference
{
    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
        deserialize(target, node);
    }
};

template <typename Object>
struct json_reader<Object, typename std::enable_if<is_specialization_of<Object, std::variant>::value>::type> // if the object is a variant
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
            json_reader<used_alternative>().Read(usedValue, node);

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
            json_reader<used_alternative>().Read(usedValue, node);

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
        json_reader<int>().Read(index, obj->GetElement("index"));

        variant_reader_by_index<Object, std::variant_size_v<Object> - 1>::ReadIndex(target, index, obj->GetElement("value"));
    }
};

template <typename Object>
struct json_reader<Object, typename std::enable_if<is_specialization_of<Object, std::pair>::value>::type> // if the object is a pair
{
    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
        JSONObject *obj = dynamic_cast<JSONObject *>(node.get());
        if (obj == nullptr) {
        throw;
        }
        
        // HACK: when using pairs in things like maps, the first element is const - and we cant have that
        typedef raw_type_t<decltype(std::declval<Object>().first)> first_type;
        json_reader<first_type>().Read(const_cast<first_type&>(target.first), obj->GetElement("first"));
        json_reader<raw_type_t<decltype(std::declval<Object>().second)>>().Read(target.second, obj->GetElement("second"));
    }
};

template <typename Object>
struct json_reader<Object, typename std::enable_if<is_specialization_of<Object, std::tuple>::value>::type> // if the object is a tuple
{
    template <int INDEX>
    struct tuple_index_reader
    {
        static void Read(const Object& tuple, std::shared_ptr<JSONObject> json)
        {
        json_reader<raw_type_t<std::tuple_element<INDEX, Object>>>().Read(std::get<INDEX>(tuple), std::to_string(INDEX));
        tuple_index_reader<INDEX - 1>::Read(tuple, json);
        }
    };

    template <>
    struct tuple_index_reader<0>
    {
        static void Read(const Object& tuple, std::shared_ptr<JSONObject> json)
        {
        json_reader<raw_type_t<std::tuple_element<0, Object>>>().Read(std::get<0>(tuple), std::to_string(0));
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
struct json_reader<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
{
    struct field_reader
    {
        field_reader(JSONObject *json)
        : _json(json)
        {}

        template<typename FieldData>
        void operator()(FieldData f)
        {
        json_reader<raw_type_t<decltype(f.get())>>().Read(f.get(), _json->GetElement(f.name()));
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
// template<typename Object>
// struct json_reader<Object, std::void_t<typename std::enable_if<(is_specialization_of<Object, std::map>::value || is_specialization_of<Object, std::unordered_map>::value)>::type>>
// {
//     // better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
//     // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer

//     private:
//     template <typename T, size_t SIZE>
//     void size_assert(std::array<T, SIZE>& nonreservable, size_t newSize) { assert(SIZE >= newSize); /*, "expected size and actual size must match");*/ }

//     public:
//     void Read(Object& target, std::shared_ptr<JSONNode> node)
//     {
//         JSONArray *arr = dynamic_cast<JSONArray *>(node.get());
//         if (arr == nullptr) {
//             throw;
//         }

//         typedef raw_type_t<decltype(std::declval<Object>())>::value_type index_type;
//         for (int i = 0; i < arr->Count(); i++) {
//             auto newElement = index_type{};
//             json_reader<index_type>().Read(newElement, arr->GetElement(i));
//             target.insert(target.end(), newElement);
//         }
//     }
// };

// iterable type writer
template<typename Object>
struct json_reader<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value && !(std::is_same<raw_type_t<Object>, std::string>::value)>::type>>
{
    // better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
    // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer
private:
    using index_type = typename raw_type_t<decltype(std::declval<Object>())>::value_type;

    // template <typename RESIZABLE>
    // void resize(RESIZABLE& resizable, size_t newSize)
    // {
    //     if constexpr (decltype(std::declval<RESIZABLE>().resize(size_t))) // this will work if we find a way to 'if constexpr' the existence of the resize method (or reserve if we are inserting)
    //     resizable.resize(newSize);
    // }

    // // // std::arrays can't be resized
    // template <typename T, size_t SIZE>
    // void resize(std::array<T, SIZE>& arr, size_t newSize) { assert(SIZE >= newSize); /*, "expected size and actual size must match");*/ }

    template <typename INSERTABLE>
    void insert(INSERTABLE& target, index_type&& item, int index)
    {
        target.insert(target.end(), item);
    }
    
    template <typename T, size_t SIZE>
    void insert(std::array<T, SIZE>& target, index_type&& item, int index)
    {
        target[index] = std::move(item);
    }

public:
    void Read(Object& target, std::shared_ptr<JSONNode> node)
    {
        JSONArray *arr = dynamic_cast<JSONArray *>(node.get());
        if (arr == nullptr) {
        throw;
        }

        // this would be a nice optimization, but not working at the moment
        // resize(target, arr->Count());

        typedef raw_type_t<decltype(std::declval<Object>())>::value_type index_type;
        for (int i = 0; i < arr->Count(); i++) {
            auto newElement = index_type{};
            json_reader<index_type>().Read(newElement, arr->GetElement(i));
            insert(target, std::move(newElement), i);
        }
    }
};
}// namespace Core::Serialization::Format