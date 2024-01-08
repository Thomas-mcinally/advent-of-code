// process inputs into 2d grid

// total = 0
// for c in COLS:
//   end_r = 0
//   for r in ROWS:
//       if grid[r][c] == '#': end_r = r+1
//       if grid[r][c] == '0': total += 10-end_r; end_r++;

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **grid = NULL;
    int ROWS = read_file_to_lines(&grid, file_path);
    int COLS = strlen(grid[0]);

    size_t total = 0;
    for (int c=0; c<COLS; c++){
        int end_r = 0;
        for (int r=0; r<ROWS; r++){
            if (grid[r][c] == '#') end_r = r+1;
            else if (grid[r][c] == 'O') {
                total += (ROWS-end_r); 
                end_r++;
            }
        }
    }
    printf("part1 sol: %zu\n", total);

}
