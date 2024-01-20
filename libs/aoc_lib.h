#ifndef AOC_LIB_H
#define AOC_LIB_H

// Declarations
int read_file_to_lines(char ***lines, char *file_path);

char *read_entire_file(char *file_path);

int split_string_by_delimiter_string(const char *string_to_split, const char *delimiter_string, char ***result_strings);

int count_lines(char *contents);

int string_to_lines(char *string, char ***lines);

long long int extract_number_from_string_starting_from(const char *str, int *index);

long long int extract_number_from_string(const char *str);

size_t extract_hex_val_from_string(char *hex, int max_len);

int count_lines_in_string(const char *str);

int max(int a, int b);

int min(int a, int b);

#endif // AOC_LIB_H
