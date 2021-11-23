#pragma once

// reference: https://en.wikipedia.org/wiki/Perlin_noise

template <typename T>
T Perlin2D(const T& x, const T& y)
{
    int x0 = static_cast<int>(x);
    int x1 = x0 + 1;
    int y0 = static_cast<int>(y);
    int y1 = y0 + 1;

    float xWeight = static_cast<float>(x) - static_cast<float>(x0);
    float yWeight = static_cast<float>(y) - static_cast<float>(y0);

    float n0, n1, ix0, ix1, value;
}