#include "stb_image.h"
#include "image.h"
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
    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
