#pragma once

#include <array>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "Core/Reflection/type_traits.h"
#include "Core/Serialization/type_traits.h"

#include "Pipeline/Dependencies/IMGUI/imgui.h"
#include "Pipeline/Factory_Temp/UIUtils.h"

namespace Editor::UI {
// fallback ui creator
template<typename Object, typename = void>
struct ui_creator
{
    void CreateUI(Object& data)
    {
        throw; // this type is not handled
    }
};

template <typename Object>
struct ui_creator<Object, std::void_t<decltype(ShowUI(std::declval<Object&>()))>> // if there is a CreateUI method that takes class reference
{
    void CreateUI(Object& data)
    {
        ShowUI(data);
    }
};

template <typename Object>
struct ui_creator<Object, typename std::enable_if<is_specialization_of<Object, std::variant>::value>::type> // if the object is a variant
{
    template <typename VARIANT, int INDEX>
    struct variant_ui_creator_by_index
    {
        static void CreateForIndex(VARIANT& variant, int index)
        {
            if (index == INDEX)
            {
                using used_alternative = std::variant_alternative<INDEX, VARIANT>::type;
                used_alternative& usedValue = std::get<INDEX>(variant);

                ui_creator<used_alternative>().CreateUI(usedValue);
                return;
            }
            
            return variant_ui_creator_by_index<VARIANT, INDEX - 1>::CreateUI(variant, index);
        }
    };

    template <typename VARIANT>
    struct variant_ui_creator_by_index<VARIANT, 0>
    {
        static void CreateForIndex(VARIANT& variant, int index)
        {
            if (index == 0)
            {
                using used_alternative = std::variant_alternative<0, VARIANT>::type;
                used_alternative& usedValue = std::get<0>(variant);

                ui_creator<used_alternative>().CreateUI(usedValue);
                return;
            }
            
            throw;
        }
    };

    void CreateUI(Object& data)
    {
        ImGui::Text("This is a variant, should we display the other options?");
        variant_reader_by_index<Object, std::variant_size_v<Object> - 1>::ReadIndex(data, data.index());
    }
};

template <typename Object>
struct ui_creator<Object, typename std::enable_if<is_specialization_of<Object, std::pair>::value>::type> // if the object is a pair
{
    void CreateUI(Object& data)
    {        
        // HACK: when using pairs in things like maps, the first element is const - and we cant have that
        typedef raw_type_t<decltype(std::declval<Object>().first)> first_type;
        json_reader<first_type>().CreateUI(const_cast<first_type&>(data.first));
        ImGui::TEXT(" : ");
        json_reader<raw_type_t<decltype(std::declval<Object>().second)>>().CreateUI(data.second);
    }
};

template <typename Object>
struct ui_creator<Object, typename std::enable_if<is_specialization_of<Object, std::tuple>::value>::type> // if the object is a tuple
{
    template <int INDEX>
    struct tuple_index_ui_creator
    {
        static void CreateUI(const Object& tuple)
        {
            ui_creator<raw_type_t<std::tuple_element<INDEX, Object>>>().CreateUI(std::get<INDEX>(tuple));
            tuple_index_ui_creator<INDEX - 1>::CreateUI(tuple);
        }
    };

    template <>
    struct tuple_index_ui_creator<0>
    {
        static void CreateUI(const Object& tuple)
        {
            ui_creator<raw_type_t<std::tuple_element<0, Object>>>().CreateUI(std::get<0>(tuple));
        }
    };

    void CreateUI(Object& data)
    {
        tuple_index_writer<std::tuple_size<Object> - 1>::CreateUI(data);
    }
};

// object type writer
template<typename Object>
struct ui_creator<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
{
    struct field_ui_creator
    {
        field_ui_creator()
        {}

        template<typename FieldData>
        void operator()(FieldData f)
        {
            ImGui::Text(f.name());
            ui_creator<raw_type_t<decltype(f.get())>>().CreateUI(f.get());
        }
    };

    void CreateUI(Object& data)
    {
        reflector::visit_all(data, field_reader());
    }
};

// iterable type writer
template<typename Object>
struct ui_creator<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value && !(std::is_same<raw_type_t<Object>, std::string>::value)>::type>>
{
    // better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
    // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer
    void CreateUI(Object& data)
    {
        if (ImGui::TreeNode("Trees"))
        {
            for (auto &elem : data) {
                ui_creator<raw_type_t<decltype(*(std::declval<Object>().begin()))>>().CreateUI(elem);
            }
        }
        ImGui::TreePop();
    }
};
}// namespace Editor::UI