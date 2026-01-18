#include <imageReader/GammaLUT.h>
#include <cmath>
#include <algorithm>

namespace mylibImageReader
{

double GammaLUT::srgbToLinear(double v)
{
    if (v <= 0.04045)
        return v / 12.92;
    return std::pow((v + 0.055) / 1.055, 2.4);
}

double GammaLUT::linearToSrgb(double v)
{
    if (v <= 0.0031308)
        return v * 12.92;
    return 1.055 * std::pow(v, 1.0 / 2.4) - 0.055;
}

std::vector<double> GammaLUT::buildGamma(double gamma, size_t size)
{
    std::vector<double> lut(size);
    for (size_t i = 0; i < size; ++i)
        lut[i] = std::pow(double(i) / (size - 1), gamma);
    return lut;
}

double GammaLUT::apply(const std::vector<double>& lut, double v)
{
    v = std::clamp(v, 0.0, 1.0);
    size_t idx = size_t(v * (lut.size() - 1));
    return lut[idx];
}

}
