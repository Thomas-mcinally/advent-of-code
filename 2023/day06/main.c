#include <stdio.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int number_of_ways_to_win(int time_limit, int record_distance)
{
    int l = 0;
    int r = time_limit;
    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        int distance_traveled = (time_limit - mid) * mid;
        if (distance_traveled > record_distance)
            r = mid - 1;
        else
            l = mid + 1;
    }
    return time_limit - r * 2 - 1;
}

int main(int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);


    int *times = NULL;
    int *distances = NULL;

    int i = strchr(lines[0], ':') - lines[0] + 1;
    while (lines[0][i] != '\0') {
        while (lines[0][i] == ' ') i++;
        arrput(times, extract_number_from_string_starting_from(lines[0], &i));
        }

    i = strchr(lines[1], ':') - lines[1] + 1;
    while (lines[1][i] != '\0') {
        while (lines[1][i] == ' ') i++;
        arrput(distances, extract_number_from_string_starting_from(lines[1], &i));
    }
    int part1_result = 1;
    for (int i = 0; i < arrlen(times); i++)
    {
        part1_result *= number_of_ways_to_win(times[i], distances[i]);
    }

    printf("Part1 sol: %d\n", part1_result);


    arrfree(times);
    arrfree(distances);
    for(int i=0; i<linecount; i++) free(lines[i]);
    free(lines);
    
    return 0;
}
