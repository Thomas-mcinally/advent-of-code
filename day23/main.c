#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

//DFS backtracking solution
void backtrack(char **grid, int ROWS, int COLS, int r, int c, size_t pathlength, size_t *longest_pathlength){
    if(r<0 || r>=ROWS || c<0 || c>=COLS || grid[r][c] == '#') return;

    if (r == ROWS-1 && c == COLS-2){
        *longest_pathlength = max(pathlength, *longest_pathlength);
        return;
    }

    if (grid[r][c] != '.'){
        int next_r, next_c;
        if (grid[r][c] == '>') next_r = r, next_c = c+1;
        else if (grid[r][c] == '<') next_r = r, next_c = c-1;
        else if (grid[r][c] == '^') next_r = r-1, next_c = c;
        else if (grid[r][c] == 'v') next_r = r+1, next_c = c;
        char temp = grid[r][c];
        grid[r][c] = '#';
        backtrack(grid, ROWS, COLS, next_r, next_c, pathlength+1, longest_pathlength);
        grid[r][c] = temp;
    }
    else if (grid[r][c] == '.') {
        grid[r][c] = '#';
        backtrack(grid, ROWS, COLS, r, c+1, pathlength+1, longest_pathlength);
        backtrack(grid, ROWS, COLS, r, c-1, pathlength+1, longest_pathlength);
        backtrack(grid, ROWS, COLS, r+1, c, pathlength+1, longest_pathlength);
        backtrack(grid, ROWS, COLS, r-1, c, pathlength+1, longest_pathlength);
        grid[r][c] = '.';
    }
}

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

    size_t longest_pathlength = 0;
    backtrack(grid, ROWS, COLS, 0, 1, 0, &longest_pathlength);
    printf("part1 sol: %zu\n", longest_pathlength);

}