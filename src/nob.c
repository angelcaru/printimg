#define NOB_IMPLEMENTATION
#include "nob.h"


typedef struct {
    char *src;
    char *out;
} Program;

#define OPT_LEVEL "0"
bool compile_program(Program program) {
    Nob_Cmd cmd = {0};
    nob_cmd_append(&cmd, "cc");
    nob_cmd_append(&cmd, "-Wall", "-Wextra", "-O"OPT_LEVEL);
    nob_cmd_append(&cmd, "-o", program.out);
    nob_cmd_append(&cmd, program.src);
    nob_cmd_append(&cmd, "-lm");
    return nob_cmd_run_sync(cmd);
}

Program programs[] = {
    { .src = "src/pim.c", .out = "build/pim" },
    { .src = "src/rim.c", .out = "build/rim" },
    { .src = "src/rect.c", .out = "build/rect" },
    { .src = "src/wim.c", .out = "build/wim" },
};

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);

    if (!nob_mkdir_if_not_exists("build")) return 1;

    for (int i = 0; i < NOB_ARRAY_LEN(programs); i++) {
        if (!compile_program(programs[i])) return 1;
    }

    nob_shift_args(&argc, &argv);
    if (argc >= 1 && strcmp(nob_shift_args(&argc, &argv), "run") == 0) {
        char *tool = nob_shift_args(&argc, &argv);
        char *tool_path = nob_temp_sprintf("./build/%s", tool);

        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, tool_path);
        nob_da_append_many(&cmd, argv, argc);
        if (!nob_cmd_run_sync(cmd)) return 1;
    }

    return 0;
}
