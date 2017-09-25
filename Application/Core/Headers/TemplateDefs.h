#pragma once

#include <cstdlib>

namespace Core
{
	template <bool B, typename T = void>
	using EnableIf = std::enable_if<B, T>;

	template <typename T1, typename T2>
	using IsSame = std::is_same<T1, T2>;

	/* DOES NOT WORK (can we get it to?)
	template <typename T1, typename ...Ts>
	using AllSame = IsSame<T1, Ts...>;
	*/

	template <typename T1, typename T2>
	using IsBaseOf = std::is_base_of<T1, T2>;

	template <typename T1, typename T2> 
	using EqualToValue = typename EnableIf<IsSame<T1, T2>::value>;

	template <typename T1, typename T2>
	using EqualToType = typename EnableIf<IsSame<T1, T2>::type>;
};