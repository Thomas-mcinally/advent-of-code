#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define MAX_NODES 20
#define HASHMAP_SIZE 256




typedef struct LinkedListNode {
    char *key;
    int value;
    struct LinkedListNode *next;
    struct LinkedListNode *prev;
} LinkedListNode;

typedef struct{
    LinkedListNode *buckets[HASHMAP_SIZE];
} HashMap;

HashMap *create_empty_hashmap()
{
    // Must be freed by caller, can use free_hashmap
    HashMap *result = malloc(sizeof(HashMap));
    for (size_t i=0; i < HASHMAP_SIZE; i++)
    {
        result->buckets[i] = malloc(sizeof(LinkedListNode));
        result->buckets[i]->key = NULL;
        result->buckets[i]->value = 0;
        result->buckets[i]->next = NULL;
        result->buckets[i]->prev = NULL;
    }
    return result;
}

void free_hashmap(HashMap *map)
{
    for (size_t i=0; i < HASHMAP_SIZE; i++)
    {
        LinkedListNode *head = map->buckets[i];
        while (head->next != NULL){
            LinkedListNode *temp = head->next;
            free(head);
            head = temp;
        }
        free(head);
    }
    free(map);
}

int generate_string_hash(char *label)
{
    int hash = 0;
    while (*label != '\0')
    {
        hash += *label;
        hash *= 17;
        hash %= HASHMAP_SIZE;
        label++;
    }
    return hash;
}

void hashmap_put(HashMap *map, char *label, int val)
{
    int hash = generate_string_hash(label);
    LinkedListNode *head = map->buckets[hash];
    while (head->next != NULL){
        head = head->next;
        if (strcmp(head->key, label) == 0)
        {
            head->value = val;
            return;
        }
    }

    // this key isnt in map yet
    LinkedListNode *new_node = malloc(sizeof(LinkedListNode));
    new_node->key = label;
    new_node->value = val;
    new_node->next = NULL;
    new_node->prev = head;

    head->next = new_node;
}

int hashmap_get(HashMap *map, char *label)
{
    int hash = generate_string_hash(label);
    LinkedListNode *head = map->buckets[hash];
    while (head->next != NULL){
        head = head->next;
        if (strcmp(head->key, label) == 0)
        {
            return head->value;
        }
    }

    return -1; //default value
}

void hashmap_del(HashMap *map, char *label)
{
    int hash = generate_string_hash(label);
    LinkedListNode *head = map->buckets[hash];
    while (head->next != NULL){
        head = head->next;
        if (strcmp(head->key, label) == 0)
        {
            head->prev->next = head->next;
            if (head->next != NULL) head->next->prev = head->prev;
            return;
        }
    }

    // Key doesnt exist in hashmap, so do nothing
}

typedef struct {
    char *key;
    int value;
} Node_To_Index;


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

int **copy_adjacency_matrix(int **adjacency_matrix){
    int **adjacency_matrix_copy = malloc(MAX_NODES * sizeof(int*));
    for (int i = 0; i < MAX_NODES; i++) {
        adjacency_matrix_copy[i] = malloc(MAX_NODES * sizeof(int));

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

    int total_nodes = 0;
    HashMap *lookup_table = create_empty_hashmap();

    int **adjacency_matrix = malloc(MAX_NODES * sizeof(int*));
    for (int i = 0; i < MAX_NODES; i++) {
        adjacency_matrix[i] = malloc(MAX_NODES * sizeof(int));
    }
    for (int i=0; i<MAX_NODES; i++){
        for (int j=0; j<MAX_NODES; j++){
            adjacency_matrix[i][j] = 0;
        }
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int lineCount = read_file_to_lines(&lines, file_path);
    printf("Read %d lines\n", lineCount);
    for (int i = 0; i < lineCount; i++) {
        char *separator = strchr(lines[i], ':');
        *separator = '\0';

        char **neighbours = NULL;
        int neighbourCount = split_string_by_delimiter_string(separator + 2, " ", &neighbours);

        for (int j = 0; j < neighbourCount; j++) {
            char *a = lines[i];
            char *b = neighbours[j];
            int a_idx = hashmap_get(lookup_table, a);
            int b_idx = hashmap_get(lookup_table, b);
            if (a_idx == -1) a_idx = total_nodes++;
            if (b_idx == -1) b_idx = total_nodes++;
            hashmap_put(lookup_table, a, a_idx);
            hashmap_put(lookup_table, b, b_idx);

            adjacency_matrix[a_idx][b_idx] = 1;
            adjacency_matrix[b_idx][a_idx] = 1;
        }
    }
    printf("total nodes: %d\n", total_nodes);
    // kergers mincut algo, assume min cut is 3 (given in question)
    int min_cut = 0;
    int partition1 = 0;
    int partition2 = 0;
    while (min_cut != 3){
        printf("Trying again\n");
        int nodes_remaining = total_nodes;
        int **adjacency_matrix_copy = copy_adjacency_matrix(adjacency_matrix);
        int *node_to_absorbed_nodes = malloc(total_nodes * sizeof(int));
        for (int i=0; i<total_nodes; i++) node_to_absorbed_nodes[i] = 1;
        while (nodes_remaining > 2){
            int start = random_node_from_adjacency_matrix(adjacency_matrix_copy);
            int finish = random_neighbour_of_node(adjacency_matrix_copy, start);
            for (int i=0; i<total_nodes; i++){
                int edges_from_finish_to_i = adjacency_matrix_copy[finish][i];
                adjacency_matrix_copy[finish][i] = 0;
                adjacency_matrix_copy[i][finish] = 0;

                if (i==start) continue;
                adjacency_matrix_copy[start][i] += edges_from_finish_to_i;
                adjacency_matrix_copy[i][start] += edges_from_finish_to_i;
            }
            node_to_absorbed_nodes[start] += node_to_absorbed_nodes[finish];
            node_to_absorbed_nodes[finish] = 0;

            nodes_remaining--;
        }

        for (int i=0; i<total_nodes; i++){
            for (int j=0; j<total_nodes; j++){
                if (adjacency_matrix_copy[i][j] != 0){
                    min_cut = adjacency_matrix_copy[i][j];
                    partition1 = node_to_absorbed_nodes[i];
                    partition2 = node_to_absorbed_nodes[j];
                    if (min_cut < 3) printf("Something went wrong, shouldnt get mincut lower than 3. Min_cut: %d\n", min_cut);
                    break;
                }
            }
        }

        deallocate_adjacency_matrix(adjacency_matrix_copy);
        free(node_to_absorbed_nodes);
}
    
    printf("Min cut: %d\n", min_cut);
    printf("Partition 1: %d\n", partition1);
    printf("Partition 2: %d\n", partition2);

    printf("Part1 sol: %d\n", partition1*partition2);
}