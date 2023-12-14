#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

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
        int diff_is_positive; // because was forced to use unsigned int type
        if (first_num >= second_num) {
            diff = first_num - second_num;
            diff_is_positive = 1;
        }
        else 
        {
            diff = second_num - first_num;
            diff_is_positive = 0;
        }

        list_of_intervals[i - start_line][0] = second_num;
        list_of_intervals[i - start_line][1] = second_num + third_num - 1;
        list_of_intervals[i - start_line][2] = diff;
        list_of_intervals[i - start_line][3] = diff_is_positive;
    }

    list_of_intervals[end_line][0] = -1; // denote end of array
}

void get_list_of_seeds_from_raw_input(char **raw_input_lines, unsigned int seeds[100])
{   
    int i=0;
    int j=7;
    unsigned int cur_num = 0;
    while (raw_input_lines[0][j] != '\n')
    {
        if (isdigit(raw_input_lines[0][j]))
        {
            cur_num *= 10;
            cur_num += raw_input_lines[0][j] - '0';
            // printf("cur_num: %u\n", cur_num); //for debugging overflow
        }
        else if (raw_input_lines[0][j] == ' ')
        {
            seeds[i] = cur_num;
            cur_num = 0;
            i++;
        }
        j++;
    }
    if(cur_num != 0)
    {
        seeds[i] = cur_num;
        i++;
    }
    seeds[i] = -1; // denote end of array
}
unsigned int get_destination_from_source_and_intervals(unsigned int list_of_intervals[100][4], unsigned int source_val)
{
  for (int j=0; list_of_intervals[j][0] != -1; j++)
    {
        if (source_val >= list_of_intervals[j][0] && source_val <= list_of_intervals[j][1])
        {
            if (list_of_intervals[j][3] == 1) return source_val + list_of_intervals[j][2];
            if (list_of_intervals[j][3] == 0) return source_val - list_of_intervals[j][2];
        }
    }
    return source_val; 
}
int main()
{
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines);
    

    // preprocess inputs
    unsigned int seed_to_soil_intervals[100][4]; // [(start1, end1, diff1, diffPositive1), (start2, end2, diff2, diffPositive2), ...] Unsorted list of non-overlapping intervals. Inclusive start and end
    get_list_of_intervals_from_raw_input(lines, seed_to_soil_intervals, 3, 12);
    unsigned int soil_to_fertilizer_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, soil_to_fertilizer_intervals, 14, 40);
    unsigned int fertilizer_to_water_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, fertilizer_to_water_intervals, 42, 71);
    unsigned int water_to_light_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, water_to_light_intervals, 73, 94);
    unsigned int light_to_temperature_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, light_to_temperature_intervals, 96, 115);
    unsigned int temperature_to_humidity_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, temperature_to_humidity_intervals, 117, 160);
    unsigned int humidity_to_location_intervals[100][4];
    get_list_of_intervals_from_raw_input(lines, humidity_to_location_intervals, 162, 189);

    unsigned int seeds[100];
    get_list_of_seeds_from_raw_input(lines, seeds);

    unsigned int lowest_location = 4294967295; //max unsigned int
    for (int i=0; seeds[i] != -1; i++)
    {
        unsigned int seed = seeds[i];
        int soil = get_destination_from_source_and_intervals(seed_to_soil_intervals, seed);
        int fertilizer = get_destination_from_source_and_intervals(soil_to_fertilizer_intervals, soil);
        int water = get_destination_from_source_and_intervals(fertilizer_to_water_intervals, fertilizer);
        int light = get_destination_from_source_and_intervals(water_to_light_intervals, water);
        int temperature = get_destination_from_source_and_intervals(light_to_temperature_intervals, light);
        int humidity = get_destination_from_source_and_intervals(temperature_to_humidity_intervals, temperature);
        int location = get_destination_from_source_and_intervals(humidity_to_location_intervals, humidity);

        if (location < lowest_location) 
        {
            lowest_location = location;
            printf("new lowest location: %u, from seed: %u\n", lowest_location, seed);
        }

    }
    printf("Part1 result: %u\n", lowest_location);
}
// Notes
// In maps, key == value unless the input says otherwise
// If in map, key: key + x, where x = value - key

// For each mapping, need to be able to look up by key
// i.e. need a way to figure out of key falls inside a range, and what x is for each range


// Think of as interval question, use input to form a list of non-overlapping intervals 