// .??..??...?##. 1,1,3

// Pseudocode
// input two indexes, one indicating position in string and one indicating position in key
// f(i, j) -> Number of valid combinations
// if i==len(s) && j==len(key): return 1
// if len(s)-i < key[j]: return 0

// res = 0
// if (no . between s[i] and s[i+key[j]]) && s[i+key[j]] != #:  res += f(i+key[j]+1, j+1)
// if s[i] == '?' || s[i] == '.': res += f(i+1, j)
// return res




#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"



size_t num_valid_combos_starting_from(char *s, int *key, size_t s_len, int key_len, int i, int j){
    if (i>=s_len && j==key_len) return 1;
    if (j == key_len){
        if (s[i] != '#') return num_valid_combos_starting_from(s, key, s_len, key_len, i+1, j);
        else return 0;
    }
    if (s_len-i < key[j]) return 0;

    size_t res = 0;
    char *next_dot = strchr(s+i, '.');
    int distance_to_next_dot = (next_dot==NULL) ? s_len-i : next_dot - (s + i);
    if (distance_to_next_dot >= key[j] && s[i+key[j]] != '#') res += num_valid_combos_starting_from(s, key, s_len, key_len, i+key[j]+1, j+1);
    if (s[i] == '?' || s[i] == '.') res += num_valid_combos_starting_from(s, key, s_len, key_len, i+1, j);
    return res;
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);
    


    size_t total_combos = 0;

    for (int i=0; i<linecount; i++){
        char *s = lines[i];
        char *space = strchr(s, ' ');
        *space = '\0';

        int j = 0;
        char *key_string = space + 1;
        int *key = NULL;
        while (key_string[j] != '\0'){
            int val = extract_number_from_string_starting_from(key_string, &j);
            arrput(key, val);
            if (key_string[j] == ',') j++;
        }

        total_combos += num_valid_combos_starting_from(s, key, strlen(s), arrlen(key), 0, 0);
        arrfree(key);
    }

    printf("Total combos: %zu\n", total_combos);
}
