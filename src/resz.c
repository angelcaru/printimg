#include "cli.h"
#include "image.h"

#include <assert.h>

void usage(const char *program_name) {
    printf("Usage: %s <factor>\n", program_name);
}

void size_down(Image *img, Image src, float factor) {
    for (int y = 0; y < img->height; y++) {
        int sy = y / factor;
        for (int x = 0; x < img->width; x++) {
            int sx = x / factor;
            Color c = src.data[sy * src.stride + sx];
            draw_point(img, x, y, c);
        }
    }
}

void size_up(Image *img, Image src, float factor) {
    for (int y = 0; y < img->height; y++) {
        int sy = y / factor;
        for (int x = 0; x < img->width; x++) {
            int sx = x / factor;
            Color c = src.data[sy * src.stride + sx];
            draw_point(img, x, y, c);
        }
    }
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);

    float factor = atof(shift_expect(&argc, &argv, "scaling factor", program_name));

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;

    Image new_img = {
        .width  = img.width  * factor,
        .height = img.height * factor,
        .stride = img.width  * factor,
        .data   = NULL,
    };
    new_img.data = malloc(sizeof(Color)*new_img.width*new_img.height);

    for (int y = 0; y < new_img.height; y++) {
        int sy = y / factor;
        for (int x = 0; x < new_img.width; x++) {
            int sx = x / factor;
            Color c = img.data[sy * img.stride + sx];
            draw_point(&new_img, x, y, c);
        }
    }

    if (!img_write(new_img, stdout, program_name)) return 1;
    return 0;
}
