#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define STEP_LIMIT_PART_2 26501365
#define STEP_LIMIT_PART_1 64
#define GRAPH_WIDTH 131

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
        if (steps_taken == STEP_LIMIT_PART_2+1) break;
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
        if (seen[i].value > STEP_LIMIT_PART_1) continue;
        size_t remaining_steps = STEP_LIMIT_PART_1 - seen[i].value;
        if (remaining_steps % 2 == 0) part1_count++;
    }

    printf("Part1 sol: %zu\n", part1_count);

    size_t even_corners = 0;
    size_t odd_corners = 0;
    size_t even_full = 0;
    size_t odd_full = 0;

    for (int i=0; i<hmlen(seen); i++){
        if (seen[i].value % 2 == 0 && seen[i].value > 65) even_corners++;
        if (seen[i].value % 2 == 1 && seen[i].value > 65) odd_corners++;
        if (seen[i].value % 2 == 0) even_full++;
        if (seen[i].value % 2 == 1) odd_full++;
    }

    size_t N = (STEP_LIMIT_PART_2 - GRAPH_WIDTH/2) / GRAPH_WIDTH;
    assert(N == 202300); // should be this for real AOC input

    size_t part2_count = (N+1)*(N+1)*odd_full + N*N*even_full - (N+1)*odd_corners + N*even_corners;
    printf("Part2 sol: %zu\n", part2_count);
    return 0;
}

// Part2 solved geometrically, see inspo here:
// https://www.reddit.com/r/adventofcode/comments/18nol3m/2023_day_21_a_geometric_solutionexplanation_for/



// Discarded part2 idea:
// Also based on a lot of same observations as the solution i went with in the end (described in the reddit post)
// Based on the stepcounts of reachable positions in the original graph
// Can reach the equivalent (twin) reachable positions in extended graph by "Shifting" in cardinal direction
// i.e. if (r,c) is valid, (r+2W, c) is also valid. Can reach this by first shifting down 2W and then taking same path as did in original graph

//Discarded because got too low answer. Was low because:
    // Tiles in the start square which are only reachable by going outside the start square and back in again
    // Tiles on the outer edge of the reachable area. Dont have enough steps if shift and then backtrack, but have enough if dont backtrack
// Couldnt find a way to calculate how many tiles i was missing in a general way
    // Maybe the amount i am off by varies in a regular way with my input stepcount?
    // If i can get a hold of Valid sols for a range of stepcounts, could figure it out? 
    // Couldnt find a list of valid sols
    //Might be able to do it now that i have solved it in a different way

    // size_t part2_count = 0;
    // for (int i=0; i<hmlen(seen); i++){
    //     size_t remaining_steps = STEP_LIMIT - seen[i].value;
    //     if (remaining_steps % 2 == 0) part2_count++;

    //     if ((GRAPH_WIDTH%2==1) && (remaining_steps%2==1)){
    //         // If shift an odd nr of times then we are on a valid position
    //         part2_count += count_twin_positions_odd_nr_of_shifts(remaining_steps);
    //     }
    //     else if ((GRAPH_WIDTH%2==1) && (remaining_steps%2==0)){
    //         // If shift an even nr of times then we are on an valid position
    //         part2_count += count_twin_positions_even_nr_of_shifts(remaining_steps);
    //     }
    // }

    // size_t count_twin_positions_even_nr_of_shifts(size_t remaining_steps){
    // // given a position in the original grid, reachable with remaining steps
    // // how many twin positions can you reach if shift directly up/down before moving from centre?
    // size_t max_shifts = remaining_steps / GRAPH_WIDTH;
    // size_t twin_positions = 0;

    // for (int i=2; i<=max_shifts; i+=2) twin_positions += i*4;
    // return twin_positions;
    // }
    // size_t count_twin_positions_odd_nr_of_shifts(size_t remaining_steps){
    //     size_t max_shifts = remaining_steps / GRAPH_WIDTH;
    //     size_t twin_positions = 0;

    //     for (int i=1; i<=max_shifts; i+=2) twin_positions += i*4;
    //     return twin_positions;
    // }
