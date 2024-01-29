# advent-of-code-2023

## Todo
- Find out why test workflow doesnt work with ubuntu workflow runner and macos runner doesnt work with day12 tests
- Make general solution to day25, and add test

## Scripts
Build and run:
- `clang main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `clang main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

Run tests in all subdirectories
- `find . -name 'tests.sh' -exec bash {} \;`
