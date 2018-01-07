#pragma once

#include <cstdlib>
#include <utility>
#include <type_traits>

namespace Core
{
	template <typename T>
	constexpr decltype(auto) Forward(std::remove_reference_t<T>&& t) noexcept
	{
		return std::forward<T>(t);
	}

	template <typename T>
	constexpr decltype(auto) Forward(std::remove_reference_t<T>& t) noexcept
	{
		return std::forward<T>(t);
	}

	/*
	// in C++17
	template <typename T>
	using Not = std::negation<T>;

	template <typename ...Ts>
	using And = std::conjunction<Ts...>;

	template <typename ...Ts>
	using Or = std::disjunction<Ts...>;
	*/

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
}