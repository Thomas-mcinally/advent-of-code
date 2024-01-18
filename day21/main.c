#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define STEP_LIMIT 64

typedef struct
{
    long long int r;
    long long int c;
}Point;

typedef struct
{
    Point key;
    size_t value; // stepcount of first visit
} Point_To_Stepcount_Map;

Point find_starting_position(char **grid, int ROWS, int COLS){
    for(int r = 0; r < ROWS; r++){
        for(int c = 0; c < COLS; c++){
            if(grid[r][c] == 'S'){
                Point p = {r, c};
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

    Point_To_Stepcount_Map *seen = NULL;
    Point *queue = malloc(sizeof(Point));
    queue[0] = starting_position;
    size_t queue_len = 1;
    size_t steps_taken = 0;
    while (1){
        if (steps_taken == STEP_LIMIT+1) break;
        Point *next_queue = malloc(4*queue_len*sizeof(Point));
        size_t next_queue_len = 0;
        for (size_t i=0;i<queue_len;i++){
            Point cur = queue[i];
            if (cur.r < 0 || cur.r >= ROWS || cur.c < 0 || cur.c >= COLS || grid[cur.r][cur.c] == '#' || hmgeti(seen, cur)>=0) continue;
            hmput(seen, cur, steps_taken);

            Point p1 = {cur.r+1, cur.c};
            Point p2 = {cur.r-1, cur.c};
            Point p3 = {cur.r, cur.c+1};
            Point p4 = {cur.r, cur.c-1};
            next_queue[next_queue_len++] = p1;
            next_queue[next_queue_len++] = p2;
            next_queue[next_queue_len++] = p3;
            next_queue[next_queue_len++] = p4;
        }
        free(queue);
        queue = next_queue;
        queue_len = next_queue_len;
        steps_taken++;
    }

    int count = 0;
    for (int i=0; i<hmlen(seen); i++){
        if ((seen[i].value % 2) == 0) count++;
    }

    printf("Part 1: %d\n", count);

    return 0;
}
