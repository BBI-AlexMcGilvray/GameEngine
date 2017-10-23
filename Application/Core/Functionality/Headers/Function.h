#pragma once

#include "Core/Headers/TemplateDefs.h"

namespace Core
{
	namespace Functionality
	{
		template <typename rT, typename T, typename ...Ts>
		struct FunctionBase
		{
			FunctionBase(T action)
				: Action(action)
			{}

			rT operator()(Ts&&... args)
			{
				return Action(Forward<Ts>(args)...);
			}

		private:
			T Action;
		};

		/*
		Not using the below because there is likely no need, and the method in which I was using this (having a base class with overloaded () operator) does not work
		but I did not know enough about templates at the time of conception

		Leaving it here incase it becomes useful

		template <typename rT, typename T, typename ...Ts>
		struct MemberFunction
		{
			using F = rT(T::*)(Ts...);
			MemberFunction(T& object, F action)
				: Object(object), Action(action)
			{}

			bool HoldsObject(T const& otherObject) const
			{
				return (otherObject == Object);
			}

			template <typename oT> // used if (oT != T)
			bool HoldsObject(oT const& otherObject) const
			{
				return false;
			}

			bool operator()(Ts&&... args)
			{
				return (Object.(*Action))(Forward<Ts>(args)...);
			}

		private:
			T& Object;
			F Action;
		};
		*/

		/*	TYPE DEFS	*/
		template <typename T, typename ...Ts>
		using Function = FunctionBase<bool, T,Ts...>;

		/*
			Not using the below because there is likely no need, and the method in which I was using this (having a base class with overloaded () operator) does not work
			but I did not know enough about templates at the time of conception

			Leaving it here incase it becomes useful
		
		template <typename T, typename ...Ts>
		using MemberFunction_Bool = MemberFunction<bool, T, Ts...>;
		*/
	}
}