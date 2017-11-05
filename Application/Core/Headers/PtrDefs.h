#pragma once

#include <memory>

namespace Core
{
	template <typename T>
	using Ptr = T*;

	template <typename T>
	using UniquePtr = std::unique_ptr<T>;

	template <typename T>
	using SharedPtr = std::shared_ptr<T>;

	template <typename T>
	using WeakPtr = std::weak_ptr<T>;

	template <typename T, typename ...Ts>
	SharedPtr<T> MakeShared(Ts&&... args)
	{
		return std::make_shared<T>(std::forward<Ts>(args)...);
	}

	template <typename T, typename ...Ts>
	UniquePtr<T> MakeUnique(Ts&&... args)
	{
		return std::make_unique<T>(std::forward<Ts>(args)...);
	}

	template <typename T>
	SharedPtr<T> ToShared(UniquePtr<T> uniquePtr)
	{
		return SharedPtr<T>(std::move(uniquePtr));
	}

	template <typename T>
	WeakPtr<T> ToWeak(SharedPtr<T> sharedPtr)
	{
		return WeakPtr<T>(sharedPtr);
	}
}