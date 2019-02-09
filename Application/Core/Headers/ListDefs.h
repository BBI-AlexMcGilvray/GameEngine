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

	template <typename T, typename std::size_t N>
	using Array = std::array<T, N>;

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
	void Pop(List<T>& list)
	{
		list.pop_back();
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
	void Push(List<T>& list, List<T> subList)
	{
		for (size i = 0; i < subList.size(); i++)
		{
			Push(list, subList[i]);
		}
	}

	template <typename T>
	Truth<size> InList(const List<T>& list, T entry)
	{
		auto index = std::find(list.begin(), list.end(), entry);
		
		if (index == list.end())
		{
			return Truth<size>(false, 0);
		}

		return Truth<size>(true, (index - list.begin()));
	}

	template <typename T, typename ...Ts>
	List<Truth<uint64>> InList(const List<T>& list, T entry, Ts... otherEntries)
	{
		List<Trust<uint64>> results;

		Push(results, InList(list, Forward<T>(entry)));
		
		Push(results, InList(list, Forward<Ts>(otherEntries)...));
		return results;
	}

	template <typename T>
	void Remove(List<T>& list, T entry)
	{
		if (auto truth = InList(list, Forward<T>(entry)))
		{
			list.erase(list.begin() + truth.Value);
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
	void RemoveIndex(List<T>& list, size index)
	{
		list.erase(list.begin() + index);
	}

	template <typename T, typename ...Ts>
	void RemoveIndex(List<T>& list, size index, Ts... otherIndices)
	{
		RemoveIndex(list, index);
		RemoveIndex(list, otherIndices...);
	}

	template <typename T>
	void RemoveIndex(List<T>& list, List<int> indices)
	{
		if (indices.size() > 0)
		{
			int currentIndex = indices[0];

			for (auto& index : indices)
			{
				if (index != 0 && index < currentIndex)
				{
					index -= 1;
				}
			}

			RemoveIndex(list, currentIndex);
			indices.erase(indices.begin());

			if (indices.size() > 0)
			{
				RemoveIndex(list, indices);
			}
		}
	}
}