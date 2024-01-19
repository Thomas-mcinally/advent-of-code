#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define STEP_LIMIT 1000
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
    // given a position in the original grid, reachable with remaining steps
    // how many twin positions can you reach if shift directly up/down before moving from centre?
    size_t max_shifts = remaining_steps / GRAPH_WIDTH;
    size_t twin_positions = 0;

    for (int i=2; i<=max_shifts; i+=2) twin_positions += i*4;
    return twin_positions;
}
size_t count_twin_positions_odd_nr_of_shifts(size_t remaining_steps){
    size_t max_shifts = remaining_steps / GRAPH_WIDTH;
    size_t twin_positions = 0;

    for (int i=1; i<=max_shifts; i+=2) twin_positions += i*4;
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
    //doesnt work yet - solution is too low
    //my soltuion doesnt account for tiles in the very outer edges of the reachable area
    //In these positions, dont have enough steps if shift and then backtrack. Have enough if dont shift


    //see inspo
    // https://www.reddit.com/r/adventofcode/comments/18nol3m/2023_day_21_a_geometric_solutionexplanation_for/
    // https://raw.githubusercontent.com/Manitary/advent-of-code/c44838423066b3c8d446f0d94f2a19d675f2b6dc/2023/python/day21.png


    // My solution is currently too low
    // maybe i can figure out a way to predict how off i am, based on the input stepcount ?
    return 0;
}


