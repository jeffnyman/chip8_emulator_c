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
