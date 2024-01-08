#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    int r;
    int c;
    size_t distance_travelled;
} Point;

size_t calculate_total_distance(int expansion_factor, char **grid, int ROWS, int COLS){
    int galaxy_count = 0;
    int *col_is_not_empty = calloc(COLS, sizeof(int));
    int *row_is_not_empty = calloc(ROWS, sizeof(int));
    int *galaxy_labels = calloc(ROWS*COLS, sizeof(int));
    Point *galxy_positions = NULL;
    for (int r=0;r<ROWS;r++){
        for (int c=0;c<COLS;c++){
            if (grid[r][c] == '.') continue;
            col_is_not_empty[c] = 1;
            row_is_not_empty[r] = 1;
            galaxy_labels[r*COLS + c] = galaxy_count;
            galaxy_count++;
            Point galaxy_position = {r, c, 0};
            arrput(galxy_positions, galaxy_position);
        }
    }
    Point *queue = NULL;
    size_t total_distance = 0;
    for (int i=0; i<galaxy_count; i++){
        int *seen_points = calloc(ROWS*COLS, sizeof(int));

        Point starting_galaxy = galxy_positions[i];
        arrput(queue, starting_galaxy);
        while (arrlen(queue) > 0){
            Point cur = queue[0];
            arrdel(queue, 0);
            if (cur.r<0 || cur.c<0 || cur.r>=ROWS || cur.c >= COLS || seen_points[cur.r*COLS + cur.c] == 1) continue;
            seen_points[cur.r*COLS + cur.c] = 1;

            if (grid[cur.r][cur.c] == '#' && galaxy_labels[cur.r*COLS + cur.c] > galaxy_labels[starting_galaxy.r*COLS + starting_galaxy.c]){
                total_distance += cur.distance_travelled;
            }
            int row_increment = row_is_not_empty[cur.r] ? 1 : expansion_factor;
            int col_increment = col_is_not_empty[cur.c] ? 1 : expansion_factor;

            Point next_point_right = {cur.r+1, cur.c, cur.distance_travelled+row_increment};
            Point next_point_left = {cur.r-1, cur.c, cur.distance_travelled+row_increment};
            Point next_point_up = {cur.r, cur.c+1, cur.distance_travelled+col_increment};
            Point next_point_down = {cur.r, cur.c-1, cur.distance_travelled+col_increment};
            arrput(queue, next_point_right);
            arrput(queue, next_point_left);
            arrput(queue, next_point_up);
            arrput(queue, next_point_down);
        }
        free(seen_points);
    }

    arrfree(galxy_positions);
    arrfree(queue);
    free(col_is_not_empty);
    free(row_is_not_empty);
    free(galaxy_labels);
    return total_distance;
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

    
    printf("part1: %zu\n", calculate_total_distance(2, grid, ROWS, COLS));
    printf("part2: %zu\n", calculate_total_distance(1000000, grid, ROWS, COLS));

}

    // Approaches considered:
    // 1. BFS from each galaxy
    // 2. Dijkstras from each galaxy
    // Dijkstras is not more optimal because: have to cross the same columns and rws for all shortest paths. 
    // wherever you cross a row/column, it yields the same result, so BFS will always find the optimal path.
    // Dijkstras would also find optimal path, but has higher time-complexity
