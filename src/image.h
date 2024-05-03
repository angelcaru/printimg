#ifndef IMAGE_H
#define IMAGE_H

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef IMG_ASSERT
#define IMG_ASSERT(cond, msg) do { \
        if (!(cond)) { \
            fprintf(stderr, "%s:%d: ASSERTION FAILED: %s\n", __FILE__, __LINE__, msg); \
            abort(); \
        } \
    } while (0)
#endif

typedef union {
    uint32_t rgba;
    struct {
        uint8_t r, g, b, a;
    };
} Color;

typedef struct {
    int width, height, stride;
    Color *data;
} Image;

bool img_read(Image *img, FILE *stream);
bool img_write(Image img, FILE *stream);

#endif // IMAGE_H

#ifdef IMAGE_IMPL

bool img_read(Image *img, FILE *stream) {
    int size[2];
    if (fread(size, sizeof(int), 2, stream) != 2) {
        fprintf(stderr, "ERROR: failed to read image size: %s\n", strerror(ferror(stream)));
        return false;
    }

    size_t data_size = size[0] * size[1];

    img->width = img->stride = size[0];
    img->height = size[1];
    img->data = malloc(data_size * sizeof(Color));
    if (fread(img->data, sizeof(Color), data_size, stream) != data_size) {
        fprintf(stderr, "ERROR: failed to read image data: %s\n", strerror(ferror(stream)));
        return false;
    }

    return true;
}

bool img_write(Image img, FILE *stream) {
    int size[2] = {img.width, img.height};
    fwrite(size, sizeof(int), 2, stream);
    if (ferror(stream)) {
        fprintf(stderr, "ERROR: failed to write image size: %s\n", strerror(ferror(stream)));
        return false;
    }

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            Color pixel = img.data[y * img.stride + x];
            fwrite(&pixel, sizeof(Color), 1, stream);
            if (ferror(stream)) {
                fprintf(stderr, "ERROR: failed to write pixel: %s\n", strerror(ferror(stream)));
                return false;
            }
        }
    }
    return true;
}

#endif
