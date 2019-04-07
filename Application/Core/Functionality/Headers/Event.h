#pragma once

#include "Core/Headers/AllCore.h"

#include "Function.h"

// testing
#include "Core/Debugging/Headers/Macros.h"

namespace Core
{
	namespace Functionality
	{
		template <typename ...Ts>
		struct DelegateNode
		{
			Ptr<DelegateNode<Ts...>> Previous = nullptr;
			Ptr<DelegateNode<Ts...>> Next = nullptr;

			DelegateNode(Ptr<DelegateNode<Ts...>> previous = nullptr)
			{
				if (previous != nullptr)
				{
					previous->Add(this);
				}
			}

			DelegateNode(DelegateNode<Ts...>& previous)
				: DelegateNode(&previous)
			{}

			virtual ~DelegateNode()
			{
				Remove();
			}

			virtual void Add(DelegateNode<Ts...>& node)
			{
				return Add(&node);
			}

			virtual void Add(Ptr<DelegateNode<Ts...>> node)
			{
				if (node == nullptr)
				{
					return;
				}

				// can only be in on DelegateNode linked list at a time
				node->Remove();

				if (Next != nullptr)
				{
					Next->Previous = node;
				}

				node->Previous = this;
				node->Next = Next;

				Next = node;
			}

			virtual void Remove()
			{
				if (Previous != nullptr)
				{
					Previous->Next = Next;
				}
				if (Next != nullptr)
				{
#if _DEBUG
					if (Previous == nullptr)
					{
						LOG("Removing an event where all delegates were not removed!");
					}
					else
#endif
					{
						Next->Previous = Previous;
					}
				}
				Next = nullptr;
				Previous = nullptr;
			}

			virtual void RemoveNode(DelegateNode<Ts...>& node)
			{
				return RemoveNode(&node);
			}

			virtual void RemoveNode(Ptr<DelegateNode<Ts...>> node)
			{
				Ptr<DelegateNode<Ts...>> currentNode = Next;

				while (currentNode != node)
				{
					if (currentNode == nullptr)
					{
						return;
					}

					currentNode = currentNode->Next;
				}

				currentNode->Remove();
			}

			void operator ()(Ts&& ...args)
			{
				CallFunction(Forward<Ts>(args)...);
			}

			void operator +=(DelegateNode<Ts...>& node)
			{
				Add(node);
			}

			void operator +=(Ptr<DelegateNode<Ts...>> node)
			{
				Add(node);
			}

			void operator -=(DelegateNode<Ts...>& node)
			{
				RemoveNode(node);
			}

			void operator -=(Ptr<DelegateNode<Ts...>> node)
			{
				RemoveNode(node);
			}

			friend void operator +(DelegateNode<Ts...>& cNode, Ptr<DelegateNode<Ts...>> node)
			{
				return (cNode += node);
			}

			friend void operator -(DelegateNode<Ts...>& cNode, Ptr<DelegateNode<Ts...>> node)
			{
				return (cNode -= node);
			}

		private:
			virtual void CallFunction(Ts&& ...args) = 0;
		};

// EVENT
		template <typename ...Ts>
		struct EventNode : DelegateNode<Ts...>
		{
			EventNode() = default;

			~EventNode()
			{
				while (Next != nullptr)
				{
					Next->Remove();
				}
			}

			operator bool()
			{
				return (Next != nullptr);
			}

		private:
			void CallFunction(Ts&& ...args) override
			{
				auto next = Next;
				while (next != nullptr)
				{
					auto currentNode = next;
					next = currentNode->Next;

					(*currentNode)(Forward<Ts>(args)...);
				}
			}
		};
		
// DELEGATE
		template <typename ...Ts>
		struct Delegate : DelegateNode<Ts...>
		{
			Delegate()
				: DelegateNode(nullptr)
			{}

			template <typename O>
			Delegate(O object, DelegateNode<Ts...>& parentEvent)
				: Delegate(Function<bool, Ts...>(object), parentEvent)
			{}

			template <typename O>
			Delegate(O object)
				: Delegate(Function<bool, Ts...>(object))
			{}

			Delegate(Function<bool, Ts...>&& function, DelegateNode<Ts...>& parentEvent)
				: DelegateNode<Ts...>(&parentEvent)
				, DelegateFunction(function)
			{}

			Delegate(Function<bool, Ts...>&& function)
				: DelegateFunction(function)
			{}

			Delegate& operator= (Function<bool, Ts...>& function)
			{
				DelegateFunction = function;

				return (*this);
			}

			Delegate& operator= (Function<bool, Ts...>&& function)
			{
				DelegateFunction = function;

				return (*this);
			}

			void CallFunction(Ts&& ...args) override
			{
				if (!DelegateFunction || DelegateFunction(Forward<Ts>(args)...))
				{
					Remove();
				}
			}

		private:
			Function<bool, Ts...> DelegateFunction;
		};

		template <typename ...Ts>
		using Event = EventNode<Ts...>;
	}
}