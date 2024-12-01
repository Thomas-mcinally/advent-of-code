#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "aoc_lib.h"

size_t number_of_ways_to_win(size_t time_limit, size_t record_distance)
{
    size_t l = 0;
    size_t r = time_limit;
    while (l <= r)
    {
        size_t mid = l + (r - l) / 2;
        size_t distance_traveled = (time_limit - mid) * mid;
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

    char *time_cursor = strchr(lines[0], ':') + 1;
    char *distance_cursor = strchr(lines[1], ':') + 1;
    while (*time_cursor == ' ') time_cursor++;
    while (*distance_cursor == ' ') distance_cursor++;
    size_t part_2_time = extract_number_from_string(time_cursor);
    size_t part_2_distance = extract_number_from_string(distance_cursor);
    size_t part2_result = number_of_ways_to_win(part_2_time, part_2_distance);
    printf("Part2 sol: %zu\n", part2_result);

    for(int i=0; i<linecount; i++) free(lines[i]);
    free(lines);
    return 0;
}
