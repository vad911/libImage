Структура библиотеки myCoreImage
myCoreImage
│
├─ types.h
│   ├─ byte
│   ├─ enum PixelFormat { RGB565, BW1 }
│   ├─ enum ChannelSemantic { Red, Green, Blue, Alpha, Gray, BlackWhite, Unknown }
│   ├─ enum ChannelDataType { UnsignedInt, SignedInt, Float }
│   └─ enum ChannelBitDepth { Bit1, Bit8, Bit16, Bit32, Bit64 }
│
├─ lib_coreImage.h
│   └─ COREIMAGE_API макросы для экспорт/импорт DLL
│
├─ channelElementDesc.h
│   └─ struct ChannelElementDesc
│       ├─ dataType, bitDepth
│       ├─ isValid()
│       └─ bytesPerElement()
│
├─ channel_info.h / channel_info.cpp
│   └─ class ChannelInfo
│       ├─ semantic() -> ChannelSemantic
│       ├─ elementDesc() -> ChannelElementDesc
│       └─ хранит ChannelSemantic + ChannelElementDesc
│
├─ channel_data.h / channel_data.cpp
│   └─ class ChannelData
│       ├─ width(), height(), strideBytes()
│       ├─ data(), dataPtr()
│       └─ владеет буфером std::vector<byte>
│
├─ channel.h / channel.cpp
│   └─ class Channel
│       ├─ хранит ChannelInfo + ChannelData
│       ├─ view() -> ChannelView
│       └─ конструкторы для width, height
│
├─ channelView.h / channelView.cpp
│   └─ class ChannelView
│       ├─ data() -> void*
│       ├─ strideBytes()
│       └─ width/height/bytesPerElement()
│
├─ image.h / image.cpp
│   └─ class Image
│       ├─ width(), height(), numChannels()
│       ├─ channel(i) -> Channel&
│       ├─ channels() -> ChannelArray&
│       ├─ static fromInterleaved(...) -> Image
│       ├─ static fromPacked(...) -> Image
│       └─ toInterleaved() -> std::vector<byte>
│
├─ imageView.h (в image.h)
│   └─ class ImageView
│       └─ channelView(i) -> ChannelView
│
├─ image_converters.h / image_converters.cpp
│   └─ namespace myCoreImage (или myCoreImage::converters)
│       ├─ fromInterleaved(...) -> ChannelArray
│       ├─ toInterleaved(...) -> std::vector<byte>
│       └─ fromPacked(...) -> Image
│
└─ test/
    ├─ test_coreImage.cpp
    ├─ test_coreImage02.cpp
    └─ test_coreImage03.cpp

Логика взаимодействия
Interleaved / Packed (std::vector<byte>)
       │
       ▼
  image_converters
       │
       ▼
  ChannelArray (planar) <-- Channel (ChannelInfo + ChannelData)
       │
       ▼
       Image
       │
       ▼
  ImageView → ChannelView → доступ к данным без копий


ChannelData — владеет памятью.

Channel — оборачивает ChannelData + метаданные (ChannelInfo).

ChannelView — предоставляет доступ к памяти без копий, stride-aware.

Image — коллекция Channel-ов + фабрики fromInterleaved/fromPacked.

image_converters — чисто функции преобразования потоков байтов ↔ ChannelArray (planar).

💡 Совет по организации файлов после переименования coreImage → image_converters

Сейчас image_converters.h/cpp выполняют роль утилит по конвертации: planar ↔ interleaved, packed ↔ planar.

Можно сделать отдельный неймспейс:

namespace myCoreImage::converters {
    ChannelArray fromInterleaved(...);
    std::vector<byte> toInterleaved(...);
    Image fromPacked(...);
}


Это подчеркнёт, что Image не должен знать об этих деталях, а ImageView/ChannelView только читают/модифицируют данные.

// -- 

