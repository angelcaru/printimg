#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define IMAGE_IMPL
#include "image.h"

#define CLI_IMPL
#include "cli.h"

void usage(const char *program_name) {
    printf("Usage: %s <filename>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);
    if (argc == 0) {
        usage(program_name);
        fprintf(stderr, "ERROR: no filename provided\n");
        return 1;
    }

    const char *filename = shift_args(&argc, &argv);

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;
    if (!stbi_write_png(filename, img.width, img.height, 4, img.data, img.stride * 4)) {
        fprintf(stderr, "%s: ERROR: Could not write image %s\n", program_name, filename);
        return 1;
    }
    return 0;
}
