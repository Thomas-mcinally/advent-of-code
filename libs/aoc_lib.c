#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <errno.h>

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

int split_string_by_delimiter_string(const char *string_to_split, const char *delimiter_string, char ***result_strings)
// assumes string_to_split is nullterminated
// populates result_strings array with nullterminated char arrays
// does not modify input string
{
  const char *substr_start = string_to_split;
  const char *pos_delim;
  int result_count = 0;

  do
  {
    pos_delim = strstr(substr_start, delimiter_string);

    size_t length = (pos_delim != NULL) ? (pos_delim - substr_start) : strlen(substr_start); // If pos_delim is NULL, no delimiter found, so just copy the rest of the string

    *result_strings = realloc(*result_strings, (result_count + 1) * sizeof(char *));
    (*result_strings)[result_count] = malloc(length + 1);
    strncpy((*result_strings)[result_count], substr_start, length);
    result_count++;

    substr_start = (pos_delim != NULL) ? pos_delim + strlen(delimiter_string) : NULL;
  } while (pos_delim != NULL);

  return result_count;
}

int read_file_to_lines(char ***lines, char *file_path)
// Might be more useful if this excludes end-of-file line?
{
  char *content = read_entire_file(file_path);
  int line_count = split_string_by_delimiter_string(content, "\n", lines);
  free(content);
  return line_count;
}

int count_lines(char *contents)
{
  int result = 1;
  while (*contents)
  {
    if (*contents == '\n')
      result++;
    contents++;
  }
  return result;
}

long long int extract_number_from_string_starting_from(const char *str, int *index)
{
  long long int result = 0;
  while (isdigit(str[*index]))
  {
    result *= 10;
    result += str[*index] - '0';
    (*index)++;
  }
  return result;
}

int max(int a, int b){
    return a >= b ? a : b;
}

int is_hexadecimal(char c) {
    if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) return 1;
    else return 0;
}


long long int extract_number_from_string(const char *str)
{
  size_t index = 0;
  long long int result = 0;
  while (isdigit(str[index]))
  {
    result *= 10;
    result += str[index] - '0';
    (index)++;
  }
  return result;
}

size_t extract_hex_val_from_string(char *hex, int max_len){
    size_t result = 0;
    size_t i = 0;
    
    while (is_hexadecimal(hex[i])){
      result *= 16;
      if (isdigit(hex[i])) result += hex[i] - '0';
      else result += hex[i] - 'a' + 10;

      i++;
      if (i == max_len) break;
    }

    return result;
}

int count_lines_in_string(const char *str) {
    int count = 1;
    while (*str) {
        if (*str == '\n') {
            count++;
        }
        str++;
    }
    return count;
}