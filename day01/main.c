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

    int count = 0;

    for (int i = 0; i < lineCount; i++)
    {
        int j = 0;
        while (!isdigit(lines[i][j])) j++;
        count += (lines[i][j] - '0') * 10;

        j = strlen(lines[i]) - 1;
        while (!isdigit(lines[i][j])) j--;
        count += lines[i][j] - '0';

        free(lines[i]);
    }
    free(lines);
    printf("Part1 sol: %i\n", count);
    return 0;
}
