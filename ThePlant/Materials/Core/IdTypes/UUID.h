#pragma once

#include "Core/Random/Random.h"
#include <array>
#include <bitset>
#include <functional>
#include <sstream>
#include <string>

namespace Core {
// hex info: https://treehozz.com/how-many-bits-are-in-a-hex-digit
struct hex
{
  hex() = default;
  hex(const hex &other) = default;

  hex(uint32_t u)
  {
    _bits = u;
  }

  hex &operator=(const hex &other) = default;

  operator uint32_t() const
  {
    return _bits.to_ulong();
  }

private:
  std::bitset<4> _bits;
};

// for reference: https://thetopsites.net/article/58467162.shtml
class UUID
{
public:
  static UUID Generate()
  {
    UUID _generated;

    _generated._first = GenerateHexs<8>();
    _generated._second = GenerateHexs<4>();
    _generated._third = GenerateHexs<4>();
    _generated._fourth = GenerateHexs<4>();
    _generated._fifth = GenerateHexs<12>();

    return _generated;
  }

  UUID(const UUID &other)
  {
    _first = other._first;
    _second = other._second;
    _third = other._third;
    _fourth = other._fourth;
    _fifth = other._fifth;
  }

  UUID &operator=(const UUID &other)
  {
    _first = other._first;
    _second = other._second;
    _third = other._third;
    _fourth = other._fourth;
    _fifth = other._fifth;

    return *this;
  }

  std::string to_string()
  {
    std::stringstream ss;
    ss << std::hex;

    GenerateStringFromHexs<8>(ss, _first);
    ss << "-";
    GenerateStringFromHexs<4>(ss, _second);
    ss << "-";
    GenerateStringFromHexs<4>(ss, _third);
    ss << "-";
    GenerateStringFromHexs<4>(ss, _fourth);
    ss << "-";
    GenerateStringFromHexs<12>(ss, _fifth);

    return ss.str();
  }

private:
  static inline Random _generation;
  UUID() = default;

  std::array<hex, 8> _first;
  std::array<hex, 4> _second;
  std::array<hex, 4> _third;
  std::array<hex, 4> _fourth;
  std::array<hex, 12> _fifth;

  template<int N>
  static std::array<hex, N> GenerateHexs()
  {
    std::array<hex, N> result;

    for (uint32_t i = 0; i < N; i++) {
      result[i] = _generation.Next<uint32_t>();
    }

    return result;
  }

  template<int N>
  static void GenerateStringFromHexs(std::stringstream &ss, const std::array<hex, N> &hexs)
  {
    for (uint32_t i = 0; i < N; i++) {
      ss << uint32_t(hexs[i]);
    }
  }
};
}// namespace Core

// template <>
// struct std::hash<Core::UUID>
// {
//     std::size_t operator()(const Core::UUID& uuid) const
//     {
//         return static_cast<const uint32_t>(uuid); // not how this should get done
//     }
// };
