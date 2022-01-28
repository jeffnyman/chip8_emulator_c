#ifndef CHIP8_H_
#define CHIP8_H_

typedef unsigned char byte;

typedef union {
    unsigned short int WORD;

    struct {
#ifdef BIGENDIAN
        byte high, low;
#else
        byte low, high;
#endif
    } BYTE;
} word;

// prototypes

char* parse_arguments(int, char*[]);

#endif
