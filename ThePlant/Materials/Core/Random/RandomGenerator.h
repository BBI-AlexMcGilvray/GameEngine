#pragma once

#include <cstddef>
#include <cstdint>

// Reasons std rand is garbage:
/*
    - https://codeforces.com/blog/entry/61587
    - https://codingnest.com/generating-random-numbers-using-c-standard-library-the-problems/
*/

// Alternative options:
/*
    - https://codingnest.com/generating-random-numbers-using-c-standard-library-the-solutions/
    - https://www.gormanalysis.com/blog/random-numbers-in-cpp/#distributions
*/

namespace Core {
class RandomGenerator
{// if ever needed, could use https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
public:
  RandomGenerator()
    : _seed(DEFAULT_SEED)
  {}

  RandomGenerator(uint32_t seed)
    : _seed(seed)
  {
    // _seed must not be zero or MODULO, or else all subsequent computed values
    // will be zero or MODULO respectively. For all other values, _seed will end
    if (_seed == 0 || _seed == MODULO) {
      _seed = DEFAULT_SEED;
    }
  }

  uint32_t Next()
  {
    // We are computing
    //       _seed = (_seed * MULTIPLIER) % MODULO
    //
    // _seed must not be zero or MODULO, or else all subsequent computed values
    // will be zero or MODULO respectively. For all other values, _seed will end
    // up cycling through every number in [1,MODULO-1]

    // we use uint64_t here to give us a larger period
    uint64_t product = _seed * MULTIPLIER;

    // Compute (product % MODULO) using the fact that ((x << 31) % MODULO) == x.
    _seed = static_cast<uint32_t>((product >> 31) + (product & MODULO));
    // The first reduction may overflow by 1 bit, so we may need to
    // repeat. mod == MODULO is not possible; using > allows the faster
    // sign-bit-based test.
    if (_seed > MODULO) {
      _seed -= MODULO;
    }
    return _seed;
  }

private:
  // you get a uniform distribution from 0 to n - 1 when (RAND_MAX % n) == (n - 1)
  // INT32_MAX + 1 is the highest n for which that is true for UINT64_MAX (which is the type we modulo), giving us the largest period
  // so we use INT32_MAX since we want to get numbers up to n - 1
  /*
            This is good enough for now, but our modulo being 1/2 our maximum value could theoretically be (UINT32_MAX) means that our maximum random
            value that could be generated is INT32_MAX
        */
  static constexpr uint32_t MODULO = INT32_MAX;// we need INT32_MAX because otherwise the (product & MODULO) is always 0 since MODULO will be all 0s in those bits
  static constexpr uint32_t MULTIPLIER = 16807;// bits 14, 8, 7, 5, 2, 1, 0
  static constexpr uint32_t DEFAULT_SEED = 1;

  uint32_t _seed;
};
}// namespace Core