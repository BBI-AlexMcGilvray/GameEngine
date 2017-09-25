#pragma once

#include <algorithm>
#include <cstdlib>
#include <stdlib.h>
#include <vector>
#include <utility>

namespace Core
{
	template <typename T>
	using List = std::vector<T>;
	
	template <typename T>
	struct Truth
	{
		bool Result;
		T Value;

		bool operator()
		{
			return Result;
		}

		T operator()
		{
			return Value;
		}
	};

	template <typename T>
	void Push(List<T> list, T entry)
	{
		list.push_back(entry);
	}

	template <typename T, typename ...Ts>
	void Push(List<T> list, T entry, Ts... otherEntries)
	{
		Push(list, entry);
		Push(list, std::forward<Ts>(otherEntries)...);
	}

	template <typename T>
	Truth<uint> InList(List<T> list, T entry)
	{
		auto index = std::find(list.begin(), list.end(), entry);
		
		if (index != list.end())
		{
			return Truth{ false, 0 };
		}

		return Truth{ true, index };
	}

	template <typename T, typename ...Ts>
	Truth<uint> InList(List<T> list, T entry, Ts... otherEntries)
	{
		if (InList(list, entry))
		{
			return InList(list, std::forward<Ts>(otherEntries)...);
		}

		return Truth{ false, 0 };
	}

	template <typename T>
	bool Remove(List<T> list, T entry)
	{
		if (auto truth = InList(list, entry))
		{
			list.erase(truth);
			return true;
		}

		return false;
	}

	template <typename T, typename ...Ts>
	bool Remove(List<T> list, T entry, Ts... otherEntries)
	{
		if (Remove(list, entry))
		{
			return Remove(list, std::forward<Ts>(otherEntries)...);
		}

		return false;
	}
};