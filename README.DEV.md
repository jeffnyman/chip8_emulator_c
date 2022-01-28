# Development Notes

This document will keep track of the evolution of the project in terms of specific milestones that new C developers will likely strive for on any project.

I started by printing the `__STDC__`. This is a macro is used to confirm the compiler standard. Generally it holds the value 1 which means that the compiler conforms to ISO Standard C. Then I also printed the `__STDC_VERSION__`. This macro holds the C Standard's version number in the form _yyyymmL_ where _yyyy_ and _mm_ are the year and month of the Standard version. This signifies which version of the C Standard the compiler conforms to. The value 199409L signifies the C89 standard amended in 1994. The value 199901L signifies the C99 standard. The value 201112L signifies the 2011 revision of the C standard. Finally 201710L specifies the 2017 revision of the C standard.

The initial compilation is simple:

```
gcc main.c -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wmissing-prototypes -Wshadow -o chip8
```

One of the first things I knew I needed to deal with was the concept of a byte. I wanted to see what would match up with the concept of a byte from a C data type. I tried this:

```
char char_type;
printf("Size of char: %zu byte\n", sizeof(char_type));
```

On some implementations of gcc, I got the following:

```
unknown conversion type character 'z' in format [-Wformat=]
```

After a lot of searching, I found that you could add the following to the gcc compiler:

```
-D__USE_MINGW_ANSI_STDIO
```

So my compile command became:

```
gcc main.c -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wmissing-prototypes -Wshadow -D__USE_MINGW_ANSI_STDIO -o chip8
```

What that did was show me that they C `char` type would work as one byte. This obviously works because a byte is simply a structure or data type capable of storing an 8-bit unsigned integer. Thus a simple way to represent a byte is to create a type definition for one using a char, which is usually 8-bits in length, as my example test logic showed me. Thus this represents a single byte of memory in the CHIP-8.

The other concept to focus on is a word. A word is two bytes put together; in other words, a word is a 16-bit unsigned integer. The reason for having this is that instructions in the CHIP-8 are two bytes. And you often want to access either the high or low 8-bits individually. It's certainly possible to use a byte mask and shift values to accomplish that, an effective and expressive approach is to design a structure that will allow that type of access relatively easily. A way to do that:

```c++
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
```

The union essentially defines a word by saying there are two components. The first component is a `WORD`, which is an unsigned short integer, which is 16-bits long. That represents a full instruction in CHIP-8, for example. The second component is a structure called a `BYTE` that has high and low components in it.

So let's say you have a word called `opcode`. To access the full 16-bit value, you would use `opcode.WORD`. To access the high 8-bit value of the word, you would use `opcode.BYTE.high`. To access the low 8-bit value of the word, you would use `w.BYTE.low`.

The `#ifdef BIGENDIAN` statement is way of dealing with byte ordering. In machines that deal with data larger than 8-bits, there are two ways to store the data. The most significant byte (MSB) can be stored in the first memory location, or it can be stored last. For example, if you have the 16-bit value `$FFEE`, the most significant byte is `$FF`, and the least significant byte is `$EE`. In memory, two locations (say 54 and 55) are used to represent this value. The endianness of the architecture determines what memory location the MSB is stored in.

For big-endian machines, `$FF` would be stored in location 54, while `$EE` would be stored in location 55. It would be stored as `$FFEE`. With little-endian machines, the locations are reversed: `$EE` would be stored in location 54, while `$FF` would be stored in location 55. It would be stored as `$EEFF`.

Most of us will be developing on x86-based systems, which are little-endian, and thus the 16-bit values end up being stored with the MSB in the last memory position. The CHIP-8, however, is a big-endian architecture, which means the MSB would be stored in the first memory position. This means that on a little-endian machine the 16-bit value `$FFEE` would be stored as `$EEFF` in memory. So let's say we had made the above union struct just this:

```c++
struct {
    byte high, low;
} BYTE;
```

The problem there is that if we then if ran the emulator on a little-endian platform (which most people will be doing), that value read back would have `high` as `$EE` and `low` as `$FF`, since the structure in memory is nothing more than a 16-bit value that would follow the byte ordering of the architecture. By adding the `#ifdef` in with no environmental pre-processor flags defined, the structure is set to correctly resolve this byte-order discrepancy, and would resolve low as `$EE` and high as `$FF`.

So the purpose of the `#ifdef BIGENDIAN` would be if you were planning to run the emulator on a big-endian architecture. You would want to supply that in the CFLAGS variable as `make CFLAGS=-DBIGENDIAN`. Since the byte-ordering of the CHIP-8 would then match the byte-ordering of the host platform, no translation would be needed when accessing the memory structure, since the 16-bit value of `$FFEE` would already be stored as `$FFEE` in memory; meaning, the 16-bit byte order would be the same on both platforms.

## Memory

The CHIP-8 has a memory and in order to do anyhting with it, you have to establish that memory. The memory should be 4 kB (4 kilobytes or 4096 bytes) large. CHIP-8's index register and program counter can only address 12 bits which, as it turns out, is 4096 addresses.

This is interesting because the index register, program counter and stack entries are all actually 16 bits long. In theory this means that they could increment beyond 4 kB of memory addresses. In practice, no CHIP-8 ROM programs (that I'm aware of) do that. The early computers running CHIP-8 usually had less than 4 kB of RAM anyway.

All of the memory is RAM and should be considered to be writable. This is because CHIP-8 ROM programs can, and do, modify themselves during execution.

In my case, I put my `byte` to use:

```c++
byte* memory;
```

Memory, in my context, will be represented as a global variable that can be used in the form of a pointer to a malloc'd block of bytes. What this means is that a ROM program will essentially be loaded up as a big block of memory.
