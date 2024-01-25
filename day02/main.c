#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines, file_path);

    int part1_solution = 0;
    int part2_solution = 0;

    for (int i = 0; i < lineCount-1; i++)
    {
        int j = 5;
        int game_id = extract_number_from_string_starting_from(lines[i], &j);
        j += 2;

        int game_max_red_count = 0;
        int game_max_green_count = 0;
        int game_max_blue_count = 0;

        while (lines[i][j] != '\0')
        {
            int count = extract_number_from_string_starting_from(lines[i], &j);
            j++;
            if (strncmp(&lines[i][j], "red", 3) == 0)
            {
                game_max_red_count = count > game_max_red_count ? count : game_max_red_count;
                j += 3;
            }
            else if (strncmp(&lines[i][j], "green", 5) == 0)
            {
                game_max_green_count = count > game_max_green_count ? count : game_max_green_count;
                j += 5;
            }
            else if (strncmp(&lines[i][j], "blue", 4) == 0)
            {
                game_max_blue_count = count > game_max_blue_count ? count : game_max_blue_count;
                j += 4;
            }
            while (lines[i][j] == ' ' || lines[i][j] == ',' || lines[i][j] == ';') j++;
        }
    if (game_max_red_count <= 12 && game_max_green_count <= 13 && game_max_blue_count <= 14)
    {
        part1_solution += game_id;
    }
    part2_solution += game_max_red_count * game_max_green_count * game_max_blue_count;
    free(lines[i]);
    }
    free(lines);
    
    printf("part1 solution: %i\n", part1_solution);
    printf("part2 solution: %i\n", part2_solution);
    return 0;
}
