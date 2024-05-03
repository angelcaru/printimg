#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define IMAGE_IMPL
#include "image.h"

#include <sys/ioctl.h>
#include <stdbool.h>
#include <time.h>

void usage(const char *program_name) {
    printf("Usage: %s <filename>\n", program_name);
}

void set_bg(Color c) {
    printf("\x1b[48;2;%d;%d;%dm", c.r, c.g, c.b);
}

void reset_term(void) {
    printf("\x1b[0m");
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

char *shift_args(int *argc, char ***argv) {
    --*argc;
    char *ret = **argv;
    ++*argv;
    return ret;
}

void print_img_struct(Image img) {
    int termwidth, termheight;
    get_term_size(&termwidth, &termheight);

    float ystep = img.height / (termheight * 0.8);
    float xstep = ystep / 2;

    for (float y = 0; y < img.height; y += ystep) {
        for (float x = 0; x < img.width; x += xstep) {
            Color c = img.data[(int)y * img.stride + (int)x];

            if (c.a < 255) {
                c = color_lerp(ASSUMED_BG, c, c.a / 255.0f);
            }
            set_bg(c);
            printf(" ");
        }
        reset_term();
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
    shift_args(&argc, &argv);

    if (argc == 0) {
        Image img;
        if (!img_read(&img, stdin)) return 1;
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
