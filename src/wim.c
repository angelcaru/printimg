#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

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

    const char *filename = nob_shift_args(&argc, &argv);

    Image img;
    if (!img_read(&img, stdin)) return 1;
    if (!stbi_write_png(filename, img.width, img.height, 4, img.data, img.stride * 4)) {
        fprintf(stderr, "Could not write image %s\n", filename);
        return 1;
    }
    return 0;
}
