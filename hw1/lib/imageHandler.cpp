#include "imageHandler.h"

ImageHandler::ImageHandler(){}

unsigned char *ImageHandler::createFileHeader(){
    file_header = new unsigned char[FILE_HEADER_SIZE];
    std::fill(file_header, file_header + FILE_HEADER_SIZE, 0);

    int fixed_width = width_bytes + padding_size;
    int file_size = (fixed_width) * height + FILE_HEADER_SIZE + INFO_HEADER_SIZE;

    file_header[ 0] = (unsigned char)('B');
    file_header[ 1] = (unsigned char)('M');
    file_header[ 2] = (unsigned char)(file_size      );
    file_header[ 3] = (unsigned char)(file_size >>  8);
    file_header[ 4] = (unsigned char)(file_size >> 16);
    file_header[ 5] = (unsigned char)(file_size >> 24);
    file_header[10] = (unsigned char)(FILE_HEADER_SIZE + INFO_HEADER_SIZE);

    return file_header;
}

unsigned char *ImageHandler::createInfoHeader(){
    info_header = new unsigned char[INFO_HEADER_SIZE];
    std::fill(info_header, info_header + INFO_HEADER_SIZE, 0);

    info_header[ 0] = (unsigned char)(INFO_HEADER_SIZE);
    info_header[ 4] = (unsigned char)(width      );
    info_header[ 5] = (unsigned char)(width >>  8);
    info_header[ 6] = (unsigned char)(width >> 16);
    info_header[ 7] = (unsigned char)(width >> 24);
    info_header[ 8] = (unsigned char)(height      );
    info_header[ 9] = (unsigned char)(height >>  8);
    info_header[10] = (unsigned char)(height >> 16);
    info_header[11] = (unsigned char)(height >> 24);
    info_header[12] = (unsigned char)(1);
    info_header[14] = (unsigned char)(BYTE_PER_PIXEL*8);

    return info_header;
}

void ImageHandler::readBuffer(unsigned char *_buf, int _w, int _h){
    width = _w, height = _h;
    buffer = _buf;
    for(int i = 0; i < width; i++){ /* Assign 0 opacity to black pixels */
        for(int j = 0; j < height; j++){
            std::swap(buffer[i * height * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL],
                      buffer[i * height * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL + 2]);
        }
    }
    width_bytes = width * BYTE_PER_PIXEL;
    std::fill(padding, padding + 4, 0);
    padding_size = (4 - (width_bytes % 4)) % 4;

    unsigned char *file_header = createFileHeader();
    unsigned char *info_header = createInfoHeader();
}

void ImageHandler::outputImage(const char *file_name){
    FILE *image = fopen(file_name, "wb");

    fwrite(file_header, 1, FILE_HEADER_SIZE, image);
    fwrite(info_header, 1, INFO_HEADER_SIZE, image);
    for(int i = 0; i < height; ++i){
        fwrite(buffer + (i * width_bytes), BYTE_PER_PIXEL, width, image);
        fwrite(padding, 1, padding_size, image);
    }

    for(int i = 0; i < width; i++){ /* Assign 0 opacity to black pixels */
        for(int j = 0; j < height; j++){
            std::swap(buffer[i * height * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL],
                      buffer[i * height * BYTE_PER_PIXEL + j * BYTE_PER_PIXEL + 2]);
        }
    }
    fclose(image);
}