#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;

size_t gcd(size_t a, size_t b) {
    // Euclidean algorithm
    if (b == 0) return a;
    return gcd(b, a % b);
}
 
size_t lcm(int arr[], size_t n) {
  size_t ans = arr[0];
 
  for (size_t i = 1; i < n; i++){
    ans = (ans * arr[i]) / gcd(ans, arr[i]);
  }
 
  return ans;
}

void part1(Node_To_Neighbours *adj, char *instructions, int instruction_length)
{
    char *current_node = "AAA";
    int step_count = 0;
    int i = 0;
    while (strcmp(current_node, "ZZZ") != 0)
    {
        char **current_node_neighbours = shget(adj, current_node);
        if (instructions[i] == 'L') current_node = current_node_neighbours[0];
        else current_node = current_node_neighbours[1];
        step_count++;
        i = (i+1) % instruction_length;
    }
    printf("Part1: %d\n", step_count);
}

void part2_lcm(Node_To_Neighbours *adj, char *instructions, int instruction_length)
{
    // Assumption we can make(not evident from problem statement): After each Z node, the next node is the same as the second node on the path to this Z-node
    // i.e. There are N isolated paths, each of which has exactly one A node and one Z node
    // Need to find the Lowest Common Multiple of the path lengths
    char **level = NULL;
    for (int i = 0; i < shlen(adj); i++)
    {
        if (adj[i].key[2] == 'A') arrput(level, adj[i].key);
    }
    int N = arrlen(level);

    int steps_to_reach_end[N];
    for (int i=0;i<N;i++) {
        steps_to_reach_end[i] = 0;
        char *current_node = level[i];
        int j=0;
        while(current_node[2] != 'Z'){
            char **current_node_neighbours = shget(adj, current_node);
            if (instructions[j] == 'L') current_node = current_node_neighbours[0];
            else current_node = current_node_neighbours[1];
            steps_to_reach_end[i]++;
            j = (j+1) % instruction_length;
        }
    }

    size_t ans = lcm(steps_to_reach_end, N);
    printf("Part2: %zu\n", ans);
    arrfree(level);
}

void part2_brute_force(Node_To_Neighbours *adj, char *instructions, int instruction_length)
{
    // Takes a very long time
    char **level = NULL;
    for (int i = 0; i < shlen(adj); i++)
    {
        if (adj[i].key[2] == 'A') arrput(level, adj[i].key);
    }
    int N = arrlen(level);

    size_t step_count = 0;
    int j = 0;
    while (1)
    {
        bool is_next_level_all_z = true;
        for (int i=0; i < N; i++)
        {
            char *current_node = level[i];
            char **current_node_neighbours = shget(adj, current_node);
            char *next_node;
            if (instructions[j] == 'L') next_node = current_node_neighbours[0];
            else next_node = current_node_neighbours[1];
            if (next_node[2] != 'Z') is_next_level_all_z = false;
            level[i] = next_node;
        }
        step_count++;
        j = (j+1) % instruction_length;
        if (is_next_level_all_z) break;      
    }

    printf("Part2: %zu\n", step_count);
    arrfree(level);
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

    char *instructions = lines[0];
    int instruction_length = strlen(instructions);

    Node_To_Neighbours *adj = NULL;
    for (int i = 2; i < linecount; i++)
    {
        char *line = lines[i];
        line[3] = '\0';
        line[10] = '\0';
        line[15] = '\0';

        char **neighbours = malloc(2 * sizeof(char*));
        neighbours[0] = line + 7;
        neighbours[1] = line + 12;
        shput(adj, line, neighbours);
    }
    part1(adj, instructions, instruction_length);
    part2_lcm(adj, instructions, instruction_length);


    for (int i = 0; i < shlen(adj); i++) free(adj[i].value);
    hmfree(adj);
    for (int i = 0; i < linecount; i++) free(lines[i]);
    free(lines);
    return 0;
}


// Process inputs
    // First line -> char array "instructions"
    // All other lines -> graph adjacency list, i.e.  hashmap {node: [neighbourL, neighbourR]}

// Part1
// Traverse graph using adjacency list and insturctions, until reach node ZZZ. Assume able to reach ZZZ.

// Part2
// LCM trick, see notes inside part2_lcm function
