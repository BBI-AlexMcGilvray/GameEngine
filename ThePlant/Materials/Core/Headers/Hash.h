#pragma once

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TemplateDefs.h"

// delete once working
#include <iostream>

namespace Core {
static const uint StartHashValue = 1431655765;// Bits: 01010101010101010101010101010101

struct Hash;

// these may not be needed anymore since hashing function was improved with different shift value
Hash HashValue(uint u);
void HashValue(uint u, Hash &existingHash);

Hash HashValue(String s);
void HashValue(String s, Hash &existingHash);

Hash HashValue(char b);
void HashValue(char b, Hash &existingHash);

template<typename T>
Hash HashValue(T &&type);
template<typename T>
void HashValue(T &&type, Hash &existingHash);

struct Hash
{
  static const Hash VOID;

  friend Hash HashValue(uint u);
  friend void HashValue(uint u, Hash &existingHash);

  friend Hash HashValue(String s);
  friend void HashValue(String s, Hash &existingHash);

  friend Hash HashValue(char b);
  friend void HashValue(char b, Hash &existingHash);

  template<typename T>
  friend Hash HashValue(T &&type);
  template<typename T>
  friend void HashValue(T &&type, Hash &existingHash);

  constexpr Hash()
    : _hash(StartHashValue)
  {}

// remove constructors from uint? should always create from hash or explicit hashing function
  constexpr Hash(const uint &u)
    : _hash(u)
  {}

  constexpr Hash(const Hash &h)
    : _hash(h._hash)
  {}

  Hash &operator=(const uint &u)
  {
    _hash = u;

    return (*this);
  }

  Hash &operator=(const Hash &h)
  {
    _hash = h._hash;

    return (*this);
  }

  template<typename T>
  Hash &operator=(T &&t)
  {
    _hash = HashValue(Forward<T>(t));

    return (*this);
  }

  Hash &operator+(const Hash &h) = delete;

  template<typename T>
  Hash &operator+(T &&t)
  {
    HashValue(t, (*this));

    return (*this);
  }

// if _DEBUG? should maintain type-safety otherwise
  constexpr operator uint() const
  {
    return _hash;
  }

private:
  uint _hash;
};

template<typename T>
Hash HashValue(T &&type)
{
  Hash newHash;

  HashValue(type, newHash);

  return newHash;
}

template<typename T>
void HashValue(T &&type, Hash &existingHash)
{
  size numBytes = sizeof(type);

  // this should be redone once serialization stuff is working
  Ptr<const char> typeBytes = reinterpret_cast<Ptr<const char>>(&type);// <- this is not being consistent

  for (size i = 0; i < numBytes; i++) {
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
}// namespace Core
