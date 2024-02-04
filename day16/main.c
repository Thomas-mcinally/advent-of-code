#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

const int DOWN = 1 << 0;
const int UP = 1 << 1;
const int RIGHT = 1 << 2;
const int LEFT = 1 << 3;

void dfs(char **grid, int ROWS, int COLS, int *visited, int cur_r, int cur_c, int inbound_dir)
{
    if (cur_r < 0 || cur_r >= ROWS || cur_c < 0 || cur_c >= COLS || visited[cur_r*COLS + cur_c]&inbound_dir)
        return;

    visited[cur_r*COLS + cur_c] |= inbound_dir;

    int outgoing_dir = 0;
    switch (grid[cur_r][cur_c]) {
        case '.':
            outgoing_dir = inbound_dir;
            break;
        case '/':
            if      (inbound_dir == RIGHT) outgoing_dir = UP;
            else if (inbound_dir == LEFT)  outgoing_dir = DOWN;
            else if (inbound_dir == DOWN)  outgoing_dir = LEFT;
            else if (inbound_dir == UP)    outgoing_dir = RIGHT;
            break;
        case '\\':
            if      (inbound_dir == RIGHT) outgoing_dir = DOWN;
            else if (inbound_dir == LEFT)  outgoing_dir = UP;
            else if (inbound_dir == DOWN)  outgoing_dir = RIGHT;
            else if (inbound_dir == UP)    outgoing_dir = LEFT;
            break;
        case '-':
            if      (inbound_dir == RIGHT) outgoing_dir = RIGHT;
            else if (inbound_dir == LEFT)  outgoing_dir = LEFT;
            else if (inbound_dir == DOWN)  outgoing_dir = LEFT | RIGHT;
            else if (inbound_dir == UP)    outgoing_dir = LEFT | RIGHT;
            break;
        case '|':
            if      (inbound_dir == RIGHT) outgoing_dir = UP | DOWN;
            else if (inbound_dir == LEFT)  outgoing_dir = UP | DOWN;
            else if (inbound_dir == DOWN)  outgoing_dir = DOWN;
            else if (inbound_dir == UP)    outgoing_dir = UP;
            break;
    }

    if (outgoing_dir & RIGHT) dfs(grid, ROWS, COLS, visited, cur_r, cur_c+1, RIGHT);
    if (outgoing_dir & LEFT) dfs(grid, ROWS, COLS, visited, cur_r, cur_c-1, LEFT);
    if (outgoing_dir & DOWN) dfs(grid, ROWS, COLS, visited, cur_r+1, cur_c, DOWN);
    if (outgoing_dir & UP) dfs(grid, ROWS, COLS, visited, cur_r-1, cur_c, UP);
}

int find_energized_tiles_given_starting_pos(char **grid, int ROWS, int COLS, int start_r, int start_c, int start_direction)
{
    int *visited = (int*)calloc(ROWS * COLS, sizeof(int));
    dfs(grid, ROWS, COLS, visited, start_r, start_c, start_direction);

    int count = 0;
    for (int i = 0; i < ROWS * COLS; i++) if (visited[i]) count++;
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

    printf("Part1 sol: %d\n", find_energized_tiles_given_starting_pos(grid, ROWS, COLS, 0, 0, RIGHT));

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

    printf("Part2 sol: %d\n", max_count);

    for (int r = 0; r < ROWS; r++) free(grid[r]);
    free(grid);
}
