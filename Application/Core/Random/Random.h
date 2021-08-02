#pragma once
#include "Core/Random/RandomGenerator.h"

namespace Core
{
    class Random
    {
    public:
        Random()
        {}
        
        Random(uint32_t seed)
        : _generator(seed)
        {}

        template <typename T>
        T Next()
        {
            return Next(T(0));
        }

    private:
        RandomGenerator _generator;

        uint32_t Next(uint32_t)
        {
            return _generator.Next();
        }

        // will always be greater than 0 because uints are always greater than 0, and the max uint generated in INT32_MAX
        int Next(int)
        {
            return int(Next<uint32_t>());
        }

        // double and float are between 0 and 1 because
        // a: our max value in RandomGenerator is INT32_MAX so we will never overflow into negative values
        // b: mod will not work
        // c: floating point errors will render larger values essentially useless
        //      - at best we could do max int / X (where X is MAX_UINT = X * MAX_FLOAT), but that is how we would get (worse) floating point errors

        // between 0 and 1
        double Next(double)
        {
            return double(Next<int>()) * (1.0 / double(INT32_MAX));
        }

        // between 0 and 1
        float Next(float)
        {
            return float(Next<double>());
        }

        bool Next(bool)
        {
            return (Next<uint32_t>() % 2 == 0);
        }
    };
}