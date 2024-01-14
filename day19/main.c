#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"


typedef struct
{
    char *key;
    char *value;
} WorkflowsMapItem;
int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    // process inputs into a useful format
    char *file_path = argv[1];
    char *file_contents = read_entire_file(file_path);
    char **sections = NULL;
    const int section_count = split_string_by_delimiter_string(file_contents, "\n\n", &sections);

    char **workflow_lines = NULL;
    int workflow_count = split_string_by_delimiter_string(sections[0], "\n", &workflow_lines);

    WorkflowsMapItem *workflows = NULL;
    for (int i = 0; i < workflow_count; i++)
    {
        char *cursor = strchr(workflow_lines[i], '}');
        *cursor = '\0';
        cursor = strchr(workflow_lines[i], '{');
        *cursor = '\0';

        shput(workflows, workflow_lines[i], cursor + 1);
    }

    char **item_lines = NULL;
    int item_count = split_string_by_delimiter_string(sections[1], "\n", &item_lines);
    int **items = malloc(item_count * sizeof(int *));
    for(int i = 0; i < item_count; i++) items[i] = malloc(4 * sizeof(int));
    for (int i=0; i<item_count; i++){
        int j = 3;
        items[i][0] = extract_number_from_string_starting_from(item_lines[i], &j);
        j+=3;
        items[i][1] = extract_number_from_string_starting_from(item_lines[i], &j);
        j+=3;
        items[i][2] = extract_number_from_string_starting_from(item_lines[i], &j);
        j+=3;
        items[i][3] = extract_number_from_string_starting_from(item_lines[i], &j);
    }

    // calculate part1
    int total = 0;
    for (int i=0; i<item_count; i++){
        int cur_x = items[i][0];
        int cur_m = items[i][1];
        int cur_a = items[i][2];
        int cur_s = items[i][3];
        char cur[4]= {'i', 'n', '\0', '\0'};
        while (cur[0] != 'R' && cur[0] != 'A'){
            char *rules = shget(workflows, &cur);
            while (1){
                char *rule_end = strchr(rules, ',');
                if (rule_end == NULL) {
                    strcpy(cur, rules); 
                    break;
                }
                char c = rules[0];
                char cond = rules[1];
                int val = extract_number_from_string(rules+2);
                char *dest_start = strchr(rules, ':') + 1;
                rules = rule_end + 1;

                if ((c == 'x' && cond == '<' && cur_x < val)
                || (c == 'x' && cond == '>' && cur_x > val)
                || (c == 'm' && cond == '<' && cur_m < val)
                || (c == 'm' && cond == '>' && cur_m > val)
                || (c == 'a' && cond == '<' && cur_a < val)
                || (c == 'a' && cond == '>' && cur_a > val)
                || (c == 's' && cond == '<' && cur_s < val)
                || (c == 's' && cond == '>' && cur_s > val)){
                    strncpy(cur, dest_start, rule_end - dest_start);
                    cur[rule_end - dest_start] = '\0';
                    break;
                }
            }
        }
        if (cur[0] == 'A') total += cur_x + cur_m + cur_a + cur_s;
    }
    printf("Part 1: %i\n", total);
    return 0;
}





