#pragma once

#include <type_traits>

/*
* type traits should not be in namespaces (?)
*/

template<typename T>
struct raw_type
{
  using type = typename std::remove_reference<typename std::remove_cv<T>::type>::type;
};

template<typename T>
using raw_type_t = typename raw_type<T>::type;

/*
* make_const ensures that the given type T has the same const-ness as the type M
*/
template<typename M, typename T>
struct make_const
{
  typedef T type;
};

template<typename M, typename T>
struct make_const<const M, T>
{
  typedef typename std::add_const<T>::type type;
};

template<typename... Args>
constexpr std::size_t va_count(Args &&...)
{
  return sizeof...(Args);
}

template<typename T, int N>
struct visitable
{
  template<typename T2, int N2, typename = void>
  struct nested_type : std::false_type
  {
    using type = void;
  };

  template<typename T2, int N2>
  struct nested_type<T2, N2, std::void_t<typename T2::template field_data<N2, T2>>> : std::true_type
  {
    using type = typename T::template field_data<N, T>;
  };

  static constexpr bool value = nested_type<T, N>::value;
  using type = typename nested_type<T, N>::type;
};

template<typename T, int N>
using visitable_t = typename visitable<T, N>::type;

namespace details {
template<typename T>
struct fields_count_internal
{
  template<typename T2, typename = void>
  struct field_count
  {
    static constexpr int num_fields = 0;
  };

  template<typename T2>
  struct field_count<T2, std::void_t<decltype(T2::fields_n)>>
  {
    static constexpr int num_fields = T2::fields_n;
  };

  static constexpr int num_fields = field_count<T>::num_fields;
};
}// namespace details

template<typename T>
using is_visitable = visitable<T, details::fields_count_internal<T>::num_fields>;

// c++ 17 and up only
//template <typename T>
//inline constexpr bool is_visitable_v = is_visitable<T>::value;