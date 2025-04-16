#include "nob.h"
#include "stb_image.h"
#include "image.h"
#include "cli.h"

void usage(const char *program_name) {
    printf("Usage: %s <path/to/mask.png>\n", program_name);
}

int main(int argc, char **argv) {
    const char *program_name = nob_shift_args(&argc, &argv);

    const char *other_image_path = shift_expect(&argc, &argv, "path to mask", program_name);

    Image img;
    if (!img_read(&img, stdin, program_name)) return 1;

    int width, height;
    unsigned char *data = stbi_load(other_image_path, &width, &height, NULL, 4);
    if (data == NULL) {
        fprintf(stderr, "Could not load image %s: %s\n", other_image_path, stbi_failure_reason());
        return 1;
    }
    Image mask = (Image) {
        .width = width,
        .height = height,
        .stride = width,
        .data = (Color *)data
    };

	if (img.width != mask.width || img.height != mask.height) {
		fprintf(stderr, "image and mask must be the same size\n");
		return 1;
	}
	for (size_t y = 0; y < img.height; y++) {
		for (size_t x = 0; x < img.width; x++) {
			uint8_t r = IMG_AT(&img, x, y).r * IMG_AT(&mask, x, y).r / 255;
			uint8_t g = IMG_AT(&img, x, y).g * IMG_AT(&mask, x, y).g / 255;
			uint8_t b = IMG_AT(&img, x, y).b * IMG_AT(&mask, x, y).b / 255;
			uint8_t a = IMG_AT(&img, x, y).a * IMG_AT(&mask, x, y).a / 255;
			IMG_AT(&img, x, y) = (Color) { .r = r, .g = g, .b = b, .a = a };
		}
	}

    if (!img_write(img, stdout, program_name)) return 1;
    return 0;
}
