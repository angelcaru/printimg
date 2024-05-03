#define NOB_IMPLEMENTATION
#include "nob.h"

#define IMAGE_IMPL
#include "image.h"

void usage(const char *program_name) {
    printf("Usage: %s <x> <y> <w> <h>\n", program_name);
}

char *shift_expect(int *argc, char ***argv, const char *arg_name, const char *program_name) {
    if (*argc == 0) {
        usage(program_name);
        fprintf(stderr, "ERROR: missing %s\n", arg_name);
        exit(1);
    }
    return nob_shift_args(argc, argv);
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);

    int x = atoi(shift_expect(&argc, &argv, "x pos", program_name));
    int y = atoi(shift_expect(&argc, &argv, "y pos", program_name));
    int w = atoi(shift_expect(&argc, &argv, "width", program_name));
    int h = atoi(shift_expect(&argc, &argv, "height", program_name));

    Image img;
    if (!img_read(&img, stdin)) return 1;

    img = img_crop(img, x, y, w, h);
    if (!img_write(img, stdout)) return 1;
    return 0;
}
