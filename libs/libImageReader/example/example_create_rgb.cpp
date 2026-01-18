#include <iostream>
#include <imageReader/imageCommon.h>
#include <imageReader/pixelView.h>
#include <imageReader/pixelConverter.h>


using namespace mylibImageReader;


void createGrayImage();
void createGray8Image();
void convertGray2RGB();
void workWithAlphaImage();



int main()
{
    ImageCommon img;

    img.width  = 4;
    img.height = 2;

    img.format = PixelFormat{
        ColorSpace::RGB,
        ChannelLayout::RGB,
        ChannelType::UInt,
        ChannelSize::Bit8,
        PixelPacking::None
    };

    // stride = width * bytesPerPixel
    img.strideBytes = img.width * img.format.bytesPerPixel();

    // allocate memory
    img.data.resize(img.sizeBytes());

    // fill image
    for (int y = 0; y < img.height; ++y)
    {
        for (int x = 0; x < img.width; ++x)
        {
            byte* pixelPtr =
                img.data.data() +
                y * img.stride() +
                x * img.format.bytesPerPixel();

            PixelView px(pixelPtr, img.format);

            px.channel(0).set(1.0);   // R = 255
            px.channel(1).set(0.5);   // G = 128
            px.channel(2).set(0.0);   // B = 0
        }
    }

    std::cout << "Image created and filled\n";
}



void createGrayImage()
{
    ImageCommon gray;

gray.width  = 3;
gray.height = 3;

gray.format = PixelFormat{
    ColorSpace::Gray,
    ChannelLayout::Y,
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

gray.data.resize(gray.sizeBytes());

// gradient
for (int y = 0; y < gray.height; ++y)
{
    for (int x = 0; x < gray.width; ++x)
    {
        gray.data[y * gray.stride() + x] =
            static_cast<byte>((x + y) * 255 / 4);
    }
}

}


void createGray8Image()
{
    ImageCommon gray;

gray.width  = 3;
gray.height = 3;

gray.format = PixelFormat{
    ColorSpace::Gray,
    ChannelLayout::Y,
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

gray.data.resize(gray.sizeBytes());

// gradient
for (int y = 0; y < gray.height; ++y)
{
    for (int x = 0; x < gray.width; ++x)
    {
        gray.data[y * gray.stride() + x] =
            static_cast<byte>((x + y) * 255 / 4);
    }
}

}

void convertGray2RGB()
{

 ImageCommon gray;

gray.width  = 3;
gray.height = 3;

gray.format = PixelFormat{
    ColorSpace::Gray,
    ChannelLayout::Y,
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

gray.data.resize(gray.sizeBytes());

// gradient
for (int y = 0; y < gray.height; ++y)
{
    for (int x = 0; x < gray.width; ++x)
    {
        gray.data[y * gray.stride() + x] =
            static_cast<byte>((x + y) * 255 / 4);
    }
}



    
ImageCommon rgb;

rgb.width  = gray.width;
rgb.height = gray.height;
rgb.format = {
    ColorSpace::RGB,
    ChannelLayout::RGB,
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

rgb.data.resize(rgb.sizeBytes());

bool ok = PixelConverter::convertImage(gray, rgb);
if (!ok)
{
    std::cerr << "Conversion failed\n";
}

}


void workWithAlphaImage()
{
ImageCommon rgba;

rgba.width = 2;
rgba.height = 2;

rgba.format = {
    ColorSpace::RGB,
    ChannelLayout::RGBA,
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

rgba.data.resize(rgba.sizeBytes());

for (int i = 0; i < 4; ++i)
{
    byte* p = rgba.data.data() + i * 4;
    PixelView px(p, rgba.format);

    px.channel(0).set(0.0); // R
    px.channel(1).set(1.0); // G
    px.channel(2).set(0.0); // B
    px.channel(3).set(1.0); // A = opaque
}



// -- read PixelView
PixelView px(rgba.data.data(), rgba.format);

double r = px.channel(0).get();
double g = px.channel(1).get();
double b = px.channel(2).get();
double a = px.alpha();  // всегда 1.0 если нет альфы

}