#define IMAGE_IMPL
#include "image.h"

int main(void) {
    Image img;
    if (!img_read(&img, stdin)) return 1;
    printf("Resolution: %dx%d\n", img.width, img.height);
    return 0;
}
