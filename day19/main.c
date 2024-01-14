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

size_t part2(WorkflowsMapItem *workflows, char *cur, int x_start, int x_end, int m_start, int m_end, int a_start, int a_end, int s_start, int s_end){
    if (x_end < x_start || m_end < m_start || a_end < a_start || s_end < s_start) return 0;
    if (*cur == 'A') {
        size_t result = ((size_t)(x_end-x_start+1)) * ((size_t)(m_end-m_start+1)) * ((size_t)(a_end-a_start+1)) * ((size_t)(s_end-s_start+1));
        printf("acceptance base case: x_start: %i, x_end: %i, m_start: %i, m_end: %i, a_start: %i, a_end: %i, s_start: %i, s_end: %i, new combos: %zu \n", x_start, x_end, m_start, m_end, a_start, a_end, s_start, s_end, result);
        return result;
        }
    else if (*cur == 'R') return 0;
    else{
        size_t total = 0;
        char *rules = shget(workflows, cur);
        while (1){
            char *rule_end = strchr(rules, ',');
            if (rule_end == NULL) {
                total += part2(workflows, rules, x_start, x_end, m_start, m_end, a_start, a_end, s_start, s_end);
                break;
            }

            char c = rules[0];
            char cond = rules[1];
            int val = extract_number_from_string(rules+2);
            char *dest_start = strchr(rules, ':') + 1;
            *rule_end = '\0';

            if (c=='x' && cond == '<'){
                total += part2(workflows, dest_start, x_start, val-1, m_start, m_end, a_start, a_end, s_start, s_end);
                x_start = val;
            }
            if (c=='x' && cond == '>'){
                total += part2(workflows, dest_start, val+1, x_end, m_start, m_end, a_start, a_end, s_start, s_end);
                x_end = val;
            }
            if (c=='m' && cond == '<'){
                total += part2(workflows, dest_start, x_start, x_end, m_start, val-1, a_start, a_end, s_start, s_end);
                m_start = val;
            }
            if (c=='m' && cond == '>'){
                total += part2(workflows, dest_start, x_start, x_end, val+1, m_end, a_start, a_end, s_start, s_end);
                m_end = val;
            }
            if (c=='a' && cond == '<'){
                total += part2(workflows, dest_start, x_start, x_end, m_start, m_end, a_start, val-1, s_start, s_end);
                a_start = val;
            }
            if (c=='a' && cond == '>'){
                total += part2(workflows, dest_start, x_start, x_end, m_start, m_end, val+1, a_end, s_start, s_end);
                a_end = val;
            }
            if (c=='s' && cond == '<'){
                total += part2(workflows, dest_start, x_start, x_end, m_start, m_end, a_start, a_end, s_start, val-1);
                s_start = val;
            }
            if (c=='s' && cond == '>'){
                total += part2(workflows, dest_start, x_start, x_end, m_start, m_end, a_start, a_end, val+1, s_end);
                s_end = val;
            }

            rules = rule_end + 1;
        }
        return total;

    }
}

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

    char start[3] = {'i', 'n', '\0'};
    printf("Part 2: %zu\n", part2(workflows, start, 1, 4000, 1, 4000, 1, 4000, 1, 4000));
    return 0;
}


//part2 idea:
// There is only a single entrypoint to the graph, when cur=="in".

// Any distinct combination of "x", "m", "a", "s" should follow a single path in the graph and end up at a single end node. 
// I am following every possible path and keeping track of the ranged of "x", "m", "a", "s" which fit into these paths