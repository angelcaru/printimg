#include "nob.h"
#include "image.h"
#include "cli.h"
#include "stb_image.h"
#include "base64.h"

#include <sys/ioctl.h>

void usage(const char *program_name) {
    printf("Usage: %s [filename]\n", program_name);
}

#define KITTY_MESSAGE_PAYLOAD_CAP 4096

void print_img_struct(Image img) {
    //struct winsize ws;
    //ioctl(fileno(stderr), TIOCGWINSZ, &ws);
    //unsigned short width_px = ws.ws_xpixel;
    //unsigned short height_px = ws.ws_ypixel;
    assert(img.width == img.stride && "Images with stride are not yet supported");

    int base64_len;
    char *base64_data = base64(img.data, img.width * img.height * sizeof(*img.data), &base64_len);
    Nob_String_View base64_sv = nob_sv_from_parts(base64_data, base64_len);
    for (size_t chunk_idx = 0; base64_sv.count > 0; chunk_idx++) {
        bool first = chunk_idx == 0;
        bool last = base64_sv.count <= KITTY_MESSAGE_PAYLOAD_CAP;

        printf("\x1b_G");
        if (first) printf("a=T,f=32,s=%d,v=%d,t=d,", img.width, img.height);
        printf("m=%d;", last ? 0 : 1);

        Nob_String_View chunk = nob_sv_chop_left(&base64_sv, KITTY_MESSAGE_PAYLOAD_CAP);
        fwrite(chunk.data, 1, chunk.count, stdout);

        printf("\x1b\\");
    }

    printf("\n");
    free(base64_data);
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
    if (!print_img_file(path)) return 1;
}
