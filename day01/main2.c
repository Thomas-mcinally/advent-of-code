#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

int read_string_digit(char *string, bool reverse)
{
    if (isdigit(*string)) return *string - '0';
    if (strncmp(reverse?string-3:string, "zero", 4) == 0) return 0;
    if (strncmp(reverse?string-2:string, "one", 3) == 0) return 1;
    if (strncmp(reverse?string-2:string, "two", 3) == 0) return 2;
    if (strncmp(reverse?string-4:string, "three", 5) == 0) return 3;
    if (strncmp(reverse?string-3:string, "four", 4) == 0) return 4;
    if (strncmp(reverse?string-3:string, "five", 4) == 0) return 5;
    if (strncmp(reverse?string-2:string, "six", 3) == 0) return 6;
    if (strncmp(reverse?string-4:string, "seven", 5) == 0) return 7;
    if (strncmp(reverse?string-4:string, "eight", 5) == 0) return 8;
    if (strncmp(reverse?string-3:string, "nine", 4) == 0) return 9;
    return -1;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines, file_path);

    int count = 0;

    for (int i = 0; i < lineCount-1; i++)
    {
        int j = 0;
        while (read_string_digit(&lines[i][j], false) == -1) j++;
        count += read_string_digit(&lines[i][j], false) * 10;

        j = strlen(lines[i]) - 1;
        while (read_string_digit(&lines[i][j], true) == -1) j--;
        count += read_string_digit(&lines[i][j], true);

        free(lines[i]);
    }
    free(lines);
    printf("Part2 sol: %i\n", count);
    return 0;
}
