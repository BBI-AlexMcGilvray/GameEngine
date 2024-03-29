#pragma once

#include "Core/Headers/Macros.h"
#include "Core/Reflection/type_traits.h"
#include <cstddef>
#include <functional>
#include <iostream>
#include <stdio.h>
#include <string>

// Reference: https://stackoverflow.com/questions/1559254/are-there-binary-memory-streams-in-c
#define REFLECTABLE(...)                                    \
  static constexpr int fields_n = VA_NUM_ARGS(__VA_ARGS__); \
  template<typename T>                                      \
  friend struct details::fields_count_internal;             \
  template<typename T, int N>                               \
  friend struct visitable;                                  \
  friend struct reflector;                                  \
  template<int N, class Self>                               \
  struct field_data                                         \
  {                                                         \
  };                                                        \
  FOR_EACH(REFLECT_EACH_INDIRECT, __VA_ARGS__)

#define REFLECT_EACH_INDIRECT(i, ...) \
  OBSTRUCT(REFLECT_EACH)              \
  (i, ARG_I(i, __VA_ARGS__))

#define REFLECT_EACH(i, x)                            \
  PAIR(x);                                            \
  template<class Self>                                \
  struct field_data<i, Self>                          \
  {                                                   \
    Self &self;                                       \
    field_data(Self &self) : self(self) {}            \
    /* this will return a const reference if Self is const */  \
    typename make_const<Self, TYPEOF(x)>::type &get() \
    {                                                 \
      return self.STRIP(x);                           \
    }                                                 \
    typename std::add_const<TYPEOF(x)>::type &get() const  \
    {                                                 \
      return self.STRIP(x);                           \
    }                                                 \
    void set(std::add_const<TYPEOF(x)>::type &val)         \
    {                                                 \
      self.STRIP(x) = val;                            \
    }                                                 \
    const char *name() const                          \
    {                                                 \
      return OBSTRUCT(TO_STRING)(STRIP(x));           \
    }                                                 \
    int index() const                                 \
    {                                                 \
      return i;                                       \
    }                                                 \
  };

// explicit implementation for this macro so that fields_n is 0, and there is nothing _actually_ reflectable
#define NOTHING_REFLECTABLE()                         \
  static constexpr int fields_n = 0;                  \
  template<typename T>                                \
  friend struct details::fields_count_internal;       \
  template<typename T, int N>                         \
  friend struct visitable;                            \
  friend struct reflector;                            \
  template<int N, class Self>                         \
  struct field_data                                   \
  {                                                   \
  };

struct reflector
{
  // Get the number of fields
  template<typename T>
  static constexpr int num_fields = T::fields_n;

  //Get field_data at index N
  template<int N, class T>
  static typename T::template field_data<N, T> get_field_data(T &x)
  {
    return typename T::template field_data<N, T>(x);
  }

  template<int N, class C, class Visitor>
  static void visit_field(C &c, Visitor v)
  {
    v(reflector::get_field_data<N>(c));
  }

  template<int N, class C, class Visitor>
  struct visit_each
  {
    static void apply(C &c, Visitor v)
    {
      visit_field<N>(c, v);
      visit_each<N - 1, C, Visitor>::apply(c, v);
    }
  };

  template<class C, class Visitor>
  struct visit_each<0, C, Visitor>
  {
    static void apply(C &c, Visitor v)
    {
      visit_field<0>(c, v);
    }
  };

  template<class C, class Visitor>
  struct visit_each<-1, C, Visitor>
  {
    static void apply(C& c, Visitor v)
    {
      return; // -1 implies the number of fields was 0, so there is nothing to visit
    }
  };

  // should Visitor be a reference (and passed along as a reference?)
  template<class C, class Visitor>
  static void visit_all(C &c, Visitor v)
  {
    visit_each<reflector::num_fields<C> - 1, C, Visitor>::apply(c, v);
  }
};

struct print_visitor
{
  template<class FieldData>
  void operator()(FieldData f)
  {
    std::cout << f.index() << ": " << f.name() << " = " << f.get() << '\n';
  }
};

template<class T>
void print_fields(T &x)
{
  reflector::visit_all(x, print_visitor());
}