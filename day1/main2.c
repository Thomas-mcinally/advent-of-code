#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

int read_string_digit_starting_at(char *string)
{
    if (strncmp(string, "zero", 4) == 0) return 0;
    if (strncmp(string, "one", 3) == 0) return 1;
    if (strncmp(string, "two", 3) == 0) return 2;
    if (strncmp(string, "three", 5) == 0) return 3;
    if (strncmp(string, "four", 4) == 0) return 4;
    if (strncmp(string, "five", 4) == 0) return 5;
    if (strncmp(string, "six", 3) == 0) return 6;
    if (strncmp(string, "seven", 5) == 0) return 7;
    if (strncmp(string, "eight", 5) == 0) return 8;
    if (strncmp(string, "nine", 4) == 0) return 9;
    return -1;
}
int read_reverse_string_digit_starting_at(char *string)
{
    if (strncmp(string-3, "zero", 4) == 0) return 0;
    if (strncmp(string-2, "one", 3) == 0) return 1;
    if (strncmp(string-2, "two", 3) == 0) return 2;
    if (strncmp(string-4, "three", 5) == 0) return 3;
    if (strncmp(string-3, "four", 4) == 0) return 4;
    if (strncmp(string-3, "five", 4) == 0) return 5;
    if (strncmp(string-2, "six", 3) == 0) return 6;
    if (strncmp(string-4, "seven", 5) == 0) return 7;
    if (strncmp(string-4, "eight", 5) == 0) return 8;
    if (strncmp(string-3, "nine", 4) == 0) return 9;
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
        while (1)
        {
            if (isdigit(lines[i][j]))
            {
                count += (lines[i][j] - '0') * 10;
                break;
            }
            int string_digit = read_string_digit_starting_at(&lines[i][j]);
            if (string_digit != -1)
            {
                count += string_digit * 10;
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
            int string_digit = read_reverse_string_digit_starting_at(&lines[i][j]);
            if (i==2) printf("reverse string digit result: %i\n", string_digit);
            if (string_digit != -1)
            {
                count += string_digit;
                break;
            }
            j--;
        }
        free(lines[i]);
    }
    free(lines);
    printf("Part2 sol: %i\n", count);
    return 0;
}


// PART2
// Your calculation isn't quite right. It looks like some of the digits are actually spelled out with 
// letters: one, two, three, four, five, six, seven, eight, and nine also count as valid "digits".

// Equipped with this new information, you now need to find the real first and last digit on each line. For example:

// two1nine
// eightwothree
// abcone2threexyz
// xtwone3four
// 4nineeightseven2
// zoneight234
// 7pqrstsixteen
// In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76. Adding these together produces 281.
