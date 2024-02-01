#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;

void dfs(Node_To_Neighbours *adjacency_list, char *node, int *is_node_visited, size_t *graph_size) {
    int node_i = shgeti(adjacency_list, node);
    if (is_node_visited[node_i]) {
        return;
    }

    is_node_visited[node_i] = 1;
    (*graph_size)++;

    char **neighbours = shget(adjacency_list, node);
    for (int i = 0; i < arrlen(neighbours); i++) {
        dfs(adjacency_list, neighbours[i], is_node_visited, graph_size);
    }
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines, file_path);
    Node_To_Neighbours *adjacency_list = NULL;
    shdefault(adjacency_list, NULL);
    for (int i = 0; i < lineCount; i++) {
        char *separator = strchr(lines[i], ':');
        *separator = '\0';

        char **neighbours = NULL;
        int neighbourCount = split_string_by_delimiter_string(separator + 2, " ", &neighbours);

        for (int j = 0; j < neighbourCount; j++) {
            char *a = lines[i];
            char *b = neighbours[j];
            char **a_neighbours = shget(adjacency_list, a);
            char **b_neighbours = shget(adjacency_list, b);

            arrput(a_neighbours, b);
            arrput(b_neighbours, a);

            shput(adjacency_list, a, a_neighbours);
            shput(adjacency_list, b, b_neighbours);
        }
    }

    int *is_node_visited = calloc(shlen(adjacency_list), sizeof(int));
    size_t graph1_size = 0;
    dfs(adjacency_list, "mhb", is_node_visited, &graph1_size);
    size_t graph2_size = 0;
    dfs(adjacency_list, "zqg", is_node_visited, &graph2_size);

    printf("Graph 1 size: %zu\n", graph1_size);
    printf("Graph 2 size: %zu\n", graph2_size);

    printf("Part1 sol: %zu\n", graph1_size * graph2_size);


}



// approach:
// By inspecting graph visually, found that my linkers are mhb/zqg, sjr/jlt, fjn/mzb
// Removed these edges then explored both graphs to find nr. of nodes in each. Startpoints: mhb and zqg