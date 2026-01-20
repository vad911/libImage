#include <iostream>
#include <cstring>  // -- для memcpy

#include <imageReader/imageCommon.h>
#include <imageReader/pixelView.h>
#include <imageReader/pixelConverter.h>
#include <thread>


using namespace mylibImageReader;


void createGrayImage();
void createGray8Image();
void convertGray2RGB();

void* bmpRowPtr(int row);  // -- возвращает указатель на нужную строку

void workWithAlphaImage();
void writeDataFrom_JPEGdecoder (int decodedWidth, int  decodedHeight, void* decoderOutput);
void writeDataFrom_BMPdecoder  (int bmpWidth, int  bmpHeight, size_t bmpStride, void* bmpRowPtr);

// --  Multithread fill по строкам (идеальный паттерн)
// -- Когда это нужно
// -- большие изображения
// -- CPU-bound conversion
// -- без гонок данных
// -- Ключевая идея
// -- 👉 каждый поток работает со своей строкой
void convertRows(const ImageCommon& src, ImageCommon& dst, int y0, int y1);
void parallelConvert(const ImageCommon& src, ImageCommon& dst);




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



// -- 
void writeDataFrom_JPEGdecoder (int decodedWidth, int  decodedHeight, void* decoderOutput) {
// Пример: JPEG decoder (RGB8)
// Допустим, сторонний decoder (libjpeg, stb, libjpeg-turbo) даёт:
// width
// height
// interleaved RGB8 (uint8_t*)
// Код заполнения :
ImageCommon img;

img.width  = decodedWidth;
img.height = decodedHeight;

img.format = PixelFormat{
    ColorSpace::RGB,
    ChannelLayout::RGB,
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

// стандартный плотный stride
img.strideBytes = img.width * img.format.bytesPerPixel();

img.data.resize(img.sizeBytes());

// decoderOutput — uint8_t* RGBRGBRGB...
std::memcpy(img.data.data(),
            decoderOutput,
            img.sizeBytes());


// ✔ O(1)
// ✔ без копий по строкам
// ✔ zero overhead
}


void* bmpRowPtr(int row) {
    
}


// -- (BGR8 + padding)
void writeDataFrom_BMPdecoder(int bmpWidth, int  bmpHeight, size_t bmpStride, void* bmpRowPtr)
{
//   BMP часто даёт:
// 
// BGR
// 
// stride выровнен на 4 байта

ImageCommon img;

img.width  = bmpWidth;
img.height = bmpHeight;

img.format = PixelFormat{
    ColorSpace::RGB,
    ChannelLayout::BGR,     // ВАЖНО
    ChannelType::UInt,
    ChannelSize::Bit8,
    PixelPacking::None
};

img.strideBytes = bmpStride;   // --  с padding
img.data.resize(img.strideBytes * img.height);

// читаем построчно
for (int y = 0; y < img.height; ++y)
{
    std::memcpy(
        img.data.data() + y * img.strideBytes,
        // bmpRowPtr(y),
        bmpRowPtr,  // -- нужная строка в массиве изоюбражения bmp
        img.strideBytes
    );
}


// ➡️ Дальше PixelConverter сделает BGR→RGB, если нужно.
} // -- writeDataFrom_BMPdecoder  


void convertRows(const ImageCommon& src,
                 ImageCommon& dst,
                 int y0, int y1)
{
    for (int y = y0; y < y1; ++y)
    {
        const byte* srcRow = src.data.data() + y * src.stride();
        byte* dstRow = dst.data.data() + y * dst.stride();

        for (int x = 0; x < src.width; ++x)
        {
            const byte* sp = srcRow + x * 3;
            byte* dp = dstRow + x;

            // FAST PATH — без PixelView
            double r = sp[0] / 255.0;
            double g = sp[1] / 255.0;
            double b = sp[2] / 255.0;

            dp[0] = static_cast<byte>(
                (0.299*r + 0.587*g + 0.114*b) * 255.0
            );
        }
    }
}  // -- end func void convertRows

void parallelConvert(const ImageCommon& src, ImageCommon& dst)
{
    const int threads = std::thread::hardware_concurrency();
    std::vector<std::thread> pool;

    int rowsPerThread = src.height / threads;

    for (int t = 0; t < threads; ++t)
    {
        int y0 = t * rowsPerThread;
        int y1 = (t == threads - 1)
               ? src.height
               : y0 + rowsPerThread;

        pool.emplace_back(convertRows,
                          std::cref(src),
                          std::ref(dst),
                          y0, y1);
    }

    for (auto& th : pool)
        th.join();
}
