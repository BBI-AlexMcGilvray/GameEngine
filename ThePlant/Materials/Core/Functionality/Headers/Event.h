#pragma once

#include "Core/Logging/LogFunctions.h"
#include "Core/Functionality/Headers/Function.h"
#include "Core/Headers/PtrDefs.h"

namespace Core {
namespace Functionality {
/*
* NOTE: Rewrite this whole thing to use the 'new' Delegate type in Delegate.h
*     * plus, you know, this is all probably terrible
*/

  template<typename... Ts>
  struct EventDelegate
  {    
    EventDelegate(EventDelegate&&) = delete;
    EventDelegate& operator=(const EventDelegate&) = delete;
    EventDelegate& operator=(EventDelegate&&) = delete;

    virtual ~EventDelegate()
    {
      Remove();
    }

    virtual void Add(Ptr<EventDelegate<Ts...>> node)
    {
      if (node == nullptr) {
        return;
      }

      // can only be in on EventDelegate linked list at a time
      node->Remove();

      if (_next != nullptr) {
        _next->_previous = node;
      }

      node->_previous = this;
      node->_next = _next;

      _next = node;
    }

    virtual void Remove()
    {
      if (_previous != nullptr) {
        _previous->_next = _next;
      }
      if (_next != nullptr) {
        if (_previous == nullptr) {
          DEBUG_LOG("EVENT", "Removing an event where all delegates were not removed!");
        }
        else
        {
          _next->_previous = _previous;
        }
      }
      _next = nullptr;
      _previous = nullptr;
    }

    virtual void RemoveNode(EventDelegate<Ts...> &node)
    {
      return RemoveNode(&node);
    }

    virtual void RemoveNode(Ptr<EventDelegate<Ts...>> node)
    {
      Ptr<EventDelegate<Ts...>> currentNode = _next;

      while (currentNode != node) {
        if (currentNode == nullptr) {
          return;
        }

        currentNode = currentNode->_next;
      }

      currentNode->Remove();
    }

    void operator()(Ts &&...args)
    {
      _CallFunction(std::forward<Ts>(args)...);
    }

    void operator+=(EventDelegate<Ts...> &node)
    {
      Add(&node);
    }

    void operator+=(Ptr<EventDelegate<Ts...>> node)
    {
      Add(node);
    }

    void operator-=(EventDelegate<Ts...> &node)
    {
      RemoveNode(node);
    }

    void operator-=(Ptr<EventDelegate<Ts...>> node)
    {
      RemoveNode(node);
    }

    friend void operator+(EventDelegate<Ts...> &cNode, Ptr<EventDelegate<Ts...>> node)
    {
      return (cNode += node);
    }

    friend void operator-(EventDelegate<Ts...> &cNode, Ptr<EventDelegate<Ts...>> node)
    {
      return (cNode -= node);
    }

    Ptr<EventDelegate<Ts...>> GetNext() { return _next; } // to fix the fact that EventDelegate can't just directly reference the 'next' member variable for some reason

  protected:
    Ptr<EventDelegate<Ts...>> _previous = nullptr;
    Ptr<EventDelegate<Ts...>> _next = nullptr;

    EventDelegate(EventDelegate<Ts...>& previous)
    : EventDelegate(&previous)
    {}

    EventDelegate(Ptr<EventDelegate<Ts...>> previous = nullptr)
    {
      if (previous != nullptr) {
        previous->Add(this);
      }
    }

  private:
    virtual void _CallFunction(Ts &&...args) = 0;
  };

  // EVENT
  template<typename... Ts>
  struct Event : public EventDelegate<Ts...>
  {
    Event(const Event&) = delete;
    Event(Event&&) = delete;
    Event& operator=(const Event&) = delete;
    Event& operator=(Event&&) = delete;

    Event() = default;

    ~Event()
    {
      while (_next != nullptr) {
        _next->Remove();
      }
    }

    operator bool()
    {
      return (_next != nullptr);
    }

  private:
    void _CallFunction(Ts &&...args) override
    {
      Ptr<EventDelegate<Ts...>> next = _next;
      while (next != nullptr) {
        (*next)(std::forward<Ts>(args)...);
        next = next->GetNext();
      }
    }
  };

  // DELEGATE
  template<typename... Ts>
  struct Delegate : public EventDelegate<Ts...>
  {
    Delegate(const Delegate&) = delete;
    Delegate(Delegate&&) = delete;
    Delegate& operator=(const Delegate&) = delete;
    Delegate& operator=(Delegate&&) = delete;

    Delegate()
      : EventDelegate(nullptr)
    {}

    template<typename O>
    Delegate(O object, Event<Ts...> &event)
      : Delegate(BoolFunction<Ts...>(object), event)
    {}

    template<typename O>
    Delegate(O object)
      : Delegate(BoolFunction<Ts...>(object))
    {}

    Delegate(BoolFunction<Ts...> &&function, Event<Ts...> &event)
      : EventDelegate<Ts...>(&event), _function(function)
    {}

    Delegate(BoolFunction<Ts...> &&function)
      : _function(function)
    {}

    Delegate &operator=(BoolFunction<Ts...> &function)
    {
      _function = function;

      return (*this);
    }

    Delegate &operator=(BoolFunction<Ts...> &&function)
    {
      _function = function;

      return (*this);
    }

  private:
    BoolFunction<Ts...> _function;

    void _CallFunction(Ts &&...args) override
    {
      if (!_function || _function(Forward<Ts>(args)...)) {
        Remove();
      }
    }
  };
}// namespace Functionality
}// namespace Core