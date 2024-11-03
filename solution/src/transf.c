#include "../include/transfo.h"

struct image rotate_90(const struct image source) {
    struct image rotated = create_image(source.height, source.width);

    for (uint64_t i = 0; i < source.height; i++) {
        for (uint64_t j = 0; j < source.width; j++) {
            rotated.data[j * rotated.width + (rotated.width - i - 1)] = source.data[i * source.width + j];
        }
    }

    return rotated;
}
