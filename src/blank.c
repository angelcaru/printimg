#define NOB_IMPLEMENTATION
#include "nob.h"

#define IMAGE_IMPL
#include "image.h"

void usage(const char *program_name) {
    printf("Usage: %s <width> <height> [color]\n", program_name);
    printf("If [color] is not provided, the image will be filled by a transparent color");
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

    int w = atoi(shift_expect(&argc, &argv, "width", program_name));
    int h = atoi(shift_expect(&argc, &argv, "height", program_name));

    Color c;
    if (argc == 0) {
        c.rgba = 0;
    } else {
        char *color_str = nob_shift_args(&argc, &argv);
        if (!color_from_string(color_str, &c)) return 1;
    }

    Image img = {
        .width = w,
        .height = h,
        .stride = w,
        .data = (Color *)malloc(sizeof(Color) * w * h),
    };
    
    for (int i = 0; i < w * h; i++) {
        img.data[i] = c;
    }
    if (!img_write(img, stdout)) return 1;
    return 0;
}
