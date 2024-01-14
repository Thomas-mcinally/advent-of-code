# advent-of-code-2023
- My first time writing code in C!
- Some inspo for C code: https://github.com/stevemolloy/AOC2023/tree/main
- Library for hashtable and dynamic arrays: https://github.com/stevemolloy/AOC2023/blob/68fadbce0cf4a735e20b371241571e95769a766b/day_08/src/stb_ds.h#L4
- Inspo for concise code (sols written in python): https://github.com/xHyroM/aoc/tree/main/2023



TODO, to make this project professional:
- Add tests
- Add github actions that build and test code
- Improved folder structure and refactor code to be professional
- Get feedback from experienced C developer
- Redo in C++ to see main differences?
- Install a good debugger - to help with segmentation faults.

TODO - implement optimal solutions:
- Day9: https://www.reddit.com/r/adventofcode/comments/18eiv3z/2023_day_9_how_to_solve_it_by_only_iterating/
- Day11: Improve BFS by using queue data structure. Currently when i queue.popleft(), it is an O(N) operation.
- Day17: Make more optimal dijkstras by using a heap (instead of just arra that is sorted every iteration)


Useful scripts:
- gcc main.c ../libs/aoc_lib.c -I ../libs
