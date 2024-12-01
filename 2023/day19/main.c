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

WorkflowsMapItem *populate_workflows_hashmap(char *s, WorkflowsMapItem *workflows){
    char **workflow_lines = NULL;
    int workflow_count = split_string_by_delimiter_string(s, "\n", &workflow_lines);

    for (int i = 0; i < workflow_count; i++)
    {
        char *end_of_key = strchr(workflow_lines[i], '{');
        *end_of_key = '\0';
        char *key = malloc(end_of_key - workflow_lines[i] + 1);
        strcpy(key, workflow_lines[i]);

        char *end_of_value = strchr(end_of_key+1, '}');
        *end_of_value = '\0';
        char *value = malloc(end_of_value - end_of_key);
        strcpy(value, end_of_key + 1);

        shput(workflows, key, value);
    }
    for (int i = 0; i < workflow_count; i++) free(workflow_lines[i]);
    free(workflow_lines);
    return workflows;
}

void populate_items_array(char *s, int **items, int item_count){
    char **item_lines = NULL;
    split_string_by_delimiter_string(s, "\n", &item_lines);

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
    for (int i = 0; i < item_count; i++) free(item_lines[i]);
    free(item_lines);
}

size_t dfs_part1(WorkflowsMapItem *workflows, char *cur, int x, int m, int a, int s){
    if (*cur == 'R') return 0;
    if (*cur == 'A') return x + m + a + s;

    char *rules = shget(workflows, cur);
    char *dest = malloc(4*sizeof(char));
    int dest_found = 0;

    while (!dest_found){
        char *rule_end = strchr(rules, ',');
        if (rule_end == NULL) {
            dest_found = 1;
            strcpy(dest, rules);
        }
        char c = rules[0];
        char cond = rules[1];
        int val = extract_number_from_string(rules+2);
        char *label_start = strchr(rules, ':') + 1;
        rules = rule_end + 1;

        if ((c == 'x' && cond == '<' && x < val)
        || (c == 'x' && cond == '>' && x > val)
        || (c == 'm' && cond == '<' && m < val)
        || (c == 'm' && cond == '>' && m > val)
        || (c == 'a' && cond == '<' && a < val)
        || (c == 'a' && cond == '>' && a > val)
        || (c == 's' && cond == '<' && s < val)
        || (c == 's' && cond == '>' && s > val)){
            dest_found = 1;
            strncpy(dest, label_start, rule_end - label_start);
            dest[rule_end - label_start] = '\0';
        }
    }
    size_t result = dfs_part1(workflows, dest, x, m, a, s);
    free(dest);
    return result;
}

size_t part1(WorkflowsMapItem *workflows, int **items, int item_count){
    size_t total = 0;
    for (int i=0; i<item_count; i++){
        int cur_x = items[i][0];
        int cur_m = items[i][1];
        int cur_a = items[i][2];
        int cur_s = items[i][3];
        total += dfs_part1(workflows, "in", cur_x, cur_m, cur_a, cur_s);
    }
    return total;
}

size_t part2(WorkflowsMapItem *workflows, char *cur, int x_start, int x_end, int m_start, int m_end, int a_start, int a_end, int s_start, int s_end){
    if (x_end < x_start || m_end < m_start || a_end < a_start || s_end < s_start || *cur == 'R') return 0;
    if (*cur == 'A') {
        size_t combos = ((size_t)(x_end-x_start+1)) * ((size_t)(m_end-m_start+1)) * ((size_t)(a_end-a_start+1)) * ((size_t)(s_end-s_start+1));
        return combos;
        }
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

    char *file_path = argv[1];
    char *file_contents = read_entire_file(file_path);
    char **sections = NULL;
    const int section_count = split_string_by_delimiter_string(file_contents, "\n\n", &sections);

    WorkflowsMapItem *workflows = NULL;
    workflows = populate_workflows_hashmap(sections[0], workflows);

    int item_count = count_lines_in_string(sections[1]);
    int **items = malloc(item_count * sizeof(int *));
    for(int i = 0; i < item_count; i++) items[i] = malloc(4 * sizeof(int));
    populate_items_array(sections[1], items, item_count);

    printf("Part1 sol: %zu\n", part1(workflows, items, item_count));
    printf("Part2 sol: %zu\n", part2(workflows, "in", 1, 4000, 1, 4000, 1, 4000, 1, 4000));

    for (int i = 0; i < section_count; i++) free(sections[i]);
    free(sections);
    free(file_contents);
    for (int i = 0; i < item_count; i++) free(items[i]);
    free(items);
    shfree(workflows);
    return 0;
}


//part2 idea:
// There is only a single entrypoint to the graph, when cur=="in".

// Any distinct combination of "x", "m", "a", "s" should follow a single path in the graph and end up at a single end node. 
// I am following every possible path and keeping track of the ranged of "x", "m", "a", "s" which fit into these paths