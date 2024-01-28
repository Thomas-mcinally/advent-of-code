# advent-of-code-2023

## Todo
- Remove need for newline in input (many of early days i did this for some reason)
- Fix github workflow - currently failing
- Make general solution to day25, and add test

## Scripts
Build and run:
- `gcc main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `gcc main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

Run tests in all subdirectories
- `find . -name 'tests.sh' -exec bash {} \;`
