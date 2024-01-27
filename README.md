# advent-of-code-2023
- My first time writing code in C!

## Todo
- Add tests
- Add github action that builds and tests code

## Scripts
Build and run:
- `gcc main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `gcc main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

Remove binaries:
- `find . -name "*.out" -type f -delete`
