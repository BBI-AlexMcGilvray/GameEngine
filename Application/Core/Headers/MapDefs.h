#pragma once

#include <map>

#include "Core/Headers/ListDefs.h"

namespace Core
{
	template <typename Key, typename T>
	using Map = std::map<Key, T>;

	template <typename Key, typename T>
	void Insert(Map<Key, T>& map, Key&& key, T&& t)
	{
		Insert(map, Pair<Key, T>(Forward<Key>(key), Forward<T>(t)));
	}

	template <typename Key, typename T>
	void Insert(Map<Key, T>& map, Pair<Key, T> pair)
	{
		map.insert(pair);
	}

	template <typename Key, typename T>
	void Erase(Map<Key, T>& map, Key&& key)
	{
		map.erase(Forward<Key>(key));
	}

	template <typename Key, typename T>
	void Clear(Map<Key, T>& maap)
	{
		map.clear();
	}

	template <typename Key, typename T>
	bool Empty(Map<Key, T>& map)
	{
		return map.empty();
	}

	template <typename Key, typename T>
	bool In(Map<Key, T>& map, Key&& key)
	{
		auto iterator = map.find(Forward<Key>(key));

		return (iterator != map.end());
	}
}