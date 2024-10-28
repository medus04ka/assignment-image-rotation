#include "bmp.h"
#include <stdlib.h>

#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
};
#pragma pack(pop)

enum read_status from_bmp(FILE *in, struct image *img) {
    struct bmp_header header;
    fread(&header, sizeof(struct bmp_header), 1, in);

    if (header.bfType != 0x4D42) {
        return READ_INVALID_SIGNATURE;
    }

    img->width = header.biWidth;
    img->height = header.biHeight;
    img->data = malloc(img->width * img->height * sizeof(struct pixel));

    fseek(in, header.bOffBits, SEEK_SET);

    for (uint64_t i = 0; i < img->height; i++) {
        fread(img->data + i * img->width, sizeof(struct pixel), img->width, in);
        fseek(in, (4 - ((long)img->width * 3) % 4) % 4, SEEK_CUR);
    }

    return READ_OK;
}

enum write_status to_bmp(FILE *out, const struct image *img) {
    struct bmp_header header = {0};
    header.bfType = 0x4D42;
    header.bfileSize = (uint32_t) (sizeof(struct bmp_header) + img->width * img->height * sizeof(struct pixel));
    header.bOffBits = sizeof(struct bmp_header);
    header.biSize = 40;
    header.biWidth = (uint32_t) (img->width);
    header.biHeight = (uint32_t) (img->height);
    header.biPlanes = 1;
    header.biBitCount = 24;
    header.biSizeImage = (uint32_t) (img->width * img->height * sizeof(struct pixel));

    fwrite(&header, sizeof(struct bmp_header), 1, out);

    for (uint64_t i = 0; i < img->height; i++) {
        fwrite(img->data + i * img->width, sizeof(struct pixel), img->width, out);
        uint8_t padding = 0;
        fwrite(&padding, 1, (4 - (img->width * 3) % 4) % 4, out);
    }

    return WRITE_OK;
}
