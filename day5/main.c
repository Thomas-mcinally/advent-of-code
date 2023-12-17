#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define SENTINEL_VALUE 9223372036854775807 //max long long int value

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


void get_list_of_intervals_from_raw_input(char **raw_input_lines, long long int list_of_intervals[100][3], int start_line, int end_line)
{    
    for (int i=start_line; i<end_line; i++)
    {
        long long int first_num = 0;
        int j = 0;
        while (raw_input_lines[i][j] != ' ')
        {
            first_num *= 10;
            first_num += raw_input_lines[i][j] - '0';
            j++;
        }

        long long int second_num = 0;
        j++;
        while (raw_input_lines[i][j] != ' ')
        {
            second_num *= 10;
            second_num += raw_input_lines[i][j] - '0';
            j++;
        }

        long long int third_num = 0;
        j++;
        while (raw_input_lines[i][j] != '\n')
        {
            third_num *= 10;
            third_num += raw_input_lines[i][j] - '0';
            j++;
        }

        list_of_intervals[i - start_line][0] = second_num;
        list_of_intervals[i - start_line][1] = second_num + third_num - 1; 
        list_of_intervals[i - start_line][2] = first_num - second_num;
    }

    list_of_intervals[end_line-start_line][0] = SENTINEL_VALUE; // denote end of array
}

void get_list_of_seeds_from_raw_input(char **raw_input_lines, long long int seeds[100])
{   
    int i=0;
    int j=7;
    long long int cur_num = 0;
    while (raw_input_lines[0][j] != '\n')
    {
        if (isdigit(raw_input_lines[0][j]))
        {
            cur_num *= 10;
            cur_num += raw_input_lines[0][j] - '0';
        }
        else if (raw_input_lines[0][j] == ' ')
        {
            seeds[i] = cur_num;
            cur_num = 0;
            i++;
        }
        j++;
    }
    seeds[i] = cur_num;
    i++;
    seeds[i] = SENTINEL_VALUE; // denote end of array
}


long long int get_destination_from_source_and_intervals(long long int list_of_intervals[100][3], long long int source_val)
{
  for (int i=0; list_of_intervals[i][0] != SENTINEL_VALUE; i++)
    {
        if (source_val >= list_of_intervals[i][0] && source_val <= list_of_intervals[i][1])
        {
            return source_val + list_of_intervals[i][2];  
        }
    }
    return source_val; 
}


int main()
{
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines);
    

    // preprocess inputs
    long long int seed_to_soil_intervals[100][3]; // [(start1, end1, diff1, diffPositive1), (start2, end2, diff2, diffPositive2), ...] Unsorted list of non-overlapping intervals. Inclusive start and end
    get_list_of_intervals_from_raw_input(lines, seed_to_soil_intervals, 3, 12);
    long long int soil_to_fertilizer_intervals[100][3];
    get_list_of_intervals_from_raw_input(lines, soil_to_fertilizer_intervals, 14, 40);
    long long int fertilizer_to_water_intervals[100][3];
    get_list_of_intervals_from_raw_input(lines, fertilizer_to_water_intervals, 42, 71);
    long long int water_to_light_intervals[100][3];
    get_list_of_intervals_from_raw_input(lines, water_to_light_intervals, 73, 94);
    long long int light_to_temperature_intervals[100][3];
    get_list_of_intervals_from_raw_input(lines, light_to_temperature_intervals, 96, 115);
    long long int temperature_to_humidity_intervals[100][3];
    get_list_of_intervals_from_raw_input(lines, temperature_to_humidity_intervals, 117, 160);
    long long int humidity_to_location_intervals[100][3];
    get_list_of_intervals_from_raw_input(lines, humidity_to_location_intervals, 162, 189);

    long long int seeds[100];
    get_list_of_seeds_from_raw_input(lines, seeds);


    long long int lowest_location = SENTINEL_VALUE; //max long long int
    for (int i=0; seeds[i] != SENTINEL_VALUE; i++)
    {
        long long int seed = seeds[i];
        long long int soil = get_destination_from_source_and_intervals(seed_to_soil_intervals, seed);
        long long int fertilizer = get_destination_from_source_and_intervals(soil_to_fertilizer_intervals, soil);
        long long int water = get_destination_from_source_and_intervals(fertilizer_to_water_intervals, fertilizer);
        long long int light = get_destination_from_source_and_intervals(water_to_light_intervals, water);
        long long int temperature = get_destination_from_source_and_intervals(light_to_temperature_intervals, light);
        long long int humidity = get_destination_from_source_and_intervals(temperature_to_humidity_intervals, temperature);
        long long int location = get_destination_from_source_and_intervals(humidity_to_location_intervals, humidity);

        if (location < lowest_location) 
        {
            lowest_location = location;
            printf("new lowest location: %lli, from seed: %lli\n", lowest_location, seed);
        }

    }
    printf("Part1 result: %lli\n", lowest_location);
}

// Think of as interval question, use input to form a list of non-overlapping intervals 

// Strategies for iterating through an array in C: Use a "SENTINEL VALUE" i.e. a value which is never used in array. The function which constructs the array can return its length.
