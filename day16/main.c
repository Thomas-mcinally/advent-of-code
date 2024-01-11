#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"


void dfs(char **grid, int ROWS, int COLS, int **visited, int cur_r, int cur_c, int prev_r, int prev_c)
{
    if (cur_r < 0 || cur_r >= ROWS || cur_c < 0 || cur_c >= COLS ) 
        return;
    
    int is_travelling_down = (cur_r == prev_r + 1);
    int is_travelling_up = (cur_r == prev_r - 1);
    int is_travelling_right = (cur_c == prev_c + 1);
    int is_travelling_left = (cur_c == prev_c - 1);

    if (visited[cur_r*COLS + cur_c] != NULL && is_travelling_down && visited[cur_r*COLS + cur_c][0]) return;
    if (visited[cur_r*COLS + cur_c] != NULL && is_travelling_up && visited[cur_r*COLS + cur_c][1]) return;
    if (visited[cur_r*COLS + cur_c] != NULL && is_travelling_right && visited[cur_r*COLS + cur_c][2]) return;
    if (visited[cur_r*COLS + cur_c] != NULL && is_travelling_left && visited[cur_r*COLS + cur_c][3]) return;

    if (visited[cur_r*COLS + cur_c] == NULL){
        visited[cur_r*COLS + cur_c] = calloc(4, sizeof(int));
    }
    visited[cur_r*COLS + cur_c][0] = is_travelling_down;
    visited[cur_r*COLS + cur_c][1] = is_travelling_up;
    visited[cur_r*COLS + cur_c][2] = is_travelling_right;
    visited[cur_r*COLS + cur_c][3] = is_travelling_left;

    if (grid[cur_r][cur_c] == '.'){
        if (is_travelling_down) dfs(grid, ROWS, COLS, visited, cur_r+1, cur_c, cur_r, cur_c);
        else if (is_travelling_up) dfs(grid, ROWS, COLS, visited, cur_r-1, cur_c, cur_r, cur_c);
        else if (is_travelling_right) dfs(grid, ROWS, COLS, visited, cur_r, cur_c+1, cur_r, cur_c);
        else if (is_travelling_left) dfs(grid, ROWS, COLS, visited, cur_r, cur_c-1, cur_r, cur_c);
        return;
    }

    if (grid[cur_r][cur_c] == '|'){
        if (is_travelling_left || is_travelling_right){
            dfs(grid, ROWS, COLS, visited, cur_r+1, cur_c, cur_r, cur_c);
            dfs(grid, ROWS, COLS, visited, cur_r-1, cur_c, cur_r, cur_c);
        }
        else if (is_travelling_up) dfs(grid, ROWS, COLS, visited, cur_r-1, cur_c, cur_r, cur_c);
        else if (is_travelling_down) dfs(grid, ROWS, COLS, visited, cur_r+1, cur_c, cur_r, cur_c);

        return;
    }

    if (grid[cur_r][cur_c] == '-'){
        if (is_travelling_up || is_travelling_down){
            dfs(grid, ROWS, COLS, visited, cur_r, cur_c+1, cur_r, cur_c);
            dfs(grid, ROWS, COLS, visited, cur_r, cur_c-1, cur_r, cur_c);
        }
        else if (is_travelling_left) dfs(grid, ROWS, COLS, visited, cur_r, cur_c-1, cur_r, cur_c);
        else if (is_travelling_right) dfs(grid, ROWS, COLS, visited, cur_r, cur_c+1, cur_r, cur_c);
        return;
    }

    if (grid[cur_r][cur_c] == '/'){
        if (is_travelling_down) dfs(grid, ROWS, COLS, visited, cur_r, cur_c-1, cur_r, cur_c);
        else if (is_travelling_up) dfs(grid, ROWS, COLS, visited, cur_r, cur_c+1, cur_r, cur_c);
        else if (is_travelling_right) dfs(grid, ROWS, COLS, visited, cur_r-1, cur_c, cur_r, cur_c);
        else if (is_travelling_left) dfs(grid, ROWS, COLS, visited, cur_r+1, cur_c, cur_r, cur_c);
        return;
    }

    if (grid[cur_r][cur_c] == '\\'){

        if (is_travelling_down) dfs(grid, ROWS, COLS, visited, cur_r, cur_c+1, cur_r, cur_c);
        else if (is_travelling_up) dfs(grid, ROWS, COLS, visited, cur_r, cur_c-1, cur_r, cur_c);
        else if (is_travelling_right) dfs(grid, ROWS, COLS, visited, cur_r+1, cur_c, cur_r, cur_c);
        else if (is_travelling_left) dfs(grid, ROWS, COLS, visited, cur_r-1, cur_c, cur_r, cur_c);
        return;
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

    int **visited = malloc(ROWS * COLS * sizeof(int *));
    dfs(grid, ROWS, COLS, visited, 0, 0, 0, -1); // start top left travelling right

    int count = 0;
    for (int r=0; r<ROWS; r++){
        for (int c=0; c<COLS; c++){
            if(visited[r*COLS + c] != NULL) count += 1;
        }
    }
    printf("part1 sol: %d\n", count);

}
