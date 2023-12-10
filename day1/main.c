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
    FILE *file = fopen("./input.txt", "r");

    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines);

    int count = 0;
    // Iterate over each line
    for (int i = 0; i < lineCount; i++)
    {
        int j = 0;
        while (1)
        {
            if (isdigit(lines[i][j]))
            {
                count += (lines[i][j] - '0') * 10;
                break;
            }

            j += 1;
        }

        j = strlen(lines[i]) - 1;
        while (1)
        {
            if (isdigit(lines[i][j]))
            {
                count += lines[i][j] - '0';
                break;
            }
            j -= 1;
        }
        free(lines[i]);
    }
    free(lines);
    printf("%i", count);
    return 0;
}
