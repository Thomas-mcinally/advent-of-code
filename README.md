# advent-of-code-2023

## Todo
- Add tests for all days
- Standardise output format for all days
- Remove need for newline in input (many of early days i did this for some reason)

## Scripts
Build and run:
- `gcc main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `gcc main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

Remove binaries:
- `find . -name "*.out" -type f -delete`

Run tests in all subdirectories
- `find . -name 'tests.sh' -exec bash {} \;`
