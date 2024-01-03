#include <string.h>
#include <stdio.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
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
    if (pos.r < 0 || pos.r >= ROWS || pos.c < 0 || pos.c >= COLS || grid[pos.r][pos.c] == '.'|| visited[pos.r * COLS + pos.c])
    {
        return -1;
    }
    if (grid[pos.r][pos.c] == 'S')
    {
        return 0;
    }

    visited[pos.r * COLS + pos.c] = 1;

    int res;
    if (grid[pos.r][pos.c] == '|' && prev_pos.r < pos.r){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '|' && prev_pos.r > pos.r){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '-' && prev_pos.c < pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '-' && prev_pos.c > pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'L' && prev_pos.c == pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'L' && prev_pos.c != pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'J' && prev_pos.c == pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'J' && prev_pos.c != pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r - 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '7' && prev_pos.c == pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c - 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == '7' && prev_pos.c != pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'F' && prev_pos.c == pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r, pos.c + 1}, visited, pos);
    }
    else if (grid[pos.r][pos.c] == 'F' && prev_pos.c != pos.c){
        res = distance_to_end_of_loop(grid, ROWS, COLS, (Point){pos.r + 1, pos.c}, visited, pos);
    }


    if (res != -1){
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
        {starting_position.r, starting_position.c - 1}
    };
    
    int *visited = malloc(ROWS * COLS * sizeof(int)); // 0->univisited, 1-> visited and not in loop, 2-> visited and in loop
    int loop_length;
    for (int i = 0; i < 4; i++)
    {
        loop_length = distance_to_end_of_loop(grid, ROWS, COLS, first_positions[i], visited, starting_position);
        if (loop_length != -1) break;
    }
    


    printf("Part1: %d\n", (loop_length + 1) / 2);
}