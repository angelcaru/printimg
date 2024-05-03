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

bool color_from_string(const char *str, Color *c);

typedef struct {
    int width, height, stride;
    Color *data;
} Image;

bool img_read(Image *img, FILE *stream);
bool img_write(Image img, FILE *stream);

void draw_rect(Image *img, int x, int y, int w, int h, Color c);
void draw_circle(Image *img, int x, int y, int r, Color c);

#endif // IMAGE_H

#ifdef IMAGE_IMPL

bool ishex(char ch) {
    return (ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'f') || (ch >= 'A' && ch <= 'F');
}

uint8_t parse_nybble(char ch) {
    if (ch >= '0' && ch <= '9') {
        return (uint8_t)(ch - '0');
    } else if (ch >= 'a' && ch <= 'f') {
        return (uint8_t)(ch - 'a' + 10);
    } else if (ch >= 'A' && ch <= 'F') {
        return (uint8_t)(ch - 'A' + 10);
    } else {
        fprintf(stderr, "ERROR: invalid hex character: '%c'\n", ch);
        return 0;
    }
}

uint8_t parse_hex(const char *chs) {
    if (!ishex(chs[0]) || !ishex(chs[1])) {
        fprintf(stderr, "ERROR: invalid hex character: '%s'\n", chs);
        return 0;
    }
    return (uint8_t)((uint8_t)parse_nybble(chs[0]) << 4 | parse_nybble(chs[1]));
}

bool ishexbyte(const char *chs) {
    return ishex(chs[0]) && ishex(chs[1]);
}

bool color_from_string(const char *str, Color *c) {
    if (*str != '#') {
        fprintf(stderr, "ERROR: invalid color string '%s': expected '#' as first character\n", str);
        return false;
    }
    str++;
    if (!ishexbyte(str)) return false;
    c->r = parse_hex(str); str += 2;

    if (!ishexbyte(str)) return false;
    c->g = parse_hex(str); str += 2;

    if (!ishexbyte(str)) return false;
    c->b = parse_hex(str); str += 2;

    if (*str != '\0') {
        fprintf(stderr, "ERROR: invalid color string '%s': expected end of input after 3 hex bytes\n", str);
        return false;
    }

    c->a = 255;
    return true;
}

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

void draw_rect(Image *img, int x, int y, int w, int h, Color c) {
    for (int dx = 0; dx < w; dx++) {
        for (int dy = 0; dy < h; dy++) {
            int cx = x + dx;
            int cy = y + dy;
            if (cx < 0 || cx >= img->width || cy < 0 || cy >= img->height) continue;
            img->data[cy * img->stride + cx] = c;
        }
    }
}

void draw_circle(Image *img, int cx, int cy, int r, Color c) {
    for (int dx = 0; dx < r * 2; dx++) {
        for (int dy = 0; dy < r * 2; dy++) {
            int x = cx + dx - r;
            int y = cy + dy - r;
            if (x < 0 || x >= img->width || y < 0 || y >= img->height) continue;
            int dx2 = x - cx;
            int dy2 = y - cy;
            if (dx2 * dx2 + dy2 * dy2 < r * r) {
                img->data[y * img->stride + x] = c;
            }
        }
    }
}

#endif
