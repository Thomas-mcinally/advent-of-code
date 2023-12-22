#ifndef AOC_LIB_H
#define AOC_LIB_H

// Declarations
int read_file_to_lines(char ***lines, char *file_path);

char *read_entire_file(char *file_path);

int split_string_by_delimiter_string(const char *string_to_split, const char *delimiter_string, char ***result_strings);

int count_lines(char *contents);

int string_to_lines(char *string, char ***lines);

#endif // AOC_LIB_H
