#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define IMAGE_IMPL
#include "image.h"

#define CLI_IMPL
#include "cli.h"

void usage(const char *program_name) {
    printf("Usage: %s\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);

    Image img;

    if (argc != 0) {
        const char *path = shift_args(&argc, &argv);
        int width, height;
        unsigned char *data = stbi_load(path, &width, &height, NULL, 4);
        if (data == NULL) {
            fprintf(stderr, "%s: ERROR: could not load image %s: %s\n", program_name, path, stbi_failure_reason());
            return 1;
        }
        img = (Image) {
            .width = width,
            .height = height,
            .stride = width,
            .data = (Color *)data
        };
    } else {
        if (!img_read(&img, stdin, program_name)) return 1;
    }
    printf("Resolution: %dx%d\n", img.width, img.height);
    return 0;
}
