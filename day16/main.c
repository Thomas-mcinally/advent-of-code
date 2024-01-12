#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

const int DOWN = 1 << 0;
const int UP = 1 << 1;
const int RIGHT = 1 << 2;
const int LEFT = 1 << 3;

void dfs(char **grid, int ROWS, int COLS, int *visited, int cur_r, int cur_c, int direction)
{
    if (cur_r < 0 || cur_r >= ROWS || cur_c < 0 || cur_c >= COLS || visited[cur_r*COLS + cur_c]&direction)
        return;

    visited[cur_r*COLS + cur_c] |= direction;

    if (grid[cur_r][cur_c] == '.')
    {
        int next_r, next_c;
        if (direction == DOWN)
            next_r = cur_r + 1, next_c = cur_c;
        else if (direction == UP)
            next_r = cur_r - 1, next_c = cur_c;
        else if (direction == RIGHT)
            next_r = cur_r, next_c = cur_c + 1;
        else if (direction == LEFT)
            next_r = cur_r, next_c = cur_c - 1;
        dfs(grid, ROWS, COLS, visited, next_r, next_c, direction);
        return;
    }
    if (grid[cur_r][cur_c] == '/')
    {
        int next_r, next_c;
        int next_direction;
        if (direction == DOWN){
            next_r = cur_r;
            next_c = cur_c - 1;
            next_direction = LEFT;
        }
        else if (direction == UP){
            next_r = cur_r;
            next_c = cur_c + 1;
            next_direction = RIGHT;
        }
        else if (direction == RIGHT){
            next_r = cur_r - 1;
            next_c = cur_c;
            next_direction = UP;
        }
        else if (direction == LEFT){
            next_r = cur_r + 1;
            next_c = cur_c;
            next_direction = DOWN;
        }
        dfs(grid, ROWS, COLS, visited, next_r, next_c, next_direction);
        return;
    }

    if (grid[cur_r][cur_c] == '\\')
    {
        int next_r, next_c;
        int next_direction;
        if (direction == DOWN){
            next_r = cur_r, next_c = cur_c + 1;
            next_direction = RIGHT;
        }
        else if (direction == UP){
            next_r = cur_r, next_c = cur_c - 1;
            next_direction = LEFT;
        }
        else if (direction == RIGHT){
            next_r = cur_r + 1, next_c = cur_c;
            next_direction = DOWN;
        }
        else if (direction == LEFT){
            next_r = cur_r - 1, next_c = cur_c;
            next_direction = UP;
        }
        dfs(grid, ROWS, COLS, visited, next_r, next_c, next_direction);
        return;
    }

    if (grid[cur_r][cur_c] == '|')
    {
        if (direction==LEFT || direction==RIGHT)
        {
            dfs(grid, ROWS, COLS, visited, cur_r + 1, cur_c, DOWN);
            dfs(grid, ROWS, COLS, visited, cur_r - 1, cur_c, UP);
        }
        else if (direction==UP)
            dfs(grid, ROWS, COLS, visited, cur_r - 1, cur_c, UP);
        else if (direction==DOWN)
            dfs(grid, ROWS, COLS, visited, cur_r + 1, cur_c, DOWN);

        return;
    }

    if (grid[cur_r][cur_c] == '-')
    {
        if (direction==UP || direction==DOWN)
        {
            dfs(grid, ROWS, COLS, visited, cur_r, cur_c + 1, RIGHT);
            dfs(grid, ROWS, COLS, visited, cur_r, cur_c - 1, LEFT);
        }
        else if (direction==LEFT)
            dfs(grid, ROWS, COLS, visited, cur_r, cur_c - 1, LEFT);
        else if (direction==RIGHT)
            dfs(grid, ROWS, COLS, visited, cur_r, cur_c + 1, RIGHT);
        return;
    }
}

int find_energized_tiles_given_starting_pos(char **grid, int ROWS, int COLS, int start_r, int start_c, int start_direction)
{
    int *visited = calloc(ROWS * COLS, sizeof(int));
    dfs(grid, ROWS, COLS, visited, start_r, start_c, start_direction);

    int count = 0;
    for (int i = 0; i < ROWS * COLS; i++)
    {
        if (visited[i])
            count++;
    }
    free(visited);
    return count;
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

    printf("part1 sol: %d\n", find_energized_tiles_given_starting_pos(grid, ROWS, COLS, 0, 0, RIGHT));

    int max_count = 0;
    for (int r = 0; r < ROWS; r++)
    {
        max_count = max(max_count, find_energized_tiles_given_starting_pos(grid, ROWS, COLS, r, 0, RIGHT));
        max_count = max(max_count, find_energized_tiles_given_starting_pos(grid, ROWS, COLS, r, COLS - 1, LEFT));
    }
    for (int c = 0; c < COLS; c++)
    {
        max_count = max(max_count, find_energized_tiles_given_starting_pos(grid, ROWS, COLS, 0, c, DOWN));
        max_count = max(max_count, find_energized_tiles_given_starting_pos(grid, ROWS, COLS, ROWS - 1, c, UP));
    }

    printf("part2 sol: %d\n", max_count);

    for (int r = 0; r < ROWS; r++)
        free(grid[r]);
    free(grid);
}

// Two potential major improvements
// 1. Simplify DFS - overly complex logic to determine next move
// 2. Simplify Visited check inside DFS