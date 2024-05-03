#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define IMAGE_IMPL
#include "image.h"

#define NOB_IMPLEMENTATION
#include "nob.h"

void usage(const char *program_name) {
    printf("Usage: %s <filename>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);
    if (argc == 0) {
        usage(program_name);
        fprintf(stderr, "ERROR: no filename provided\n");
        return 1;
    }

    int width, height;
    unsigned char *data = stbi_load(argv[0], &width, &height, NULL, 4);
    if (data == NULL) {
        fprintf(stderr, "Could not load image %s: %s\n", argv[0], stbi_failure_reason());
        return 1;
    }
    Image img = (Image) {
        .width = width,
        .height = height,
        .stride = width,
        .data = (Color *)data
    };
    if (!img_write(img, stdout)) return 1;
    return 0;
}
