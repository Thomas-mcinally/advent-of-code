#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void tilt_north(char **grid, int ROWS, int COLS)
{
    for (int c=0; c<COLS; c++){
        int end_r = 0;
        for (int r=0; r<ROWS; r++){
            if (grid[r][c] == '#') end_r = r+1;
            else if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[end_r][c] = 'O';
                end_r++;
            }
        }
    }
}
void tilt_south(char **grid, int ROWS, int COLS)
{
    for (int c=0; c<COLS; c++){
        int end_r = ROWS-1;
        for (int r=ROWS-1; r>=0; r--){
            if (grid[r][c] == '#') end_r = r-1;
            else if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[end_r][c] = 'O';
                end_r--;
            }
        }
    }
}
void tilt_west(char **grid, int ROWS, int COLS)
{
    for (int r=0; r<ROWS; r++){
        int end_c = 0;
        for (int c=0; c<COLS; c++){
            if (grid[r][c] == '#') end_c = c+1;
            else if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[r][end_c] = 'O';
                end_c++;
            }
        }
    }
}
void tilt_east(char **grid, int ROWS, int COLS)
{
    for (int r=0; r<ROWS; r++){
        int end_c = COLS-1;
        for (int c=COLS-1; c>=0; c--){
            if (grid[r][c] == '#') end_c = c-1;
            else if (grid[r][c] == 'O') {
                grid[r][c] = '.';
                grid[r][end_c] = 'O';
                end_c--;
            }
        }
    }
}

size_t calculate_north_beam_load(char **grid, int ROWS, int COLS){
    size_t total = 0;
    for (int c=0; c<COLS; c++){
        for (int r=0; r<ROWS; r++){
            if (grid[r][c] == 'O') {
                total += (ROWS-r); 
            }
        }
    }
    return total;
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

    tilt_north(grid, ROWS, COLS);
    printf("part1 sol: %zu\n", calculate_north_beam_load(grid, ROWS, COLS));

    // TODO: Dynamically determine cycle length instead of hardcoding
    // Observed cycle length of 18 (from experimenting with data)
    // Therefore, after cycle 1 000 000 000 should have same num as after cycle 1 000 000 000 - 18
    // And also 1 000 000 000 - 18*55555500 = 1000
    for (int i=1; i<1001; i++){ 
        tilt_north(grid, ROWS, COLS);
        tilt_west(grid, ROWS, COLS);
        tilt_south(grid, ROWS, COLS);
        tilt_east(grid, ROWS, COLS);
    }

    printf("part2 sol: %zu\n", calculate_north_beam_load(grid, ROWS, COLS));
}   
