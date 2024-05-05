#include "cli.h"
#include "image.h"

void usage(const char *program_name) {
    printf("Usage: %s <width> <height> [color]\n", program_name);
    printf("If [color] is not provided, the image will be filled by a transparent color");
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);

    int w = atoi(shift_expect(&argc, &argv, "width", program_name));
    int h = atoi(shift_expect(&argc, &argv, "height", program_name));

    Color c;
    if (argc == 0) {
        c.rgba = 0;
    } else {
        char *color_str = shift_args(&argc, &argv);
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
    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
