#pragma once

#include "CoreDefs.h"
#include "PtrDefs.h"
#include "TemplateDefs.h"

// delete once working
#include <iostream>

namespace Core
{
	const uint StartHashValue = 1431655765; // Bits: 01010101010101010101010101010101

	struct Hash;

	// these may not be needed anymore since hashing function was improved with different shift value
	Hash HashValue(uint u);
	void HashValue(uint u, Hash& existingHash);

	Hash HashValue(String s);
	void HashValue(String s, Hash& existingHash);

	Hash HashValue(char b);
	void HashValue(char b, Hash& existingHash);

	template <typename T>
	Hash HashValue(T&& type);
	template <typename T>
	void HashValue(T&& type, Hash& existingHash);

	struct Hash
	{
		uint H;

		constexpr Hash()
			: H(StartHashValue)
		{}

		constexpr Hash(const Hash& h)
			: H(h.H)
		{}

		Hash& operator=(const Hash& h)
		{
			H = h.H;

			return (*this);
		}

		template <typename T>
		Hash& operator=(T&& t)
		{
			H = HashValue(Forward<T>(t), (*this));

			return (*this);
		}

		Hash& operator+(const Hash& h) = delete;

		template <typename T>
		Hash& operator+(T&& t)
		{
			HashValue(t, (*this));

			return (*this);
		}

		constexpr operator uint() const
		{
			return H;
		}
	};

	template <typename T>
	Hash HashValue(T&& type)
	{
		Hash newHash;

		HashValue(type, newHash);

		return newHash;
	}

	template <typename T>
	void HashValue(T&& type, Hash& existingHash)
	{
		int numBytes = sizeof(type);

		// this should be redone once serialization stuff is working
		Ptr<const char> typeBytes = reinterpret_cast<Ptr<const char>>(&type); // <- this is not being consistent

		for (int i = 0; i < numBytes; i++)
		{
			// pending the serialization stuff, maybe this works
			char byte = typeBytes[i];

			HashValue(byte, existingHash);
		}
	}

	/*
		POSSIBLE!!

		But would we ever need to deconstruct a hash?
		If we need to ensure a starting condition was used, just reconstruct the hash
	*/
	// char UnHashValue(Hash& currentHash, Hash& previousHash);

	/*
		NOT POSSIBLE!!
		
		Since we do not know the true 'previous hash'.
		
		We would need the hashing of the type to return the second last result from the hashing process
		(and unhash both ? ) as we go back, and 'bunny-hop' them to the final result).
	*/
	/*
	template <typename T>
	T UnHashValue(Hash& currentHash, Hash& previousHash)
	{
		T t = 0;

		int numBytes = sizeof(T);

		for (int i = numBytes; i > 0; i--)
		{
			Hash currentHashCopy = currentHash;
			char b = UnHashValue(currentHash, previousHash);
			T newType = b;
			t += (newType << (i * 8));
			previousHash = currentHashCopy;
		}

		return t;
	}
	*/
}
