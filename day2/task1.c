#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
    int MAX_LINE_LENGTH = 256;
    FILE *file = fopen("./input.txt", "r");

    char **lines = NULL;
    int lineCount = 0;

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        // Allocate memory for the new line
        lines = realloc(lines, (lineCount + 1) * sizeof(char *));
        lines[lineCount] = malloc(strlen(buffer) + 1);

        strcpy(lines[lineCount], buffer);
        lineCount++;
    }
    fclose(file);
    int result = 0;

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
    }
    printf("%i", result);
    return 0;
}

// ans: 2278