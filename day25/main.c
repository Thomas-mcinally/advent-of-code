#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define MAX_NODES 2000
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;


int random_node_from_adjacency_matrix(int **adjacency_matrix){
    // Chooses a random node from adjacency matrix which still exists
    while (1){
        int node = rand() % MAX_NODES;
        for (int i=0; i<MAX_NODES; i++){
            if (adjacency_matrix[node][i] != 0) return node;
            // Node exists of it has at least one edge
        }
    }
}

int random_neighbour_of_node(int **adjacency_matrix, int node){
    // Chooses a random neighbour of a node
    while (1){
        int neighbour = rand() % MAX_NODES;
        if (adjacency_matrix[node][neighbour] != 0) return neighbour;
    }
}

void print_adjacency_matrix(int **adjacency_matrix){
    printf("   ");
    for (int c=0; c<MAX_NODES; c++) printf("%d, ", c);
    printf("\n");
    for (int i=0; i<MAX_NODES; i++){
        printf("%d: ", i);
        for (int j=0; j<MAX_NODES; j++){
            printf("%d, ", adjacency_matrix[i][j]);
        }
        printf("\n");
    }
}

int **copy_adjacency_matrix(int **adjacency_matrix){
    int **adjacency_matrix_copy = calloc(MAX_NODES, sizeof(int*));
    for (int i = 0; i < MAX_NODES; i++) {
        adjacency_matrix_copy[i] = calloc(MAX_NODES, sizeof(int));
    }
    for (int i=0; i<MAX_NODES; i++){
        for (int j=0; j<MAX_NODES; j++){
            adjacency_matrix_copy[i][j] = adjacency_matrix[i][j];
        }
    }
    return adjacency_matrix_copy;
}

void deallocate_adjacency_matrix(int **adjacency_matrix){
    for (int i=0; i<MAX_NODES; i++) free(adjacency_matrix[i]);
    free(adjacency_matrix);
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


    // build up adjacency matrix of size N x N. Int matrix, value indicates nr of edges 

    int **adjacency_matrix = calloc(MAX_NODES, sizeof(int*));
    for (int i = 0; i < MAX_NODES; i++) {
        adjacency_matrix[i] = calloc(MAX_NODES, sizeof(int));
    }

    for (int i=0; i<shlen(adjacency_list); i++){
        int a_idx = i;
        for (int j=0; j<arrlen(adjacency_list[i].value); j++){
            int b_idx = shgeti(adjacency_list, adjacency_list[i].value[j]);
            adjacency_matrix[a_idx][b_idx] = 1;
        }
    }




    int min_cut = 0x7FFFFFFF;
    int partition1 = 0;
    int partition2 = 0;
    while (min_cut != 3){
        int total_nodes = shlen(adjacency_list);
        int **adjacency_matrix_copy = copy_adjacency_matrix(adjacency_matrix);
        int *node_to_absorbed_nodes = calloc(MAX_NODES, sizeof(int));
        for (int i=0; i<MAX_NODES; i++) node_to_absorbed_nodes[i] = 1;
        while (total_nodes > 2){
            int start = random_node_from_adjacency_matrix(adjacency_matrix_copy);
            int finish = random_neighbour_of_node(adjacency_matrix_copy, start);
            for (int i=0; i<MAX_NODES; i++){
                int edges_from_finish_to_i = adjacency_matrix_copy[finish][i];
                adjacency_matrix_copy[finish][i] = 0;
                adjacency_matrix_copy[i][finish] = 0;

                if (i==start) continue;
                adjacency_matrix_copy[start][i] += edges_from_finish_to_i;
                adjacency_matrix_copy[i][start] += edges_from_finish_to_i;
            }
            node_to_absorbed_nodes[start] += node_to_absorbed_nodes[finish];
            node_to_absorbed_nodes[finish] = 0;

            total_nodes--;
        }

        for (int i=0; i<MAX_NODES; i++){
            for (int j=0; j<MAX_NODES; j++){
                if (adjacency_matrix_copy[i][j] != 0){
                    if (adjacency_matrix_copy[i][j] < min_cut) {
                        min_cut = adjacency_matrix_copy[i][j];
                        partition1 = node_to_absorbed_nodes[i];
                        partition2 = node_to_absorbed_nodes[j];
                    }
                    break;
                }
            }
        }

        deallocate_adjacency_matrix(adjacency_matrix_copy);
}
    
    printf("Min cut: %d\n", min_cut);
    printf("Partition 1: %d\n", partition1);
    printf("Partition 2: %d\n", partition2);

    printf("Solution: %d\n", partition1*partition2);

    return 0;
}


//Refactoring ideas
// Build up lookup table and adjacency matrix at the same time, dont need adjacency list
// Get actual number of nodes when building uo adjacency matrix, and use this in code instead of MAX_NODES
