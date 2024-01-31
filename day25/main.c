#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    char *key;
    int value; // edge-count
} Neighbour_To_Edge_Count;

typedef struct {
    char *key;
    Neighbour_To_Edge_Count *value;
} Node_To_Neighbours;

typedef struct {
    char *key;
    int value;
} Node_To_Absorbed_Node_Count;


int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }



        int min_cut = 20000;
        int iterations = 0;
        int partition1, partition2;
        while(iterations<1000){

            //build adjacency list
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

                    Neighbour_To_Edge_Count *a_neighbours = shget(adjacency_list, a);
                    Neighbour_To_Edge_Count *b_neighbours = shget(adjacency_list, b);
                    shput(a_neighbours, b, 1);
                    shput(b_neighbours, a, 1);
                    shput(adjacency_list, a, a_neighbours);
                    shput(adjacency_list, b, b_neighbours);
                }
            }

            Node_To_Absorbed_Node_Count *node_to_absorbed_nodes = NULL;
            for (int i=0; i<shlen(adjacency_list); i++) shput(node_to_absorbed_nodes, adjacency_list[i].key, 1);


            while (shlen(adjacency_list) > 2){
                char *start = adjacency_list[rand() % shlen(adjacency_list)].key;
                Neighbour_To_Edge_Count *start_neighbours = shget(adjacency_list, start);

                char *finish = start_neighbours[rand() % shlen(start_neighbours)].key;
                Neighbour_To_Edge_Count *finish_neighbours = shget(adjacency_list, finish);

                for (int i=0; i<shlen(finish_neighbours); i++){
                    char *key = finish_neighbours[i].key;
                    int value = finish_neighbours[i].value;
                    Neighbour_To_Edge_Count *key_neighbours = shget(adjacency_list, key);
                    if (shgeti(key_neighbours, finish) != -1) shdel(key_neighbours, finish);
                    shput(adjacency_list, key, key_neighbours);

                    if (strcmp(key, start) == 0) continue;

                    int cur_val = shget(start_neighbours, key);
                    shput(start_neighbours, key, cur_val + value);
                    key_neighbours = shget(adjacency_list, key);
                    int cur_val_2 = shget(key_neighbours, start);
                    shput(key_neighbours, start, cur_val_2 + value);
                }

                int absorbed_nodes = shget(node_to_absorbed_nodes, finish);
                int absorbed_nodes_2 = shget(node_to_absorbed_nodes, start);
                shput(node_to_absorbed_nodes, start, absorbed_nodes + absorbed_nodes_2);
                if (shgeti(node_to_absorbed_nodes, finish) != -1 ) shdel(node_to_absorbed_nodes, finish);
                if (shgeti(adjacency_list, finish) != -1 ) shdel(adjacency_list, finish);
            }

            iterations++;
            char *node1 = adjacency_list[0].key;
            char *node2 = adjacency_list[1].key;
            Neighbour_To_Edge_Count *node1_neighbours = shget(adjacency_list, node1);
            int cut = shget(node1_neighbours, node2);
            if (cut < min_cut){
                min_cut = cut;
                partition1 = shget(node_to_absorbed_nodes, node1);
                partition2 = shget(node_to_absorbed_nodes, node2);
            }

        }
        printf("Solution min_cut %d\n", min_cut);
        printf("Solution partition1 %d\n", partition1);
        printf("Solution partition2 %d\n", partition2);
        printf("Partiton1 * partiton2 %d\n", partition1 * partition2);
    }


// Still not working :(