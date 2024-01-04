#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct
{
    int r;
    int c;
} Point;

Point find_starting_position(char **grid, int ROWS, int COLS)
{
    Point starting_position = {-1, -1};
    for (int r = 0; r < ROWS; r++)
    {
        for (int c = 0; c < COLS; c++)
        {
            if (grid[r][c] == 'S')
            {
                starting_position.r = r;
                starting_position.c = c;
                return starting_position;
            }
        }
    }
    return starting_position;
}

int distance_to_end_of_loop(char **grid, int ROWS, int COLS, Point pos, int *visited, Point prev_pos)
{
    if (pos.r < 0 || pos.r >= ROWS || pos.c < 0 || pos.c >= COLS || grid[pos.r][pos.c] == '.' || visited[pos.r * COLS + pos.c])
    {
        return -1;
    }
    if (grid[pos.r][pos.c] == 'S')
    {
        visited[pos.r * COLS + pos.c] = 2;
        return 0;
    }

    visited[pos.r * COLS + pos.c] = 1;

    int res;
    if (grid[pos.r][pos.c] == '|' && prev_pos.r < pos.r)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '|' && prev_pos.r > pos.r)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '-' && prev_pos.c < pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '-' && prev_pos.c > pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'L' && prev_pos.c == pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'L' && prev_pos.c != pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'J' && prev_pos.c == pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'J' && prev_pos.c != pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '7' && prev_pos.c == pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '7' && prev_pos.c != pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'F' && prev_pos.c == pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'F' && prev_pos.c != pos.c)
    {
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, pos);
    }

    if (res != -1)
    {
        visited[pos.r * COLS + pos.c] = 2;
        return res + 1;
    }
    return -1;
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

    Point starting_position = find_starting_position(grid, ROWS, COLS);

    Point first_positions[4] = {
        {starting_position.r + 1, starting_position.c},
        {starting_position.r - 1, starting_position.c},
        {starting_position.r, starting_position.c + 1},
        {starting_position.r, starting_position.c - 1}};

    int *visited = malloc(ROWS * COLS * sizeof(int)); // 0->univisited, 1-> visited, 2-> visited and in loop
    int loop_length;
    for (int i = 0; i < 4; i++)
    {
        loop_length = distance_to_end_of_loop(grid, ROWS, COLS, first_positions[i], visited, starting_position);

        if (loop_length != -1)
        {
            break;
        }
    }
    printf("Part1: %d\n", (loop_length + 1) / 2);

    int total_enclosed_land = 0;
    for (int r = 0; r < ROWS; r++)
    {
        char last_corner = '.';
        bool is_enclosed = 0;
        for (int c = 0; c < COLS; c++)
        {
            if (visited[r*COLS + c] != 2 && is_enclosed) {
                total_enclosed_land++;
                }
            if (grid[r][c] != '-' && visited[r*COLS + c] == 2) {
                if (
                    !(grid[r][c] == 'J' && last_corner == 'F') &&
                    !(grid[r][c] == '7' && last_corner == 'L')
                ) is_enclosed = !is_enclosed;

                if (grid[r][c] != '|') last_corner = grid[r][c];
            }
        }
    }
    printf("Part2: %d\n", total_enclosed_land);
}

// For part2:
// can determine if a point is enclosed by looking at all cells to left (or right)
// Only care about cells that are a part of large circle
// everytime cross border we become enclosed/unenclosed
// Everytime find opening corner, it WILL BE FOLLOWED by a closing corner BEFORE any cell which is not part of circle
// If the second corner is in opposite direction of the first (e.g. L---7), we don't consider it a bordercrossing