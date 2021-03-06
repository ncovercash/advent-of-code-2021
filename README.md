# Advent Of Code 2021

These are my ~~not great~~ Advent of Code 2021 scripts. These are all written in C++ and, at a minimum, require the C++11 standard (and some C++20).

This code was often written for speed, not readability or maintainability. Please keep this in mind as you try to navigate the mess!

## Explain Yourself

Each day of code has an associated `md` file for an explanation of my thought process.

Other questions:

- Why did I chose C++? Nice standard library, I guess, but no real reason.
- Why do I mix `printf` and `cout` so much? Chaos. Just kidding -- in most cases, `cout` is fairly elegant and the modern stream syntax is rather neat. However, when something is dense with a lot of variables, `printf` is much more compact.

## Compilation

To compile these scripts, use the Makefile:

```sh
make # compile all sources
make -j4 # compile all sources, using four threads (recommended)
make all # alias for above
make 03-2 # compile part 2 of day 3
make clean # clean up all compiled sources
```

## Running

These scripts assume that the input data is stored as a file in the same directory with the day's name. For example, day two code would require `02.txt` be present.

To run these, simply use `./02-1.out` (or `./02-1.exe`, as applicable).
