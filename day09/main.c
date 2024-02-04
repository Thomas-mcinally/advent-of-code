#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int extrapolate_next_val(int *nums, int num_count, bool is_part1)
{
    int *diff_array = (int*)calloc(num_count - 1, sizeof(int));
    bool is_next_arr_all_zeroes = true;
    for (int i = 1; i < num_count; i++)
    {
        int diff = nums[i] - nums[i - 1];
        if (diff != 0)
            is_next_arr_all_zeroes = false;
        diff_array[i - 1] = diff;
    }

    int next_result = is_next_arr_all_zeroes ? next_result = 0 : extrapolate_next_val(diff_array, num_count - 1, is_part1);
    free(diff_array);

    if (is_part1)
        return nums[num_count - 1] + next_result;
    else
        return nums[0] - next_result;
}

int **split_string_lines_into_int_lines(char **string_lines, int linecount, char *separator)
// output nums must be freed by caller
{
    int **nums = NULL;
    for (int i = 0; i < linecount; i++)
    {
        char **substrings = NULL;
        int substring_count = split_string_by_delimiter_string(string_lines[i], " ", &substrings);

        int *num_arr = NULL;
        for (int i = 0; i < substring_count; i++)
        {
            int num = atoi(substrings[i]);
            arrput(num_arr, num);
            free(substrings[i]);
        }
        arrput(nums, num_arr);
        free(substrings);
    }
    return nums;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);

    int **num_arrs = split_string_lines_into_int_lines(lines, linecount, " ");

    int part1_result = 0;
    int part2_result = 0;
    for (int i = 0; i < linecount; i++)
    {
        int *num_arr = num_arrs[i];
        int num_count = arrlen(num_arr);
        part1_result += extrapolate_next_val(num_arr, num_count, true);
        part2_result += extrapolate_next_val(num_arr, num_count, false);
        arrfree(num_arr);
    }
    arrfree(num_arrs);

    printf("Part1 sol: %d\n", part1_result);
    printf("Part2 sol: %d\n", part2_result);

    for (int i = 0; i < linecount; i++)
        free(lines[i]);
    free(lines);
    return 0;
}