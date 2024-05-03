#define NOB_IMPLEMENTATION
#include "nob.h"

#define IMAGE_IMPL
#include "image.h"

void usage(const char *program_name) {
    printf("Usage: %s <x> <y> <w> <h> <color>\n", program_name);
}

char *shift_expect(int *argc, char ***argv, const char *arg_name, const char *program_name) {
    if (*argc == 0) {
        usage(program_name);
        fprintf(stderr, "ERROR: missing %s\n", arg_name);
        exit(1);
    }
    return nob_shift_args(argc, argv);
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

Color color_from_string(const char *str) {
    Color c = { .r = 0, .g = 0, .b = 0, .a = 255 };
    if (sscanf(str, "#%02hhx%02hhx%02hhx", &c.r, &c.g, &c.b) != 3) {
        fprintf(stderr, "ERROR: could not parse color: %s\n", str);
        exit(1);
    }
    return c;
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);

    int x = atoi(shift_expect(&argc, &argv, "x pos", program_name));
    int y = atoi(shift_expect(&argc, &argv, "y pos", program_name));
    int w = atoi(shift_expect(&argc, &argv, "width", program_name));
    int h = atoi(shift_expect(&argc, &argv, "height", program_name));

    char *color_str = shift_expect(&argc, &argv, "color", program_name);
    Color c = color_from_string(color_str);

    Image img;
    if (!img_read(&img, stdin)) return 1;
    draw_rect(&img, x, y, w, h, c);
    if (!img_write(img, stdout)) return 1;
    return 0;
}
