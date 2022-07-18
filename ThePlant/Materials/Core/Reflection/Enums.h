#pragma once

#include "Core/Headers/Macros.h"
#include <exception>

namespace meta
{
  template<typename ENUM, ENUM... VALUES>
  struct enum_meta;

  template<typename ENUM>
  struct enum_meta<ENUM>
  {
    template<typename T>
    static bool constexpr is_value(T)
    {
      return false;
    }

    static ENUM constexpr at_index(int index)
    {
      throw std::out_of_range("index is bigger than the size of enum");
    }

    static int constexpr get_index(ENUM val)
    {
      throw std::bad_cast();
    }

    static int constexpr count() { return 0; }
  };

  template<typename ENUM, ENUM FIRST, ENUM... REST>
  struct enum_meta<ENUM, FIRST, REST...> : private enum_meta<ENUM, REST...>
  {
    using super = enum_meta<ENUM, REST...>;

    template<typename T>
    static bool constexpr is_value(T t)
    {
      return (FIRST == static_cast<ENUM>(t) || super::is_value(t));
    }

    static ENUM constexpr at_index(int index)
    {
      if (index == 0) {
        return FIRST;
      }

      return super::at_index(index - 1);
    }

    static int constexpr get_index(ENUM val)
    {
      if (val == FIRST) {
        return 0;
      }

      return 1 + super::get_index(val);
    }

    static int constexpr count()
    {
      return (1 + super::count());
    }
  };
}

#define SPLIT(X) (X),
#define COMMA(...) ,

#define NAME(X)      \
  OBSTRUCT(GET_NAME) \
  (SPLIT X)// 'NAME((A)(= 1))' into 'GET_NAME((A), (= 1))'
#define GET_NAME(X, Y) EXPAND X// 'GET_NAME((A), (= 1))' into 'A'
#define DEFINITION(X)      \
  OBSTRUCT(GET_DEFINITION) \
  (SPLIT X)// 'NAME((A)(= 1))' into 'GET_DEFINITION((A), (= 1))'
#define GET_DEFINITION(X, Y) EXPAND Y// 'GET_DEFINITION((A), (= 1))' into '= 1'

/*
// use example:
ENUM(MyEnum, int,
(A)(= 1),
(B)(<< 1));
// what is in the bracket is what would be used to set the value

// Notes:
Ideally 'meta_TYPE' is more well defined via some template, or having it pass into/specialize a containing templated struct.
This would allow a common interface to use namespaced types without users needing to _know_ that 'meta_TYPE' is a defined type
*/

// NOTE: Macro will currently only work with < 15 values! if more are needed, macros (Macros.h) will need to be udpates!
#define ENUM(TYPE, BASE, ...)                                                                                          \
  enum class TYPE : BASE {                                                                                             \
    FOR_EACH(ENUM_VALUE_INDIRECT, __VA_ARGS__)                                                                         \
  };                                                                                                                   \
  struct meta_ ## TYPE                                                                                                     \
  {                                                                                                                    \
    using meta_data = meta::enum_meta<TYPE, EVAL(REPEAT(VA_NUM_ARGS(__VA_ARGS__), ENUM_META_VALUE_INDIRECT, TYPE, __VA_ARGS__))>; \
                                                                                                                       \
    template<typename T>                                                                                               \
    static bool constexpr is_value(T t)                                                                                \
    {                                                                                                                  \
      return meta_data::is_value<T>(t);                                                                                     \
    }                                                                                                                  \
    static TYPE constexpr at_index(int index) { return meta_data::at_index(index); }                                        \
    static int constexpr get_index(TYPE val) { return meta_data::get_index(val); }                                          \
    static int constexpr count() { return meta_data::count(); }                                                             \
  };

#define ENUM_VALUE_INDIRECT(i, ...) \
  OBSTRUCT(ENUM_VALUE)              \
  (i, ARG_I(i, __VA_ARGS__))

#define ENUM_VALUE(i, VALUE)           \
  IF(i)                                \
  (OBSTRUCT(COMMA), OBSTRUCT(EMPTY))() \
    NAME(VALUE) DEFINITION(VALUE)

#define ENUM_META_VALUE_INDIRECT(i, TYPE, ...) \
  OBSTRUCT(ENUM_META_VALUE)                    \
  (i, TYPE, ARG_I(i, __VA_ARGS__))

#define ENUM_META_VALUE(i, TYPE, VALUE) \
  IF(i)                                 \
  (OBSTRUCT(COMMA), OBSTRUCT(EMPTY))()  \
    TYPE::OBSTRUCT(NAME)(VALUE)

#define STRING_CAST_ENUM(TYPE, BASE, ...)                                                   \
  ENUM(TYPE, BASE, __VA_ARGS__)                                                             \
  inline std::string to_string(TYPE type)                                                   \
  {                                                                                         \
    switch (type) {                                                                         \
      EVAL(REPEAT(VA_NUM_ARGS(__VA_ARGS__), ENUM_STRING_VALUE_INDIRECT, TYPE, __VA_ARGS__)) \
    default:                                                                                \
      return "INVALID";                                                                     \
    }                                                                                       \
  }/* to_string can be constexpr in std20+*/                                                \
  inline void from_string(const std::string& str, TYPE& toEnum)                             \
  {                                                                                         \
    EVAL(REPEAT(VA_NUM_ARGS(__VA_ARGS__), ENUM_FROM_STRING_INDIRECT, TYPE, __VA_ARGS__))    \
    throw; /* invalid string value - make this nicer */                                     \
  }

#define ENUM_STRING_VALUE_INDIRECT(i, TYPE, ...) \
  OBSTRUCT(ENUM_STRING_VALUE)                    \
  (i, TYPE, ARG_I(i, __VA_ARGS__))

#define ENUM_STRING_VALUE(i, TYPE, VALUE)          \
  case TYPE::NAME(VALUE): {                        \
    return OBSTRUCT(TO_STRING)(TYPE::NAME(VALUE)); \
  }

#define ENUM_FROM_STRING_INDIRECT(i, TYPE, ...)    \
  OBSTRUCT(ENUM_FROM_STRING)                       \
  (i, TYPE, ARG_I(i, __VA_ARGS__))                 

#define ENUM_FROM_STRING(i, TYPE, VALUE)           \
  if (OBSTRUCT(TO_STRING)(TYPE::NAME(VALUE)))      \
  {                                                \
    toEnum = TYPE::NAME(VALUE);                    \
    return;                                        \
  }