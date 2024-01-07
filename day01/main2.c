#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

int read_string_digit(char *string, bool is_start)
{
    if (strncmp(is_start?string:string-3, "zero", 4) == 0) return 0;
    if (strncmp(is_start?string:string-2, "one", 3) == 0) return 1;
    if (strncmp(is_start?string:string-2, "two", 3) == 0) return 2;
    if (strncmp(is_start?string:string-4, "three", 5) == 0) return 3;
    if (strncmp(is_start?string:string-3, "four", 4) == 0) return 4;
    if (strncmp(is_start?string:string-3, "five", 4) == 0) return 5;
    if (strncmp(is_start?string:string-2, "six", 3) == 0) return 6;
    if (strncmp(is_start?string:string-4, "seven", 5) == 0) return 7;
    if (strncmp(is_start?string:string-4, "eight", 5) == 0) return 8;
    if (strncmp(is_start?string:string-3, "nine", 4) == 0) return 9;
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
            int string_digit = read_string_digit(&lines[i][j], true);
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
            int string_digit = read_string_digit(&lines[i][j], false);
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



// Can improve time complexity by using a Trie
// Be careful with chars in middle of num that is start of other num -> cant discard all prev seen chars when new char can't be added to cur_word.
// When new_char can't be added to cur_word: 1) If can be added to prev_char, do so. 2) Else, discard all prev chars and start new word.
// for example ninine, threight, seveight
// Example implementation, in Python: https://pastebin.com/HMuKKJqQ
