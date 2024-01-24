# advent-of-code-2023
- My first time writing code in C!
- Library for hashtable and dynamic arrays: https://github.com/stevemolloy/AOC2023/blob/68fadbce0cf4a735e20b371241571e95769a766b/day_08/src/stb_ds.h#L4

## Todo
- Add tests
- Add github actions that build and test code
- Improved folder structure and refactor code to be professional
- Get feedback from experienced C developer
- Redo in C++ to see main differences?

- Day9: https://www.reddit.com/r/adventofcode/comments/18eiv3z/2023_day_9_how_to_solve_it_by_only_iterating/
- Day11: Improve BFS by using queue data structure. Currently when i queue.popleft(), it is an O(N) operation.
    - Could also possibly improve by using a level-order traversal?
- Day17: Make more optimal dijkstras by using a heap (instead of just arra that is sorted every iteration)
- Day 21: Improve BFS by using queue data structure

## Scripts
Build and run:
- `gcc main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `gcc main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

 
