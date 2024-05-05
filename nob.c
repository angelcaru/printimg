#define NOB_IMPLEMENTATION
#include "nob.h"


typedef struct {
    char *src;
    char *out;
} Program;

#define OPT_LEVEL "0"
void cflags(Nob_Cmd *cmd) {
    nob_cmd_append(cmd, "-I./include", "-I.");
    nob_cmd_append(cmd, "-Wall", "-Wextra", "-O"OPT_LEVEL);
}

void compile_program_cmd(Program program, Nob_Cmd *cmd) {
    nob_cmd_append(cmd, "cc");
    cflags(cmd);
    nob_cmd_append(cmd, "-o", program.out);
    nob_cmd_append(cmd, program.src, "build/libs.o");
    nob_cmd_append(cmd, "-lm");
}

bool compile_program_sync(Program program) {
    Nob_Cmd cmd = {0};
    compile_program_cmd(program, &cmd);
    return nob_cmd_run_sync(cmd);
}

Nob_Proc compile_program_async(Program program) {
    Nob_Cmd cmd = {0};
    compile_program_cmd(program, &cmd);
    return nob_cmd_run_async(cmd);
}

Program programs[] = {
    { .src = "src/pim.c", .out = "build/pim" },
    { .src = "src/rim.c", .out = "build/rim" },
    { .src = "src/wim.c", .out = "build/wim" },
    { .src = "src/istats.c", .out = "build/istats" },
    { .src = "src/rect.c", .out = "build/rect" },
    { .src = "src/circle.c", .out = "build/circle" },
    { .src = "src/crop.c", .out = "build/crop" },
    { .src = "src/blank.c", .out = "build/blank" },
};

const char *libs[] = {
    "include/stb_image.h",
    "include/stb_image_write.h",
    "include/cli.h",
    "include/image.h",
    "include/libs.c",
    "nob.h",
};
size_t lib_count = NOB_ARRAY_LEN(libs);

int main(int argc, char **argv) {
    NOB_GO_REBUILD_URSELF(argc, argv);
    nob_shift_args(&argc, &argv);

    bool parallel;
    if (argc != 0 && strcmp(argv[0], "--parallelize") == 0) {
        parallel = true;
        nob_shift_args(&argc, &argv);
    }

    if (!nob_mkdir_if_not_exists("build")) return 1;

    if (nob_needs_rebuild("build/libs.o", libs, lib_count)) {
        Nob_Cmd cmd = {0};
        nob_cmd_append(&cmd, "cc");
        cflags(&cmd);
        nob_cmd_append(&cmd, "-c", "include/libs.c");
        nob_cmd_append(&cmd, "-o", "build/libs.o");
        if (!nob_cmd_run_sync(cmd)) return 1;
    }

    Nob_Procs procs = {0};
    for (int i = 0; i < NOB_ARRAY_LEN(programs); i++) {
        if (parallel) {
            Nob_Proc proc = compile_program_async(programs[i]);
            nob_da_append(&procs, proc);
        } else {
            if (!compile_program_sync(programs[i])) return 1;
        }
    }

    if (parallel) {
        nob_procs_wait(procs);
    }

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
