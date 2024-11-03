#include "../include/bmp.h"
#include "../include/transfo.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source-image> <transformed-image>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "rb");
    if (!input) {
        perror("Бредик выдает, потому что не может открыть input, его просто нету");
        return 1;
    }

    struct image img;
    if (from_bmp(input, &img) != READ_OK) {
        fclose(input);
        fprintf(stderr, "Не читается твой BMP file, бредик не пишем\n");
        return 1;
    }
    fclose(input);

    struct image rotated = rotate_90(img);

    FILE *output = fopen(argv[2], "wb");
    if (!output) {
        perror("Бредик выдает, потому что не может открыть output, зачем ты его открываешь вообще");
        free_image(&img);
        return 1;
    }

    if (to_bmp(output, &rotated) != WRITE_OK) {
        fprintf(stderr, "выдает полный бредик, потому что не может считать ничего с файла\n");
    }

    fclose(output);
    free_image(&img);
    free_image(&rotated);

    return 0;
}
