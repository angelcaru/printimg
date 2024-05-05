#include "cli.h"
#include "image.h"

void usage(const char *program_name) {
    printf("Usage: %s <x> <y> <radius> <color>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);

    int x = atoi(shift_expect(&argc, &argv, "x pos", program_name));
    int y = atoi(shift_expect(&argc, &argv, "y pos", program_name));
    int r = atoi(shift_expect(&argc, &argv, "radius", program_name));

    char *color_str = shift_expect(&argc, &argv, "color", program_name);
    Color c;
    if (!color_from_string(color_str, &c)) return 1;

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;
    draw_circle(&img, x, y, r, c);
    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
