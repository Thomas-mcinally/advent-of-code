#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char *file_contents = read_entire_file(file_path);

    char **codes = NULL;
    int num_codes = split_string_by_delimiter_string(file_contents, ",", &codes);

    size_t total_value = 0;

    for (int i=0; i<num_codes; i++){
        size_t current_value = 0;
        int j = 0;
        while (codes[i][j] != '\0')
        {
            if (codes[i][j] == '\n')
            {
                printf("found unexpected newline at i: %d, j: %d\n", i, j);
                exit(1);
            }
            else {
                current_value += codes[i][j];
                current_value *= 17;
                current_value %= 256;

            }
            j += 1;
        }
        total_value += current_value;
    }

    printf("part1 sol: %zu\n", total_value);

}