// number of pairs = n(n-1)/2. 9*8/2 = 72/2 = 36
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

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
    int *galaxy_counts = calloc(ROWS*COLS, sizeof(int));
    Point *galxy_positions = NULL;
    for (int r=0;r<ROWS;r++){
        for (int c=0;c<COLS;c++){
            if (grid[r][c] == '.') continue;
            col_is_not_empty[c] = 1;
            row_is_not_empty[r] = 1;
            galaxy_counts[r*COLS + c] = galaxy_count;
            galaxy_count++;
            Point galaxy_position = {r, c, 0};
            arrput(galxy_positions, galaxy_position);
        }
    }
    size_t total_distance = 0;
    for (int i=0; i<arrlen(galxy_positions); i++){
        int *seen_points = calloc(ROWS*COLS, sizeof(int));
        Point starting_galaxy = galxy_positions[i];

        Point *queue = NULL;
        arrput(queue, starting_galaxy);

        while (arrlen(queue) > 0){
            Point cur = queue[0];
            arrdel(queue, 0);
            if (cur.r<0 || cur.c<0 || cur.r>=ROWS || cur.c >= COLS || seen_points[cur.r*COLS + cur.c] == 1) continue;
            seen_points[cur.r*COLS + cur.c] = 1;

            if (grid[cur.r][cur.c] == '#' && galaxy_counts[cur.r*COLS + cur.c] > galaxy_counts[starting_galaxy.r*COLS + starting_galaxy.c]){
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
    }
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

    // BFS starting from each galaxy
    // once find a galaxy with higher galaxy_count -> increment total
    // determine empty rows and empty cols beforehand
    // if grid[r][c] == '.' && empty row


    // part2 -> expands more than just double

    // if total_rows = R, total_cols = C, number of galaxies = G
    // total edges ~ R*C*4/2 = E
    // BFS from each galaxy -> O(G*E)
    // Dijkstras from each galaxy -> O(G*Elog(E))

    // Impossible to find shortcut,have to cross the same columns and rws for all shortest paths, so dijkstras is overkill