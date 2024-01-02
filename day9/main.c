#include <string.h>
#include <stdio.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int calculate_next_val(int *nums, int num_count){
    int result = nums[num_count-1];

    int *cur_arr = NULL;
    for (int i=0; i<num_count; i++) arrput(cur_arr, nums[i]);
    int *next_arr = NULL;

    int next_arr_all_zeroes = 0;
    while (next_arr_all_zeroes == 0) {
        next_arr_all_zeroes = 1;
        for (int i = 1; i < arrlen(cur_arr); i++)
        {
            int diff = cur_arr[i] - cur_arr[i-1];
            if (diff != 0) next_arr_all_zeroes = 0;
            arrput(next_arr, diff);
        }
        result += arrlast(next_arr);
        arrfree(cur_arr);
        cur_arr = next_arr;
        next_arr = NULL;
    }

    return result;
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

    // turn input into array of array of ints
    int **nums = NULL;
    for (int i = 0; i < linecount; i++)
    {
        char *line = lines[i];
        int *num_arr = NULL;
        char *token = strtok(line, " ");
        while (token != NULL)
        {
            int num = atoi(token);
            arrput(num_arr, num);
            token = strtok(NULL, " ");
        }
        arrput(nums, num_arr);
    }


    int part1_result = 0;
    for (int i = 0; i < linecount; i++)
    {
        int *num_arr = nums[i];
        int num_count = arrlen(num_arr);
        int next_val = calculate_next_val(num_arr, num_count);
        part1_result += next_val;
        arrfree(num_arr);
    }
    arrfree(nums);
    printf("Part1: %d\n", part1_result);
}