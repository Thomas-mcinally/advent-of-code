#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct
{
    int r;
    int c;
    int steps_taken;
}Point;

Point find_starting_position(char **grid, int ROWS, int COLS){
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLS; c++){
            if(grid[r][c] == 'S'){
                Point p = {r, c, 0};
                return p;
            }
        }
    }
    fprintf(stderr, "Could not find starting position\n");
    exit(1);
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

    int *seen = calloc(ROWS*COLS, sizeof(int));
    Point *queue = NULL;
    arrput(queue, starting_position);
    while (1){
        Point cur = queue[0];
        if (cur.steps_taken == 65) break;
        arrdel(queue, 0); //TODO - make this efficient.

        if (cur.r < 0 || cur.r >= ROWS || cur.c < 0 || cur.c >= COLS || grid[cur.r][cur.c] == '#' || seen[cur.r*COLS + cur.c]) continue;
        seen[cur.r*COLS + cur.c] = cur.steps_taken;

        Point p1 = {cur.r+1, cur.c, cur.steps_taken+1};
        Point p2 = {cur.r-1, cur.c, cur.steps_taken+1};
        Point p3 = {cur.r, cur.c+1, cur.steps_taken+1};
        Point p4 = {cur.r, cur.c-1, cur.steps_taken+1};
        arrput(queue, p1);
        arrput(queue, p2);
        arrput(queue, p3);
        arrput(queue, p4);
    }

    int count = 0;
    for (int i=0; i<ROWS*COLS; i++){
        if (seen[i] && (seen[i]%2 == 0)) count++;
    }

    printf("Part 1: %d\n", count);

    return 0;
}
