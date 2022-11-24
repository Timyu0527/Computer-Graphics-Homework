#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include <iostream>
#include <algorithm>

#include "constant.h"

class ImageHandler{
    private:
        int width, height, width_bytes, padding_size;
        unsigned char padding[4];
        unsigned char *buffer, *file_header, *info_header;
        unsigned char *createFileHeader();
        unsigned char *createInfoHeader();
    public:
        static ImageHandler img_hdr;
        ImageHandler();
        void readBuffer(unsigned char *_buf, int _w, int _h);
        void outputImage(const char *file_name);
};

#endif