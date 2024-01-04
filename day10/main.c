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

Point next_position_east(Point pos, char **grid, int COLS, int ROWS, int *visited)
{
    if (pos.c == COLS - 1)
        return (Point){-1, -1};
    int potential_next_c = pos.c + 1;

    while (potential_next_c < COLS && visited[pos.r * COLS + potential_next_c] == 2)
    {
        if (grid[pos.r][potential_next_c] == 'L')
        {
            potential_next_c++;
            while (grid[pos.r][potential_next_c] == '-')
                potential_next_c++;
            if (grid[pos.r][potential_next_c] != 'J')
                break;
            potential_next_c++;
        }
        else if (grid[pos.r][potential_next_c] == 'F')
        {
            potential_next_c++;
            while (grid[pos.r][potential_next_c] == '-')
                potential_next_c++;
            if (grid[pos.r][potential_next_c] != '7')
                break;
            potential_next_c++;
        }
        else
            break;
    }
    if (potential_next_c < COLS && visited[pos.r * COLS + potential_next_c] == 0)
        return (Point){pos.r, potential_next_c};
    return (Point){-1, -1};
}
Point next_position_west(Point pos, char **grid, int COLS, int ROWS, int *visited)
{
    if (pos.c == 0)
        return (Point){-1, -1};
    int potential_next_c = pos.c - 1;

    while (potential_next_c >= 0 && visited[pos.r * COLS + potential_next_c] == 2)
    {
        if (grid[pos.r][potential_next_c] == 'J')
        {
            potential_next_c--;
            while (grid[pos.r][potential_next_c] == '-')
                potential_next_c--;
            if (grid[pos.r][potential_next_c] != 'L')
                break;
            potential_next_c--;
        }
        else if (grid[pos.r][potential_next_c] == '7')
        {
            potential_next_c--;
            while (grid[pos.r][potential_next_c] == '-')
                potential_next_c--;
            if (grid[pos.r][potential_next_c] != 'F')
                break;
            potential_next_c--;
        }
        else
            break;
    }

    if (potential_next_c >= 0 && visited[pos.r * COLS + potential_next_c] == 0)
        return (Point){pos.r, potential_next_c};
    return (Point){-1, -1};
}
Point next_position_south(Point pos, char **grid, int COLS, int ROWS, int *visited)
{
    if (pos.r == ROWS - 1)
        return (Point){-1, -1};
    int potential_next_r = pos.r + 1;

    while (potential_next_r < ROWS && visited[potential_next_r * COLS + pos.c] == 2)
    {
        if (grid[potential_next_r][pos.c] == 'F')
        {
            potential_next_r++;
            while (grid[potential_next_r][pos.c] == '|')
                potential_next_r++;
            if (grid[potential_next_r][pos.c] != 'L')
                break;
            potential_next_r++;
        }
        else if (grid[potential_next_r][pos.c] == '7')
        {
            potential_next_r++;
            while (grid[potential_next_r][pos.c] == '|')
                potential_next_r++;
            if (grid[potential_next_r][pos.c] != 'J')
                break;
            potential_next_r++;
        }
        else
            break;
    }

    if (potential_next_r < ROWS && visited[potential_next_r * COLS + pos.c] == 0)
        return (Point){potential_next_r, pos.c};
    return (Point){-1, -1};
}
Point next_position_north(Point pos, char **grid, int COLS, int ROWS, int *visited)
{
    if (pos.r == 0)
        return (Point){-1, -1};
    int potential_next_r = pos.r - 1;

    while (potential_next_r >= 0 && visited[potential_next_r * COLS + pos.c] == 2)
    {
        if (grid[potential_next_r][pos.c] == 'J')
        {
            potential_next_r--;
            while (grid[potential_next_r][pos.c] == '|')
                potential_next_r--;
            if (grid[potential_next_r][pos.c] != '7')
                break;
            potential_next_r--;
        }
        else if (grid[potential_next_r][pos.c] == 'L')
        {
            potential_next_r--;
            while (grid[potential_next_r][pos.c] == '|')
                potential_next_r--;
            if (grid[potential_next_r][pos.c] != 'F')
                break;
            potential_next_r--;
        }
        else
            break;
    }

    if (potential_next_r >= 0 && visited[potential_next_r * COLS + pos.c] == 0)
        return (Point){potential_next_r, pos.c};
    return (Point){-1, -1};
}

void explore_unenclosed_land(Point pos, char **grid, int ROWS, int COLS, int *visited)
{
    if (pos.r < 0 || pos.r >= ROWS || pos.c < 0 || pos.c >= COLS || visited[pos.r * COLS + pos.c])
        return;

    visited[pos.r * COLS + pos.c] = 1;
    Point next_west = next_position_west(pos, grid, COLS, ROWS, visited);
    Point next_east = next_position_east(pos, grid, COLS, ROWS, visited);
    Point next_north = next_position_north(pos, grid, COLS, ROWS, visited);
    Point next_south = next_position_south(pos, grid, COLS, ROWS, visited);

    explore_unenclosed_land(next_west, grid, ROWS, COLS, visited);
    explore_unenclosed_land(next_east, grid, ROWS, COLS, visited);
    explore_unenclosed_land(next_north, grid, ROWS, COLS, visited);
    explore_unenclosed_land(next_south, grid, ROWS, COLS, visited);

    // diagonals
    explore_unenclosed_land((Point){pos.r - 1, pos.c - 1}, grid, ROWS, COLS, visited);
    explore_unenclosed_land((Point){pos.r - 1, pos.c + 1}, grid, ROWS, COLS, visited);
    explore_unenclosed_land((Point){pos.r + 1, pos.c - 1}, grid, ROWS, COLS, visited);
    explore_unenclosed_land((Point){pos.r + 1, pos.c + 1}, grid, ROWS, COLS, visited);
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

    // grid[starting_position.r][starting_position.c] = 'J'; // TODO: Do something like this to make more robust
    printf("Part1: %d\n", (loop_length + 1) / 2);

    for (int i = 0; i < ROWS * COLS; i++)
        if (visited[i] == 1)
            visited[i] = 0;

    for (int c = 0; c < COLS; c++)
    {
        explore_unenclosed_land((Point){0, c}, grid, ROWS, COLS, visited);
        explore_unenclosed_land((Point){ROWS - 1, c}, grid, ROWS, COLS, visited);
    }
    for (int r = 0; r < ROWS; r++)
    {
        explore_unenclosed_land((Point){r, 0}, grid, ROWS, COLS, visited);
        explore_unenclosed_land((Point){r, COLS - 1}, grid, ROWS, COLS, visited);
    }
    int total_enclosed_land = 0;
    for (int i = 0; i < ROWS * COLS; i++)
        if (visited[i] == 0)
            total_enclosed_land++;
    printf("Part2: %d\n", total_enclosed_land);
}

// 724 too high
// 693 wrong

// works on all test cases in question text, but all of these are simple and dont have complex "sneaking" cases
// Think issue might be when "sneaking" past multiple sets of straight pipe.
// e.g. have considered .L----JL----J.
// What about
// 7
// |
// |
// L------J
