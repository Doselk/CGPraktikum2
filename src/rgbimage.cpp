#include "rgbimage.h"
#include "color.h"
#include "assert.h"

RGBImage::RGBImage(unsigned int Width, unsigned int Height)
{
    this->m_Height = Height;
    this->m_Width = Width;
    this->m_Image = new Color[Height * Width];
}

RGBImage::~RGBImage()
{
    delete[] this->m_Image;
}

void RGBImage::setPixelColor(unsigned int x, unsigned int y, const Color& c)
{
    this->m_Image[y * width() + x] = c;
}

const Color& RGBImage::getPixelColor(unsigned int x, unsigned int y) const
{
    return this->m_Image[y * width() + x];
}

unsigned int RGBImage::width() const
{
    return this->m_Width;
}
unsigned int RGBImage::height() const
{
    return this->m_Height;
}

unsigned char RGBImage::convertColorChannel(float v)
{
    char erg = NULL;
    if (v > 0.0f && v < 1.0f) {
        erg = v * 255;
    }
    else if (v <= 0.0f) {
        erg = 0;
    }
    else if (v >= 1.0f) {
        erg = 255;
    }
    return erg;
}

bool RGBImage::saveToDisk(const char* Filename)
{
    // https://de.wikipedia.org/wiki/Windows_Bitmap
    struct BmpHeader {
        uint16_t bfType1 = 0x4D42;
        uint32_t bfSize = 0;
        uint32_t bfReserved = 0;
        uint32_t bfOffBits = 54;
    } bmpHeader;

    struct BmpInfoHeader {
        uint32_t biSize = 40;
        int32_t biWidth = 800;
        int32_t biHeight = 600;
        uint16_t biPlanes = 1;
        uint16_t biBitCount = 24;
        uint32_t biCompression = 0;
        uint32_t biSizeImage = 0;
        int32_t biXPelsPerMeter = 0;
        int32_t biYPelsPerMeter = 0;
        uint32_t biClrUsed = 0;
        uint32_t biClrImportant = 0;
    } bmpInfoHeader;

    bmpHeader.bfSize = width() * height() * 3 + 54;
    bmpInfoHeader.biSizeImage = width() * height() * 3;
    bmpInfoHeader.biHeight = -height(); //wichtig da wir ein top bottom ansatz haben mit der bmp
    bmpInfoHeader.biWidth = width();

    FILE* file = fopen(Filename, "wb");
    fwrite(&bmpHeader.bfType1, 2, 1, file);// https://cplusplus.com/reference/cstdio/fwrite/
    fwrite(&bmpHeader.bfSize, 4, 1, file);
    fwrite(&bmpHeader.bfReserved, 4, 1, file);
    fwrite(&bmpHeader.bfOffBits, 4, 1, file);
    fwrite(&bmpInfoHeader, 40, 1, file);


    for (int y = 0; y < height(); y++) {
        for (int x = 0; x < width(); x++)
        {
            Color color = getPixelColor(x, y);
            unsigned char r = convertColorChannel(color.R);
            unsigned char g = convertColorChannel(color.G);
            unsigned char b = convertColorChannel(color.B);
            fwrite(&b, 1, 1, file);
            fwrite(&g, 1, 1, file);
            fwrite(&r, 1, 1, file);
        }
    }

    fclose(file);
    return true;
}
