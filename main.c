#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "chip8.h"

/**
 * Read command line to parse arguments.
 * 
 * Currently the only argument is the required
 * ROM program file to load.
 */
char* parse_arguments(int argc, char* argv[]) {
    int arg;
    char* filename = NULL;

    for (arg = 1; arg < argc; arg++) {
        if (filename == NULL) {
            filename = argv[arg];
        }
    }

    if (filename == NULL) {
        printf("ROM file not specified.\n");
        exit(EXIT_FAILURE);
    }

    return filename;
}

int main(int argc, char* argv[]) {
    printf("Compiler Standard Number: %d\n", __STDC__);
    printf("Compiler Standard Version Number: %ld\n", __STDC_VERSION__);

    printf("argc = %d\n", argc);

    for (int i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    char char_type;
    printf("Size of char: %zu byte\n", sizeof(char_type));
    printf("Size of byte: %zu byte\n", sizeof(byte));

    char* rom_file;
    rom_file = parse_arguments(argc, argv);

    assert(rom_file != NULL);

    return EXIT_SUCCESS;
}
