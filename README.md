# advent-of-code-2023
- My first time writing code in C!

## Todo
- Refactor days - At least the ones highlighted below
- Add tests
- Add github action that builds and tests code
- Get feedback from experienced C developer
- Redo in C++ to see main differences?

- Days 1-7: Use dynamic arrays where this helpsa keep code clean
- Day1 part2: Improve TC by using Trie
- Day9: https://www.reddit.com/r/adventofcode/comments/18eiv3z/2023_day_9_how_to_solve_it_by_only_iterating/
- Day11: Improve BFS by using queue data structure. Currently when i queue.popleft(), it is an O(N) operation.
    - Could also possibly improve by using a level-order traversal?
- Day17: Make more optimal dijkstras by using a heap (instead of just arra that is sorted every iteration)
- Day 21: Improve BFS by using queue data structure
- Day 24 part2: Refactor to only use C - perhaps use the geometric solution instead of Z3 solver.

## Scripts
Build and run:
- `gcc main.c ../libs/aoc_lib.c -I ../libs && ./a.out input.txt`

Build and run debugger:
- `gcc main.c ../libs/aoc_lib.c -I ../libs -g && lldb a.out input.txt`

Remove binaries:
- `find . -name "*.out" -type f -delete`
