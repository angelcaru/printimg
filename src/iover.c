#include "nob.h"
#include "stb_image.h"
#include "image.h"
#include "cli.h"

void usage(const char *program_name) {
    printf("Usage: %s <x> <y> <w> <h> <path/to/other_image.png>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);

    size_t x = atoi(shift_expect(&argc, &argv, "x pos", program_name));
    size_t y = atoi(shift_expect(&argc, &argv, "y pos", program_name));
    size_t w = atoi(shift_expect(&argc, &argv, "width", program_name));
    size_t h = atoi(shift_expect(&argc, &argv, "height", program_name));

    const char *other_image_path = shift_expect(&argc, &argv, "path to other image", program_name);

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;

    int width, height;
    unsigned char *data = stbi_load(other_image_path, &width, &height, NULL, 4);
    if (data == NULL) {
        fprintf(stderr, "Could not load image %s: %s\n", other_image_path, stbi_failure_reason());
        return 1;
    }
    Image src_img = (Image) {
        .width = width,
        .height = height,
        .stride = width,
        .data = (Color *)data
    };

	for (size_t dy = 0; dy < h; dy++) {
		size_t src_y = dy * src_img.height / h;
		for (size_t dx = 0; dx < w; dx++) {
			size_t src_x = dx * src_img.width / w;
			IMG_AT(&img, x + dx, y + dy) = IMG_AT(&src_img, src_x, src_y);
		}
	}

    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
