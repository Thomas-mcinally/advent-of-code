#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "aoc_lib.h"


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines, file_path);

    int *i_to_copies = malloc(lineCount * sizeof(int));
    for (int i = 0; i < lineCount; i++) i_to_copies[i] = 1;
    
    int total_score = 0;
    int total_scratchcards = 0;
    for (int i = 0; i < lineCount; i++)
    {
        int is_winning_number[101] = {0}; // max num is 99


        int j = strchr(lines[i], ':') - lines[i] + 1;
        while (lines[i][j] != '|') 
        {
            while (lines[i][j] == ' ') j++;
            int next_num = extract_number_from_string_starting_from(lines[i], &j);
            is_winning_number[next_num] = 1;
        }
        j++;

        int matches_found = 0;
        while (lines[i][j] != '\0')
        {
            while (lines[i][j] == ' ') j++;
            int next_num = extract_number_from_string_starting_from(lines[i], &j);
            if (is_winning_number[next_num]) matches_found += 1;
        }

        if (matches_found != 0) total_score += pow(2, matches_found - 1);


        total_scratchcards += i_to_copies[i];
        for (int r = i+1; r < i+1+matches_found && r < lineCount; r++) i_to_copies[r] += i_to_copies[i];

        free(lines[i]);
    }
    free(lines);
    free(i_to_copies);
    printf("Part1 sol: %i \n", total_score);
    printf("Part2 sol: %i \n", total_scratchcards);
}