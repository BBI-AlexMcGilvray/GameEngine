#pragma once

#include <algorithm>
#include <stdlib.h>
#include <vector>

#include "Core/Headers/TemplateDefs.h"
#include "Core/Headers/CoreDefs.h"

namespace Core
{
	template <typename T>
	using List = std::vector<T>;
	
	template <typename T>
	struct Truth
	{
		bool Result;
		T Value;

		Truth(bool result, T value)
			: Result(result), Value(value)
		{}

		operator bool()
		{
			return Result;
		}

		operator T&&()
		{
			return Value;
		}
	};

	template <typename T>
	void Sort(List<T>& list, int startIndex = 0)
	{
		Sort(list, startIndex, list.size());
	}

	template <typename T>
	void Sort(List<T>& list, int startIndex, int endIndex)
	{
		std::sort(list.begin() + startIndex, list.begin() + endIndex);
	}

	template <typename T>
	void Push(List<T>& list, T entry)
	{
		list.push_back(Forward<T>(entry));
	}

	template <typename T, typename ...Ts>
	void Push(List<T>& list, T entry, Ts... otherEntries)
	{
		Push(list, Forward<T>(entry));
		Push(list, Forward<Ts>(otherEntries)...);
	}

	template <typename T>
	Truth<uint> InList(const List<T>& list, T entry)
	{
		auto index = std::find(list.begin(), list.end(), entry);
		
		if (index != list.end())
		{
			return Truth<uint>(false, 0);
		}

		return Truth<uint>(true, (index - list.begin()));
	}

	template <typename T, typename ...Ts>
	List<Truth<uint>> InList(const List<T>& list, T entry, Ts... otherEntries)
	{
		List<Trust<uint>> results;

		Push(results, InList(list, Forward<T>(entry)));
		
		Push(results, InList(list, Forward<Ts>(otherEntries)...));
		return results;
	}

	template <typename T>
	void Remove(List<T>& list, T entry)
	{
		if (auto truth = InList(list, Forward<T>(entry)))
		{
			list.erase(list.begin() + truth);
		}
	}

	template <typename T, typename ...Ts>
	void Remove(List<T>& list, T entry, Ts... otherEntries)
	{
		if (Remove(list, Forward<T>(entry)))
		{
			Remove(list, Forward<Ts>(otherEntries)...);
		}
	}

	template <typename T>
	bool Remove(List<T>& list, List<T> objects)
	{
		Remove(list, objects[0]);
		objects.erase(objects.begin());

		if (objects.size() > 0)
		{
			Remove(list, objects);
		}
	}

	template <typename T>
	void Remove(List<T>& list, int index)
	{
		list.erase(list.begin() + index);
	}

	template <typename T, typename ...Ts>
	void Remove(List<T>& list, int index, Ts... otherIndices)
	{
		Remove(list, index);
		Remove(list, otherIndices...);
	}

	template <typename T>
	void Remove(List<T>& list, List<int> indices)
	{
		Remove(list, indices[0]);
		indices.erase(indices.begin());

		if (indices.size() > 0)
		{
			Remove(list, indices);
		}
	}
}