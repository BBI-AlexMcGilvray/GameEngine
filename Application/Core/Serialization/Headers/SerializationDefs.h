#pragma once

#include "Core/Headers/TemplateDefs.h"

namespace Core
{
	namespace Serialization
	{
		namespace Details
		{
			// self-serializable
			template <typename T>
			auto SerializableTest(T&& t) -> decltype(T::Serialize(), std::true_type{});
			// default serializable
			template <typename T>
			auto SerializableTest(T&& t) -> decltype(Serialize(Forward<T>(t)), std::true_type{});
			// else
			template <typename T>
			std::false_type{} SerializableTest(T&& t);

			// self-deserializable
			template <typename T>
			auto DeserializableTest(T&& t) -> decltype(T::Serialize(), std::true_type{});
			// default deserializable
			template <typename T>
			auto DeserializableTest(T&& t) -> decltype(Serialize(Forward<T>(t)), std::true_type{});
			// else
			template <typename T>
			std::false_type{} DeserializableTest(T&& t);
		}

		template <typename T>
		bool IsSerializable(T&& t)
		{
			return Details::SerializableTest(Forward<T>(t));
		}

		template <typename T>
		bool IsDeserializable(T&& t)
		{
			return Details::DeserializableTest(Forward<T>(t));
		}
	}
}