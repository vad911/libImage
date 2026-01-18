#pragma once
#include <vector>
#include <cstddef>

namespace mylibImageReader
{

class GammaLUT
{
public:
    static double srgbToLinear(double v);
    static double linearToSrgb(double v);

    static std::vector<double> buildGamma(double gamma, size_t size = 256);
    static double apply(const std::vector<double>& lut, double v);
};

}
