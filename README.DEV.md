# Development Notes

This document will keep track of the evolution of the project in terms of specific milestones that new C developers will likely strive for on any project.

I started by printing the `__STDC__`. This is a macro is used to confirm the compiler standard. Generally it holds the value 1 which means that the compiler conforms to ISO Standard C. Then I also printed the `__STDC_VERSION__`. This macro holds the C Standard's version number in the form _yyyymmL_ where _yyyy_ and _mm_ are the year and month of the Standard version. This signifies which version of the C Standard the compiler conforms to. The value 199409L signifies the C89 standard amended in 1994. The value 199901L signifies the C99 standard. The value 201112L signifies the 2011 revision of the C standard. Finally 201710L specifies the 2017 revision of the C standard.

The initial compilation is simple:

```
gcc main.c -std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wmissing-prototypes -Wshadow -o chip8
```
