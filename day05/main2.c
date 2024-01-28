#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>
#include "aoc_lib.h"

#define SENTINEL_VALUE 0x7FFFFFFFFFFFFFFF // max long long int value

void get_list_of_intervals_from_raw_input(char **lines, long long int list_of_intervals[100][3], int line_count)
{
  for (int i = 0; i < line_count; i++)
  {
    int j = 0;
    long long int first_num = extract_number_from_string_starting_from(lines[i], &j);
    j++;
    long long int second_num = extract_number_from_string_starting_from(lines[i], &j);
    j++;
    long long int third_num = extract_number_from_string_starting_from(lines[i], &j);

    list_of_intervals[i][0] = first_num;
    list_of_intervals[i][1] = first_num + third_num - 1;
    list_of_intervals[i][2] = second_num - first_num;
  }

  list_of_intervals[line_count][0] = SENTINEL_VALUE; // denote end of array
}
void get_list_of_seeds_from_raw_input(char *seed_line, long long int seeds[100][2])
{
  int i = 0;
  int j = 7;
  long long int cur_num = 0;
  long long int cur_start = 0;
  while (seed_line[j] != '\0')
  {
    if (isdigit(seed_line[j]))
    {
      cur_num *= 10;
      cur_num += seed_line[j] - '0';
    }
    else if (seed_line[j] == ' ' || seed_line[j] == '\n')
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

long long int get_destination_from_source_and_intervals(long long int list_of_intervals[100][3], long long int source_val)
{
  for (int i = 0; list_of_intervals[i][0] != SENTINEL_VALUE; i++)
  {
    if (source_val >= list_of_intervals[i][0] && source_val <= list_of_intervals[i][1])
    {
      return source_val + list_of_intervals[i][2];
    }
  }
  return source_val;
}

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
    exit(1);
  }

  char *file_path = argv[1];
  char *file_contents = read_entire_file(file_path);
  char **sections = NULL;
  const int section_count = split_string_by_delimiter_string(file_contents, "\n\n", &sections);
  const int number_of_maps = section_count - 1;
  long long int maps[number_of_maps][100][3]; // assume each section has max 100 lines
  for (int i = 0; i < number_of_maps; i++)
  {
    char **section_lines = NULL;
    const int line_count = split_string_by_delimiter_string(sections[i + 1], "\n", &section_lines);
    section_lines++; // first line is name of the map
    get_list_of_intervals_from_raw_input(section_lines, maps[i], line_count - 1);
    section_lines--;
    for (int j = 0; j < line_count; j++)
      free(section_lines[j]);
    free(section_lines);
  }
  free(file_contents);

  long long int seeds[100][2]; // [[start1, size1], [start2, size2], ...]
  get_list_of_seeds_from_raw_input(sections[0], seeds);

  for (int i = 0; i < section_count; i++)
    free(sections[i]);
  free(sections);

  long long int lowest_location = 0;
  while (lowest_location < SENTINEL_VALUE)
  {
    // find seed that produces location
    long long int cur = lowest_location;
    for (int i = number_of_maps - 1; i >= 0; i--)
    {
      cur = get_destination_from_source_and_intervals(maps[i], cur);
    }

    // check if this seed is in any of the seed ranges
    for (int i = 0; seeds[i][0] != SENTINEL_VALUE; i++)
    {
      if (cur >= seeds[i][0] && cur <= seeds[i][0] + seeds[i][1] - 1)
      {
        printf("Part2 sol: %lli\n", lowest_location);
        return 0;
      }
    }
    lowest_location++;
  }
  printf("No solution found\n");
}

// PART2:
// Idea1: Determine all possible seed values and process each of them
// Not feasible since there are so many
// Idea2: Start from location=0 and try figure out if the necessary seed value is available.

// Differences from part1 sol:
// - get_list_of_intervals_from_raw_input slightly different
// - Ranges of seeds rather than single values
// - What we do after generating maps is different