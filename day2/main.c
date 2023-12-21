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

    int result = 0;
    int power = 0;

    for (int i = 0; i < lineCount; i++)
    {
        int game_id = 0;
        int j = 5;
        while (lines[i][j] != ':')
        {
            game_id = game_id * 10 + (lines[i][j] - '0');
            j++;
        }
        j += 2;

        int game_max_red_count = 0;
        int game_max_green_count = 0;
        int game_max_blue_count = 0;

        while (lines[i][j] != '\n')
        {
            int cur_count = 0;
            while (lines[i][j] != ' ')
            {
                cur_count = cur_count * 10 + (lines[i][j] - '0');
                j++;
            }
            j++;
            if (strncmp(&lines[i][j], "red", 3) == 0)
            {
                game_max_red_count = cur_count > game_max_red_count ? cur_count : game_max_red_count;
                j += 3;
            }
            else if (strncmp(&lines[i][j], "green", 5) == 0)
            {
                game_max_green_count = cur_count > game_max_green_count ? cur_count : game_max_green_count;
                j += 5;
            }
            else if (strncmp(&lines[i][j], "blue", 4) == 0)
            {
                game_max_blue_count = cur_count > game_max_blue_count ? cur_count : game_max_blue_count;
                j += 4;
            }
            while (lines[i][j] == ' ' || lines[i][j] == ',' || lines[i][j] == ';')
            {
                j++;
            }
        }
    if (game_max_red_count <= 12 && game_max_green_count <= 13 && game_max_blue_count <= 14)
    {
        result += game_id;
    }
    power += game_max_red_count * game_max_green_count * game_max_blue_count;
    free(lines[i]);
    }
    free(lines);
    
    printf("%i\n", result);
    printf("%i\n", power);
    return 0;
}

// task1 ans: 2278
// task2 ans: 67953