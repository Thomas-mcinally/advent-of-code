#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

#include "aoc_lib.h"

#define SENTINEL_VALUE 9223372036854775807 // max long long int value


void get_list_of_intervals_from_raw_input(char **raw_input_lines, long long int list_of_intervals[100][3], int start_line, int end_line)
{
  for (int i = start_line; i < end_line; i++)
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

  list_of_intervals[end_line - start_line][0] = SENTINEL_VALUE; // denote end of array
}

void get_list_of_seeds_from_raw_input(char **raw_input_lines, long long int seeds[100])
{
  int i = 0;
  int j = 7;
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
  for (int i = 0; list_of_intervals[i][0] != SENTINEL_VALUE; i++)
  {
    if (source_val >= list_of_intervals[i][0] && source_val <= list_of_intervals[i][1])
    {
      return source_val + list_of_intervals[i][2];
    }
  }
  return source_val;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
    exit(1);
  }

  char *file_path = argv[1];
  char **lines = NULL;
  int lineCount = read_file_to_lines(&lines, file_path);

  // preprocess inputs
  long long int maps[7][100][3]; // Each map is [(start1, end1, diff1), (start2, end2, diff2), ...] Unsorted list of non-overlapping intervals. Inclusive start and end
  get_list_of_intervals_from_raw_input(lines, maps[0], 3, 12);
  get_list_of_intervals_from_raw_input(lines, maps[1], 14, 40);
  get_list_of_intervals_from_raw_input(lines, maps[2], 42, 71);
  get_list_of_intervals_from_raw_input(lines, maps[3], 73, 94);
  get_list_of_intervals_from_raw_input(lines, maps[4], 96, 115);
  get_list_of_intervals_from_raw_input(lines, maps[5], 117, 160);
  get_list_of_intervals_from_raw_input(lines, maps[6], 162, 189);

  long long int seeds[100];
  get_list_of_seeds_from_raw_input(lines, seeds);

  long long int lowest_location = SENTINEL_VALUE;
  for (int i = 0; seeds[i] != SENTINEL_VALUE; i++)
  {
    long long int step = seeds[i];

    for (int j = 0; j < 7; j++)
    {
      step = get_destination_from_source_and_intervals(maps[j], step);
    }

    if (step < lowest_location)
    {
      lowest_location = step;
      printf("new lowest location: %lli, from seed: %lli\n", lowest_location, seeds[i]);
    }
  }
  printf("Part1 result: %lli\n", lowest_location);
}

// Think of as interval question, use input to form a list of non-overlapping intervals

// ASSUMPTIONS
// - Can assume input given in predictable ladder format, where each map gives output that is input for the next map
// - Currently assume each step in ladder has a certain start and end line
// TODO: refactor
// - Grab array of maps dynamically, identify a new map by two newline characters in a row "\n\n"