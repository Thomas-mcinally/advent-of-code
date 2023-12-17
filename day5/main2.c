#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SENTINEL_VALUE 0xFFFFFFFF // Using the maximum value for unsigned int

int read_file_to_lines(char ***lines){
    int MAX_LINE_LENGTH = 256;
    FILE *file = fopen("./input.txt", "r");
    int lineCount = 0;

    char buffer[MAX_LINE_LENGTH];
    while (fgets(buffer, MAX_LINE_LENGTH, file) != NULL)
    {
        *lines = realloc(*lines, (lineCount + 1) * sizeof(char *));
        (*lines)[lineCount] = malloc(strlen(buffer) + 1);

        strcpy((*lines)[lineCount], buffer);
        lineCount++;
    }
    fclose(file);
    return lineCount;
}


void get_list_of_intervals_from_raw_input(char **raw_input_lines, unsigned int list_of_intervals[100][4], int start_line, int end_line)
{    
    for (int i=start_line; i<end_line; i++)
    {
        unsigned int first_num = 0;
        int j = 0;
        while (raw_input_lines[i][j] != ' ')
        {
            first_num *= 10;
            first_num += raw_input_lines[i][j] - '0';
            j++;
        }

        unsigned int second_num = 0;
        j++;
        while (raw_input_lines[i][j] != ' ')
        {
            second_num *= 10;
            second_num += raw_input_lines[i][j] - '0';
            j++;
        }

        unsigned int third_num = 0;
        j++;
        while (raw_input_lines[i][j] != '\n')
        {
            third_num *= 10;
            third_num += raw_input_lines[i][j] - '0';
            j++;
        }

        unsigned int diff;
        unsigned int diff_is_positive; // 0/1,  because was forced to use unsigned int type
        if (second_num >= first_num) {
            diff = second_num - first_num;
            diff_is_positive = 1;
        }
        else 
        {
            diff = first_num - second_num;
            diff_is_positive = 0;
        }

        list_of_intervals[i - start_line][0] = first_num;
        list_of_intervals[i - start_line][1] = first_num + third_num - 1; // assume this will not overflow
        list_of_intervals[i - start_line][2] = diff;
        list_of_intervals[i - start_line][3] = diff_is_positive;
        if (list_of_intervals[i - start_line][1] < first_num) printf("overflow detected 1\n"); // for debugging overflow
    }

    list_of_intervals[end_line-start_line][3] = 2; // denote end of array
}


void get_list_of_seeds_from_raw_input(char **raw_input_lines, unsigned int seeds[100][2])
{   
    int i=0;
    int j=7;
    unsigned int cur_num = 0;
    unsigned int cur_start = 0;
    while (raw_input_lines[0][j] != '\n')
    {
        if (isdigit(raw_input_lines[0][j]))
        {
            cur_num *= 10;
            cur_num += raw_input_lines[0][j] - '0';
        }
        else if (raw_input_lines[0][j] == ' ' || raw_input_lines[0][j] == '\n')
        {
            if (cur_start == 0)
            {
                cur_start = cur_num;
            }
            else
            {
                seeds[i][0] = cur_start;
                seeds[i][1] = cur_num;
                cur_start = 0;
                i++;
            }
            cur_num = 0;
        }
        j++;
    }
    seeds[i][0] = SENTINEL_VALUE; // denote end of array
}


unsigned int get_destination_from_source_and_intervals(unsigned int list_of_intervals[100][4], unsigned int source_val)
{
  for (int i=0; list_of_intervals[i][3] != 2; i++)
    {
        if (source_val >= list_of_intervals[i][0] && source_val <= list_of_intervals[i][1])
        {
            if (list_of_intervals[i][3] == 1) 
            {
                if (source_val + list_of_intervals[i][2] < source_val) return SENTINEL_VALUE; // return max value when overflow. Here we ASSUME that no range will ever contain a value greater than max val
                return source_val + list_of_intervals[i][2];
            
            }

            if (list_of_intervals[i][3] == 0) {
                return source_val - list_of_intervals[i][2];
            }    
        }
    }
    return source_val; 
}


int main()
{
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines);
    

    // preprocess inputs
    unsigned int soil_to_seed_intervals[100][4]; // [(start1, end1, diff1, diffPositive1), (start2, end2, diff2, diffPositive2), ...] Unsorted list of non-overlapping intervals. Inclusive start and end
    get_list_of_intervals_from_raw_input(lines, soil_to_seed_intervals, 3, 12);
    unsigned int fertilizer_to_soil_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, fertilizer_to_soil_intervals, 14, 40);
    unsigned int water_to_fertilizer_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, water_to_fertilizer_intervals, 42, 71);
    unsigned int light_to_water_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, light_to_water_intervals, 73, 94);
    unsigned int temperature_to_light_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, temperature_to_light_intervals, 96, 115);
    unsigned int humidity_to_temperature_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, humidity_to_temperature_intervals, 117, 160);
    unsigned int location_to_humidity_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, location_to_humidity_intervals, 162, 189);

    unsigned int seeds[100][2]; // [[start1, size1], [start2, size2], ...]
    get_list_of_seeds_from_raw_input(lines, seeds);


    unsigned int lowest_location = 0;
    while (lowest_location < SENTINEL_VALUE)
    {
        // find seed that produces location
        unsigned int humidity = get_destination_from_source_and_intervals(location_to_humidity_intervals, lowest_location);
        unsigned int temperature = get_destination_from_source_and_intervals(humidity_to_temperature_intervals, humidity);
        unsigned int light = get_destination_from_source_and_intervals(temperature_to_light_intervals, temperature);
        unsigned int water = get_destination_from_source_and_intervals(light_to_water_intervals, light);
        unsigned int fertilizer = get_destination_from_source_and_intervals(water_to_fertilizer_intervals, water);
        unsigned int soil = get_destination_from_source_and_intervals(fertilizer_to_soil_intervals, fertilizer);
        unsigned int seed = get_destination_from_source_and_intervals(soil_to_seed_intervals, soil);

        // check if this seed is in any of the seed ranges
        for (int i=0; seeds[i][0] != SENTINEL_VALUE; i++)
        {
            if (seed >= seeds[i][0] && seed <= seeds[i][0] + seeds[i][1] - 1)
            {
                printf("Part 2 sol: %u\n", lowest_location);
                return 0;
            }
        }
        lowest_location++;
    }
    printf("couldnt find solution\n");
}



// PART2:
// Idea1: Determine all possible seed values and process each of them
    // Not feasible since there are so many
// Idea2: Start from location=0 and try figure out if the necessary seed value is available.