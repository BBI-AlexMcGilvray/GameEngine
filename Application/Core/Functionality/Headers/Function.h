#pragma once

namespace Functionality
{
	template <typename rT, typename Ts...>
	struct FunctionBase
	{
		virtual FunctionBase() = default;

		rT operator()(Ts... args) = 0;
	};

	template <typename rT, typname T, typename Ts...>
	struct Function
	{
		Function(T function)
			: function(function)
		{}

		rT operator()(Ts... args)
		{
			return function(Ts...);
		}
		
	private:
		T function;
	};

	template <typename rT, typename T, typename Ts...>
	struct MemberFunction<T, Ts...> : FunctionBase<rT, Ts...>
	{
		using rT(T::* F)(Ts...);
		MemberFunction(T& object, F function)
			: Object(object), Function(function)
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

		bool operator()(Ts... args)
		{
			return (Object.(*Function))(std::forward<Ts>(args)...);
		}

	private:
		T& Object;
		F Function;
	};

	/*	TYPE DEFS	*/
	template <typename T, typename Ts...>
	using MemberFunction_Bool = MemberFunction<bool, T, Ts...>;
};