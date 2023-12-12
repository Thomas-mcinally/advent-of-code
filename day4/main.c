#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int read_file_to_lines(char ***lines){
    int MAX_LINE_LENGTH = 256;
    FILE *file = fopen("./input.txt", "r");
    int lineCount = 0;

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        *lines = realloc(*lines, (lineCount + 1) * sizeof(char *));
        (*lines)[lineCount] = malloc(strlen(buffer) + 1);

        strcpy((*lines)[lineCount], buffer);
        lineCount++;
    }
    fclose(file);
    return lineCount;
}


int main()
{
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines);


    int total_score = 0;
    for (int i = 0; i < lineCount; i++)
    {
        int seen_nums[101] = {0}; 

        int cur_num = 0;
        for (int j = 10; j < 40; j++)
        {
            if (isdigit(lines[i][j]))
            {
                cur_num *= 10;
                cur_num += lines[i][j] - '0';
            }
            else if (lines[i][j] == ' ')
            {
                seen_nums[cur_num] = 1;
                cur_num = 0;
            }
        }


        cur_num = 0;
        int cur_score = 0;
        for (int j = 42; lines[i][j] != '\0'; j++)
        {
            if (isdigit(lines[i][j]))
            {
                cur_num *= 10;
                cur_num += lines[i][j] - '0';
            }
            else if (lines[i][j] == ' ')
            {
                if (cur_num != 0 && seen_nums[cur_num])
                {
                    if (cur_score == 0) cur_score = 1;
                    else cur_score *= 2;
                }
                cur_num = 0;
            }
        }
        if (cur_num != 0 && seen_nums[cur_num] && cur_score == 0) cur_score = 1;
        if (cur_num != 0 && seen_nums[cur_num] && cur_score != 0) cur_score *= 2;
        total_score += cur_score;

    }
    printf("Part1: %i \n", total_score);
}