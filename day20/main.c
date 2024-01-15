#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "aoc_lib.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

// high -> flipflop, terminates

// construct graph from inputs: Adjacency list + current state of each node
// Make a note of start state of each node
// Do a level-based BFS, keeping track of which pulse count, and what state will be after this level
// End of level: If new_state == start_state, end.
// End of level else: update current state of each node and continue to next level


// Adjacency list. Max 10 neighbours. Indicate end of neighbours with nullpointer
typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;


typedef struct {
    char type;
    int on; // 0 or 1. Relevant for flipflop nodes
    char *last_pulse_from_neighbour; // 'L' or 'H' for each neighbour, in same order as given in adjacency list. Relevant for Conjunction nodes
} Module_State;

// State of each node. Max 10 neighbours.
typedef struct {
    char *key;
    Module_State *value;
} Node_To_State;

Node_To_State *create_new_state_dict(Node_To_Neighbours *adj)
{
    Node_To_State *state = NULL;
    for (int i = 0; i < shlen(adj); i++)
    {
        char *key = adj[i].key;
        Module_State *value = malloc(sizeof(Module_State));
        value->type = key[0];
        value->on = 0;
        value->last_pulse_from_neighbour = malloc(10 * sizeof(char));
        int j=0;
        while (adj[i].value[j] != NULL) value->last_pulse_from_neighbour[j++] = 'L';
        value->last_pulse_from_neighbour[j] = '\0';
        shput(state, key, value);
    }
    return state;
}

void free_state_dict(Node_To_State *state)
{
    for (int i = 0; i < shlen(state); i++)
    {
        free(state[i].value->last_pulse_from_neighbour);
        free(state[i].value);
    }
    shfree(state);
}

int are_state_dicts_identical(Node_To_State *state1, Node_To_State *state2)
{
    for (int i = 0; i < shlen(state1); i++)
    {
        if (state1[i].value->type != state2[i].value->type) return 0;
        if (state1[i].value->on != state2[i].value->on) return 0;
        if (strcmp(state1[i].value->last_pulse_from_neighbour, state2[i].value->last_pulse_from_neighbour) != 0) return 0;
    }
    return 1;
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
    for (int i = 0; i < linecount; i++)
    {
        char **neighbours = malloc(10 * sizeof(char*));
        char *key = lines[i];
        char *end_of_key = strchr(lines[i], ' ');
        *end_of_key = '\0';

        //split end_of_key -> by the delimiter ", " and populate neighbour array with result strings
        char *neighbour = strtok(end_of_key + 4, ", ");
        int j = 0;
        while (neighbour != NULL)
        {
            neighbours[j++] = neighbour;
            neighbour = strtok(NULL, ", ");
        }
        neighbours[j] = NULL;
        shput(adj, key, neighbours);
    }

    Node_To_State *state = create_new_state_dict(adj);

}