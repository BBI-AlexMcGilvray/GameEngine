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

/*
NOTE: The text may not be getting forwarded properly in some of these cases
    - if the UI looks like text is in the wrong spot/is weird, that is probably why!
*/

namespace Editor::UI {
// fallback ui creator
template<typename Object, typename = void>
struct ui_creator
{
    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {
        throw; // this type is not handled
    }
};

template <typename Object>
struct ui_creator<Object, std::void_t<decltype(ShowUI(std::declval<Object&>(), std::declval<const std::string&>(), std::declval<std::string&>()))>> // if there is a CreateUI method that takes class reference
{
    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {
        ShowUI(data, text, id);
    }
};

template <typename Object>
struct ui_creator<Object, typename std::enable_if<is_specialization_of<Object, std::variant>::value>::type> // if the object is a variant
{
    template <typename VARIANT>
    struct variant_options
    {
        static constexpr size_t variant_size = std::variant_size_v<VARIANT>;

        template <int INDEX>
        struct variant_option
        {
            static void set(std::array<std::string, variant_size>& array)
            {
                using index_type = std::variant_alternative<INDEX, VARIANT>::type;
                array[INDEX] = std::string(Core::TemplateTypeAsString<index_type>());

                variant_option<INDEX - 1>::set(array);
            }
        };
        
        template <>
        struct variant_option<0>
        {
            static void set(std::array<std::string, variant_size>& array)
            {
                using index_type = std::variant_alternative<0, VARIANT>::type;
                array[0] = std::string(Core::TemplateTypeAsString<index_type>());
            }
        };

        std::array<std::string, variant_size> array;

        variant_options()
        {
            variant_option<variant_size - 1>::set(array);
        }
    };

    template <typename VARIANT>
    struct variant_swapper
    {
        static constexpr size_t variant_size = std::variant_size_v<VARIANT>;

        template <int INDEX>
        struct varaint_creator
        {
            static void create(VARIANT& variant, size_t index)
            {
                using index_type = std::variant_alternative<INDEX, VARIANT>::type;
                if (INDEX == index)
                {
                    variant = index_type();
                    return;
                }

                varaint_creator<INDEX - 1>::create(variant, index);
            }
        };
        
        template <>
        struct varaint_creator<0>
        {
            static void create(VARIANT& variant, size_t index)
            {
                using index_type = std::variant_alternative<0, VARIANT>::type;
                if (0 == index)
                {
                    variant = index_type();
                    return;
                }

                throw; // invalid index provided
            }
        };

        void create_variant_for_index(VARIANT& variant, size_t index)
        {
            varaint_creator<variant_size - 1>::create(variant, index);
        }
    };

    template <typename VARIANT, int INDEX>
    struct variant_ui_creator_by_index
    {
        static void CreateForIndex(VARIANT& variant, int index, const std::string& text = "", const std::string& id = "")
        {
            if (index == INDEX)
            {
                using used_alternative = std::variant_alternative<INDEX, VARIANT>::type;
                used_alternative& usedValue = std::get<INDEX>(variant);

                ui_creator<used_alternative>().CreateUI(usedValue, text, id);
                return;
            }
            
            return variant_ui_creator_by_index<VARIANT, INDEX - 1>::CreateForIndex(variant, index);
        }
    };

    template <typename VARIANT>
    struct variant_ui_creator_by_index<VARIANT, 0>
    {
        static void CreateForIndex(VARIANT& variant, int index, const std::string& text = "", const std::string& id = "")
        {
            if (index == 0)
            {
                using used_alternative = std::variant_alternative<0, VARIANT>::type;
                used_alternative& usedValue = std::get<0>(variant);

                ui_creator<used_alternative>().CreateUI(usedValue, text, id);
                return;
            }
            
            throw;
        }
    };

    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {
        // these two could be static, but has issues with the memory tracker (they are freed last)
        variant_options<Object> options;
        variant_swapper<Object> swapper;

        ImGuiComboFlags flags = ImGuiComboFlags_PopupAlignLeft;
        const std::string& currentType = options.array[data.index()];

        const std::string selectString = IMGUITag("select", id);
        if (ImGui::BeginCombo(selectString.c_str(), currentType.c_str(), flags))
        {
            size_t index = 0;
            for (const auto& type : options.array)
            {
                const bool is_selected = (type == currentType);
                if (ImGui::Selectable(type.c_str(), is_selected) && !is_selected)
                {
                    swapper.create_variant_for_index(data, index);
                }

                // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                if (is_selected)
                {
                    ImGui::SetItemDefaultFocus();
                }
                ++index;
            }
            ImGui::EndCombo();
        }

        variant_ui_creator_by_index<Object, std::variant_size_v<Object> - 1>::CreateForIndex(data, data.index(), text, id);
    }
};

template <typename Object>
struct ui_creator<Object, typename std::enable_if<is_specialization_of<Object, std::pair>::value>::type> // if the object is a pair
{
    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {        
        // HACK: when using pairs in things like maps, the first element is const - and we cant have that
        typedef raw_type_t<decltype(std::declval<Object>().first)> first_type;
        ui_creator<first_type>().CreateUI(const_cast<first_type&>(data.first, "first", id));
        ImGui::TEXT(" : ");
        ui_creator<raw_type_t<decltype(std::declval<Object>().second)>>().CreateUI(data.second, "second", id);
    }
};

template <typename Object>
struct ui_creator<Object, typename std::enable_if<is_specialization_of<Object, std::tuple>::value>::type> // if the object is a tuple
{
    template <int INDEX>
    struct tuple_index_ui_creator
    {
        static void CreateUI(const Object& tuple, const std::string& text = "", const std::string& id = "")
        {
            ui_creator<raw_type_t<std::tuple_element<INDEX, Object>>>().CreateUI(std::get<INDEX>(tuple, text, id));
            tuple_index_ui_creator<INDEX - 1>::CreateUI(tuple, text, id);
        }
    };

    template <>
    struct tuple_index_ui_creator<0>
    {
        static void CreateUI(const Object& tuple, const std::string& text = "", const std::string& id = "")
        {
            ui_creator<raw_type_t<std::tuple_element<0, Object>>>().CreateUI(std::get<0>(tuple), text, id);
        }
    };

    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {
        tuple_index_writer<std::tuple_size<Object> - 1>::CreateUI(data, text, id);
    }
};

// object type writer
template<typename Object>
struct ui_creator<Object, std::void_t<std::enable_if_t<is_visitable<Object>::value>>>
{
    struct field_ui_creator
    {
        field_ui_creator(const std::string id)
        : _id(id)
        {}

        template<typename FieldData>
        void operator()(FieldData f)
        {
            ui_creator<raw_type_t<decltype(f.get())>>().CreateUI(f.get(), f.name(), _id);
        }

    private:
        const std::string _id;
    };

    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {
        reflector::visit_all(data, field_ui_creator(id));
    }
};

// iterable type writer
template<typename Object>
struct ui_creator<Object, std::void_t<typename std::enable_if<is_iterable<Object>::value && !(std::is_same<raw_type_t<Object>, std::string>::value)>::type>>
{
    // better way to verify we can iterate over object: http://www.shital.com/p/writing-generic-container-function-in-c11/
    // may also want to reference https://en.cppreference.com/w/cpp/named_req/SequenceContainer
    void CreateUI(Object& data, const std::string& text = "", const std::string& id = "")
    {
        if (ImGui::TreeNode("Trees"))
        {
            for (auto &elem : data) {
                ui_creator<raw_type_t<decltype(*(std::declval<Object>().begin()))>>().CreateUI(elem, text, id);
            }
        }
        ImGui::TreePop();
    }
};
}// namespace Editor::UI