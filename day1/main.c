#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"
// The newly-improved calibration document consists of lines of text; each line originally contained a 
// specific calibration value that the Elves now need to recover. On each line, the calibration value can 
// be found by combining the first digit and the last digit (in that order) to form a single two-digit number.

// What is the sum of all the calibration values?
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines, file_path);

    int count = 0;
    // Iterate over each line
    for (int i = 0; i < lineCount-1; i++)
    {
        int j = 0;
        while (1)
        {
            if (isdigit(lines[i][j]))
            {
                count += (lines[i][j] - '0') * 10;
                break;
            }

            j++;
        }

        j = strlen(lines[i]) - 1;
        while (1)
        {
            if (isdigit(lines[i][j]))
            {
                count += lines[i][j] - '0';
                break;
            }
            j--;
        }
        free(lines[i]);
    }
    free(lines);
    printf("Part1 sol: %i", count);
    return 0;
}

