#pragma once
#include <coreImage/image.h>

namespace myCoreImage {
namespace transform {

COREIMAGE_API Image resize(const Image& src, std::size_t newWidth, std::size_t newHeight);
COREIMAGE_API Image rotate(const Image& src, double angleDegrees);

} // namespace transform
} // namespace myCoreImage
