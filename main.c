#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    printf("Compiler Standard Number: %d\n", __STDC__);
    printf("Compiler Standard Version Number: %ld\n", __STDC_VERSION__);

    printf("argc = %d\n", argc);

    for (int i = 0; i < argc; ++i) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    return EXIT_SUCCESS;
}
