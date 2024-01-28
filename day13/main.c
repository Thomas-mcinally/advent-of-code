#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "aoc_lib.h"

int vertical_reflection_error_count(char **grid, int ROWS, int COLS, int mirror_c) {
  int error_count = 0;

  int left = mirror_c;
  int right = mirror_c + 1;

  while (left>=0 && right<COLS) {
    for (int i=0; i<ROWS; i++) {
      if (grid[i][left] != grid[i][right]) error_count++;
    }
    left--;
    right++;
  }

  return error_count;
}

int horizonal_reflection_error_count(char **grid, int ROWS, int COLS, int mirror_r) {
  int error_count = 0;

  int top = mirror_r;
  int bottom = mirror_r+1;

  while (top>=0 && bottom<ROWS) {
    for (int i=0; i<COLS; i++) {
      if (grid[top][i] != grid[bottom][i]) error_count++;
    }
    top--;
    bottom++;
  }

  return error_count;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "Please provide a single argument -- the file to be analysed.\n");
    return 1;
  }
    char *file_path = argv[1];
    char *content = read_entire_file(file_path);
    char **sections = NULL;
    int section_count = split_string_by_delimiter_string(content, "\n\n", &sections);

    size_t total_1 = 0;
    size_t total_2 = 0;
    for (size_t section_i=0; section_i < section_count; section_i++){
        char **grid = NULL;
        int ROWS = split_string_by_delimiter_string(sections[section_i], "\n", &grid);
        int COLS = strlen(grid[0]);
        for (int c=0; c<COLS-1; c++) {
            int err_count = vertical_reflection_error_count(grid, ROWS, COLS, c);
            if (err_count == 0) total_1 += (c+1);
            if (err_count == 1) total_2 += (c+1);
        }

        for (int r=0; r<ROWS-1; r++){
            int err_count = horizonal_reflection_error_count(grid, ROWS, COLS, r);
            if (err_count == 0) total_1 += (r+1)*100;
            if (err_count == 1) total_2 += (r+1)*100;
        }
        for (int i=0; i<ROWS; i++) free(grid[i]);
        free(grid);
    }
    printf("Part1 sol: %zu\n", total_1);
    printf("Part2 sol: %zu\n", total_2);

    for (int i=0; i<section_count; i++) free(sections[i]);
    free(sections);
    free(content);
    return 0;
}