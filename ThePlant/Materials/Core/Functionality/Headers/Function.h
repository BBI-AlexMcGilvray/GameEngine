#pragma once

#include <functional>

using namespace std;

namespace Core {
namespace Functionality {
  // NOTE: Leaving this here as example of implementation, but removing in favour of using std::function
  /*// typename T should not be defined there - need to make the type 'T' generic to allow lambdas (and possibly other things?)
  template<typename rT, typename... Ts>
  struct Function
  {
    struct FunctionImplBase
    {
      virtual rT operator()(Ts... args) = 0;
    };

    template<typename O>
    struct FunctionImpl : FunctionImplBase
    {
      O Object;

      FunctionImpl(O object)
        : Object(move(object))
      {}

      rT operator()(Ts... args)
      {
        return Object(args...);
      }
    };

    SharedPtr<FunctionImplBase> FunctionObject = nullptr;

    Function() = default;

    template<typename O>
    Function(O object)
    {
      FunctionObject = MakeShared<FunctionImpl<O>>(object);
    }

    Function(Function &&function)
    {
      FunctionObject = move(function.FunctionObject);
      function.FunctionObject = nullptr;
    }

    // NOTE: We currently need this to allow use with the std::vector since it requires copy-construction
    // https://en.cppreference.com/w/cpp/container/vector
    // Once we implement our own list we can get rid of this (and not have the FunctionObject be a SharedPtr - since that is terrible)
    Function(const Function &function)
    {
      // do we want it to be set up like this? I don't think so
      FunctionObject = function.FunctionObject;
    }

    ~Function()
    {
    }

    rT Call(Ts... args)
    {
      return (*this)(args...);
    }

    operator bool()
    {
      return (FunctionObject != nullptr);
    }

    // NOTE: We currently need this to allow use with the std::vector since it requires copy-construction
    // https://en.cppreference.com/w/cpp/container/vector
    // Once we implement our own list we can get rid of this (and not have the FunctionObject be a SharedPtr - since that is terrible)
    Function &operator=(const Function &function)
    {
      FunctionObject = function.FunctionObject;

      return (*this);
    }

    Function &operator=(Function &&function)
    {
      FunctionObject = move(function.FunctionObject);

      return (*this);
    }

    rT operator()(Ts... args)
    {
      return (*FunctionObject)(args...);
    }
  };
  */

  /*	TYPE DEFS	*/
  template<typename... Ts>
  using BoolFunction = std::function<bool(Ts...)>;

  template<typename... Ts>
  using VoidFunction = std::function<void(Ts...)>;
}// namespace Functionality
}// namespace Core