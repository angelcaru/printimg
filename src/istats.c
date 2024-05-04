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
    if (!img_read(&img, stdin, program_name)) return 1;
    printf("Resolution: %dx%d\n", img.width, img.height);
    return 0;
}
