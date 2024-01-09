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


    size_t i = 0;
    size_t current_value = 0;
    size_t total_value = 0;
    while (file_contents[i] != '\0')
    {
        if (file_contents[i] == '\n')
        {
            printf("found unexpected newline at index: %zu\n", i);
            exit(1);
        }
        else if (file_contents[i] == ',') {
            total_value += current_value;
            current_value = 0;
        }
        else {
            current_value += file_contents[i];
            current_value *= 17;
            current_value %= 256;

        }

        i += 1;
    }
    total_value += current_value;

    printf("part1 sol: %zu\n", total_value);

}