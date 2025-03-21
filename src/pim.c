#include "stb_image.h"
#include "image.h"
#include "cli.h"
#include "ansiterm.h"

#include <sys/ioctl.h>
#include <stdbool.h>
#include <time.h>

void usage(const char *program_name) {
    printf("Usage: %s <filename>\n", program_name);
}

void get_term_size(int *w, int *h) {
    struct winsize ws;
    ioctl(fileno(stderr), TIOCGWINSZ, &ws);
    *w = ws.ws_col;
    *h = ws.ws_row;
}

#define ASSUMED_BG ((Color) { .r = 24, .g = 24, .b = 24, .a = 255 }) // Used for alpha

float lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

Color color_lerp(Color a, Color b, float t) {
    return (Color) {
        .r = lerp(a.r, b.r, t),
        .g = lerp(a.g, b.g, t),
        .b = lerp(a.b, b.b, t),
        .a = lerp(a.a, b.a, t),
    };
}

void print_img_struct(Image img) {
    int termwidth, termheight;
    get_term_size(&termwidth, &termheight);

    float ystep = img.height / (termheight * 0.8);
    float xstep = ystep / 2;

    for (float y = 0; y < img.height; y += ystep) {
        for (float x = 0; x < img.width; x += xstep) {
            int x_int = (int)x;
            int y_int_top = (int)y;
            int y_int_bottom = (int)(y + ystep / 2); if (y_int_bottom >= img.height) y_int_bottom = y_int_top;
            Color top = img.data[y_int_top * img.stride + x_int];
            Color bottom = img.data[y_int_bottom * img.stride + x_int];

            if (top.a < 255) top = color_lerp(ASSUMED_BG, top, top.a / 255.0f);
            if (bottom.a < 255) bottom = color_lerp(ASSUMED_BG, bottom, bottom.a / 255.0f);

            ansiterm_set_bg_24bit(top.r, top.g, top.b);
            ansiterm_set_fg_24bit(bottom.r, bottom.g, bottom.b);
            printf("▄");
        }
        ansiterm_set_attr(ANSITERM_ATTR_RESET);
        printf("\n");
    }
}

bool print_img_file(const char *path) {
    int width, height;
    unsigned char *data_c = stbi_load(path, &width, &height, NULL, 4);
    if (data_c == NULL) {
        fprintf(stderr, "Could not load image %s: %s", path, stbi_failure_reason());
        return false;
    }
    Color *data = (Color *)data_c;

    print_img_struct((Image) { .width = width, .height = height, .stride = width, .data = (Color *)data });

    return true;
}

int main(int argc, char **argv) {
    const char *program_name = shift_args(&argc, &argv);

    if (argc == 0) {
        Image img;
        if (!img_read(&img, stdin, program_name)) return 1;
        print_img_struct(img);
        return 0;
    }

    char *path = shift_args(&argc, &argv);
    if (strcmp(path, "--animate") == 0) {
        char *path = shift_args(&argc, &argv);
        while (argc > 0) {
            printf("\x1b[H"); // move cursor to top left
            if (!print_img_file(path)) return 1;
            path = shift_args(&argc, &argv);
        }
        return 0;
    }
    if (!print_img_file(path)) return 1;
}
