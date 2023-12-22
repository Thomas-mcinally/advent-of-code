#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

int read_file_to_lines(char ***lines, char *file_path)
{
  int MAX_LINE_LENGTH = 256;
  FILE *file = fopen(file_path, "r");
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

char *read_entire_file(char *file_path)
{
  // Reads an entire file into a char array, and returns a ptr to this. The ptr should be freed by the caller
  FILE *f = fopen(file_path, "r");
  if (f == NULL)
  {
    fprintf(stderr, "Could not read %s: %s\n", file_path, strerror(errno));
    exit(1);
  }

  fseek(f, 0L, SEEK_END);
  int sz = ftell(f);
  fseek(f, 0L, SEEK_SET);

  char *contents = calloc(2 * sz, sizeof(char));
  if (contents == NULL)
  {
    fprintf(stderr, "Could not allocate memory. Buy more RAM I guess?\n");
    exit(1);
  }
  fread(contents, 1, sz, f);

  fclose(f);

  return contents;
}

void split_string_by_delimiter_string(const char *string_to_split, const char *delimiter_string, char ***result_strings)
{
  // populates result_strings array
  // does not modify input string
  char buffer[strlen(string_to_split) + 1];
  strcpy(buffer, string_to_split);
  char *in = buffer;

  char *token;
  int result_count = 0;

  do
  {
    token = strstr(in, delimiter_string);

    if (token)
      *token = '\0';

    *result_strings = realloc(*result_strings, (result_count + 1) * sizeof(char *));
    (*result_strings)[result_count] = malloc(strlen(in) + 1);
    strcpy((*result_strings)[result_count], in);
    result_count++;

    in = token + strlen(delimiter_string);

  } while (token != NULL);
}

size_t string_to_lines(char *string, char ***lines) {
  // instead of this, could use built-in strtok function

  // mutates input string
  // populates lines array with pointers to char arrays
  char *cursor = string;
  size_t num_lines = count_lines(cursor);

  *lines = calloc(num_lines, sizeof(char*));

  size_t line_ctr = 0;
  while (*cursor) {
    (*lines)[line_ctr] = cursor;
    char *pos = strstr(cursor, "\n");
    *pos = '\0';
    cursor = pos + 1;
    line_ctr++;
  }

  return num_lines;
}