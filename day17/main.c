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

// pseudocode
// visited = set()
// q = priorityqueue() // (total_weight, r, c, dir, dir_count)
// q.push((0, 0, 0, 0, 0))
// visited.add((0, 0, 0, 0))

// while q:
// total_w, r, c, dir, dir_count = q.pop()
// if r<0 || r>=ROWS || c<0 || c>=COLS || (r,c,dir,dir_count) in visited:
//  continue
// visited.add((r,c,dir,dir_count))
// if (r,c) == (ROWS-1, COLS-1):
//  return total_w

// recursive case
// next_dirs = [RIGHT, LEFT, UP, DOWN]
// next_dirs.remove(opposite_dir)
// if dir_count == 3:
    // next_dirs.remove(dir)

// if RIGHT in next_dirs: 
        // next_dir_count = dir_count + 1 if dir == RIGHT else 1
        // q.append((total_w + grid[r][c+1], r, c+1, RIGHT, next_dir_count))
// if LEFT in next_dirs:
        // next_dir_count = dir_count + 1 if dir == LEFT else 1
        // q.append((total_w + grid[r][c-1], r, c-1, LEFT, next_dir_count)) 
// if UP in next_dirs:
        // next_dir_count = dir_count + 1 if dir == UP else 1
        // q.append((total_w + grid[r-1][c], r-1, c, UP, next_dir_count))   
// if DOWN in next_dirs:
        // next_dir_count = dir_count + 1 if dir == DOWN else 1
        // q.append((total_w + grid[r+1][c], r+1, c, DOWN, next_dir_count)) 
}