#pragma once

#include <functional>
#include <string>
#include <utility>

#include "Core/Headers/CoreDefs.h"
#include "Core/Headers/PtrDefs.h"
#include "Core/Headers/TemplateDefs.h"

// delete once working
#include <iostream>

namespace Core {
static const uint StartHashValue = 1431655765;// Bits: 01010101010101010101010101010101

struct Hash;

Hash AsHash(const uint& u);

Hash HashValue(const std::string& s);
void HashValue(const std::string& s, Hash &existingHash);

Hash HashValue(const char& b);
void HashValue(const char& b, Hash &existingHash);

template<typename T>
Hash HashValue(const T& type);
template<typename T>
void HashValue(const T& type, Hash &existingHash);

template <>
struct std::hash<Hash>;

std::string to_string(const Hash& hash);

/*
We will want a way to store the initial value used for the hash to be used for debugging purposes
*/
struct Hash
{
  static constexpr uint INITIAL_HASH_VALUE = 1431655765;// Bits: 01010101010101010101010101010101

  static const Hash VOID;

  friend Hash AsHash(const uint& u);

  friend Hash HashValue(const uint& u);
  friend void HashValue(const uint& u, Hash &existingHash);

  friend Hash HashValue(const std::string& s);
  friend void HashValue(const std::string& s, Hash &existingHash);

  friend Hash HashValue(const char& b);
  friend void HashValue(const char& b, Hash &existingHash);

  template<typename T>
  friend Hash HashValue(const T& type);
  template<typename T>
  friend void HashValue(const T& type, Hash &existingHash);

  friend struct std::hash<Hash>;

  friend std::string to_string(const Hash& hash);

  constexpr Hash()
    : _hash(INITIAL_HASH_VALUE)
  {}

  constexpr Hash(const Hash &h)
    : _hash(h._hash)
  {}

  Hash &operator=(const Hash &h)
  {
    _hash = h._hash;

    return (*this);
  }

  template<typename T>
  Hash &operator=(const T& t)
  {
    _hash = HashValue(t)._hash;

    return (*this);
  }

  Hash operator+(const Hash &h) = delete;
  template<typename T>
  Hash operator+(const T& t)
  {
    return HashValue(t, Hash(*this));
  }

  Hash& operator+=(const Hash& h) = delete;
  template <typename T>
  Hash& operator+=(const T& t)
  {
      HashValue(t, *this);

      return *this;
  }

  constexpr bool operator==(const Hash& other) const
  {
    return _hash == other._hash;
  }

  bool operator!=(const Hash& other) const
  {
    return !(*this == other);
  }

// if DEBUG? should maintain type-safety otherwise
  constexpr operator uint() const
  {
    return _hash;
  }

private:
  uint _hash;
};
inline const Hash Hash::VOID = Hash();

template<typename T>
Hash HashValue(const T& type)
{
  Hash newHash;

  HashValue(type, newHash);

  return newHash;
}

template<typename T>
void HashValue(const T& type, Hash &existingHash)
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

  inline std::string to_string(const Core::Hash& hash)
  {
    return std::to_string(hash._hash);
  }
}// namespace Core

template <>
struct std::hash<Core::Hash>
{
  std::size_t operator()(const Core::Hash& hash) const
  {
    return hash._hash;
  }
};
