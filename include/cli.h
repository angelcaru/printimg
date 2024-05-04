#ifndef CLI_H
#define CLI_H

void usage(const char *program_name); // user-defined

char *shift_args(int *argc, char ***argv);
char *shift_expect(int *argc, char ***argv, const char *arg_name, const char *program_name);

#endif // CLI_H

#ifdef CLI_IMPL

#include <stdlib.h>
#include <stdio.h>

char *shift_args(int *argc, char ***argv) {
    --*argc;
    char *ret = **argv;
    ++*argv;
    return ret;
}
char *shift_expect(int *argc, char ***argv, const char *arg_name, const char *program_name) {
    if (*argc == 0) {
        usage(program_name);
        fprintf(stderr, "%s: ERROR: Missing argument: %s\n", program_name, arg_name);
        exit(1);
    }
    char *ret = **argv;
    --*argc;
    ++*argv;
    return ret;
}

#endif // CLI_IMPL
