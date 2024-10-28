#include "image.h"
#include <stdlib.h>

struct image create_image(uint64_t width, uint64_t height) {
    struct image img;
    img.width = width;
    img.height = height;
    img.data = malloc(width * height * sizeof(struct pixel));
    return img;
}

void free_image(struct image *img) {
    free(img->data);
    img->data = NULL;
}
