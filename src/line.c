#include "nob.h"
#include "image.h"
#include "cli.h"

void usage(const char *program_name) {
    printf("Usage: %s <x1> <y1> <x2> <y2> <color>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);

    int x1 = atoi(shift_expect(&argc, &argv, "x1", program_name));
    int y1 = atoi(shift_expect(&argc, &argv, "y1", program_name));
    int x2 = atoi(shift_expect(&argc, &argv, "x2", program_name));
    int y2 = atoi(shift_expect(&argc, &argv, "y2", program_name));

    char *color_str = shift_expect(&argc, &argv, "color", program_name);
    Color c;
    if (!color_from_string(color_str, &c)) return 1;

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;
    draw_line(&img, x1, y1, x2, y2, c);
    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
