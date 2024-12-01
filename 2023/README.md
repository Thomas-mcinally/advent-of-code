# advent-of-code-2023

## Scripts
Build and run:
- `clang main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `clang main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

Run tests in all subdirectories
- `find . -name 'tests.sh' -exec bash {} \;`
