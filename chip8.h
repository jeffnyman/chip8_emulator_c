#ifndef CHIP8_H_
#define CHIP8_H_

#define MEMORY 0x1000 /* 4 kilobyte (4096 byte) memory size */

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

byte* memory;

// prototypes

char* parse_arguments(int, char*[]);

#endif
