#define NOB_IMPLEMENTATION
#include "nob.h"

#define IMAGE_IMPL
#include "image.h"

#define CLI_IMPL
#include "cli.h"

void usage(const char *program_name) {
    printf("Usage: %s <x> <y> <w> <h> <color>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);

    int x = atoi(shift_expect(&argc, &argv, "x pos", program_name));
    int y = atoi(shift_expect(&argc, &argv, "y pos", program_name));
    int w = atoi(shift_expect(&argc, &argv, "width", program_name));
    int h = atoi(shift_expect(&argc, &argv, "height", program_name));

    char *color_str = shift_expect(&argc, &argv, "color", program_name);
    Color c;
    if (!color_from_string(color_str, &c)) return 1;

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;
    draw_rect(&img, x, y, w, h, c);
    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
