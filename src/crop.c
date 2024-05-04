#define CLI_IMPL
#include "cli.h"

#define IMAGE_IMPL
#include "image.h"

void usage(const char *program_name) {
    printf("Usage: %s <x> <y> <w> <h>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);

    int x = atoi(shift_expect(&argc, &argv, "x pos", program_name));
    int y = atoi(shift_expect(&argc, &argv, "y pos", program_name));
    int w = atoi(shift_expect(&argc, &argv, "width", program_name));
    int h = atoi(shift_expect(&argc, &argv, "height", program_name));

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;

    img = img_crop(img, x, y, w, h);
    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
