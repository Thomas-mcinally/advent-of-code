#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define STEP_LIMIT 10
#define GRAPH_WIDTH 11

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

size_t count_twin_positions_even_nr_of_shifts(size_t remaining_steps){
    //assumes ROWS = COLS = GRAPH_WIDTH
    //assumes GRAPH_WIDTH is an odd nr
    size_t max_shifts = remaining_steps / GRAPH_WIDTH;
    size_t twin_positions = 0;

    for (int i=2; i<=max_shifts; i+=2) twin_positions += (i+1)*2;
    return twin_positions;
}
size_t count_twin_positions_odd_nr_of_shifts(size_t remaining_steps){
    //assumes ROWS = COLS = GRAPH_WIDTH
    //assumes GRAPH_WIDTH is an odd nr
    //assumes positioned on an invalid position originally, with remaining steps
    size_t max_shifts = remaining_steps / GRAPH_WIDTH;
    size_t twin_positions = 0;

    for (int i=1; i<=max_shifts; i+=2) twin_positions += (i+1)*2;
    return twin_positions;
}
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
            if (cur.r<0 || cur.c < 0 || hmgeti(seen, cur)>=0 || grid[cur.r%ROWS][cur.c%COLS] == '#') continue;
            hmput(seen, cur, steps_taken);

            Point p1 = {(cur.r+1)%ROWS, (cur.c)%COLS};
            Point p2 = {(cur.r-1)%ROWS, (cur.c)%COLS};
            Point p3 = {(cur.r)%ROWS, (cur.c + 1)%COLS};
            Point p4 = {(cur.r)%ROWS, (cur.c - 1)%COLS};
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

    size_t part1_count = 0;
    for (int i=0; i<hmlen(seen); i++){
        size_t remaining_steps = STEP_LIMIT - seen[i].value;
        if (remaining_steps % 2 == 0) part1_count++;
    }

    printf("part1 result: %zu\n", part1_count);

    size_t part2_count = 0;
    for (int i=0; i<hmlen(seen); i++){
        size_t remaining_steps = STEP_LIMIT - seen[i].value;
        if (remaining_steps % 2 == 0) part2_count++;

        if ((GRAPH_WIDTH%2==1) && (remaining_steps%2==1)){
            // If shift an odd nr of times then we are on a valid position
            part2_count += count_twin_positions_odd_nr_of_shifts(remaining_steps);
        }
        else if ((GRAPH_WIDTH%2==1) && (remaining_steps%2==0)){
            // If shift an even nr of times then we are on an valid position
            part2_count += count_twin_positions_even_nr_of_shifts(remaining_steps);
        }
    }

    printf("part2 result: %zu\n", part2_count);

    return 0;
}

// Part2: 
// There is a straight horisontal channel through input that goes through start position
// Therefore, If can reach (r,c) in n steps, can reach (r,c+COLS) in n+COLS steps

// Also, there is a straight vertical channel through input that goes through start position
// Therefore, If can reach (r,c) in n steps, can reach (r+ROWS,c) in n+ROWS steps

// so, for every valid pos (r,c) we can calculate the number of valid "twin" positions. 
// -- Can reach (r+ROWS,c) in n+ROWS steps. Since n is a valid nr of steps, n+ROWS is an invalid number of steps, since ROWS is odd.


// ROWS = COLS = x
// (r,c) is valid
// (r+x,c) is invalid
// (r+2*x,c) is valid
// (r+3*x,c) is invalid

// (r+x, c+x) is valid
// (r+x, c+2*x) is invalid
// (r+2*x, c+x) is invalid
// (r+2*x, c+2*x) is valid

// We have a grid of size (2*26501366)^2
// Figure out how many valid positions there are in the original grid. and calculate the number of valid "twin positions" reachable using the remaining steps


// given a pos (r,c) reachable in s steps
// remaining_steps = STEP_LIMIT - s
// (a+b) * x <= remaining_steps
// (a+b) % 2 = 0
// a and b are integers
// How permutations (a,b) satisfy the above equation?



// y * x <= remaining_steps
// how many even y exist?
// Maybe there is a nice formula to find permutations (a,b) from valid y value?



// 18446744073709551615 (max llui - for reference)
// 153901049660277 too low
// 306697130449377 too low also
