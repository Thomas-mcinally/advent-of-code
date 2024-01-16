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
    char *origin;
    char *destination;
    char type;
} Pulse;

typedef struct {
    char *key;
    char **value;
} Node_To_Neighbours;


typedef struct {
    char type;
    int on; // 0 or 1. Relevant for flipflop nodes
    char last_sent_pulse_type; // L or H
} Module_State;

// State of each node. Max 10 neighbours.
typedef struct {
    char *key;
    Module_State *value;
} Node_To_State;

Pulse *create_new_pulse(char *origin, char *destination, char type)
{
    Pulse *pulse = malloc(sizeof(Pulse));
    pulse->origin = origin;
    pulse->destination = destination;
    pulse->type = type;
    return pulse;
}

Node_To_State *create_new_state_dict(char **lines, int linecount)
{
    Node_To_State *state = NULL;
    for (int i = 0; i < linecount; i++)
    {
        Module_State *value = malloc(sizeof(Module_State));
        char *key = lines[i];
        value->type = key[0];
        value->on = 0;
        value->last_sent_pulse_type = 'L';
        shput(state, key+1, value);
    }

    Module_State *button_state = malloc(sizeof(Module_State));
    button_state->type = '-';
    button_state->on = 0;
    button_state->last_sent_pulse_type = 'L';
    shput(state, "button", button_state);
    
    return state;
}

void free_state_dict(Node_To_State *state)
{
    for (int i = 0; i < shlen(state); i++)
    {
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
        if (state1[i].value->last_sent_pulse_type != state2[i].value->last_sent_pulse_type) return 0;
    }
    return 1;
}

Node_To_Neighbours *create_adjacency_list(char **lines, int linecount)
{
    Node_To_Neighbours *adj = NULL;
    for (int i = 0; i < linecount; i++)
    {
        char **neighbours = malloc(10 * sizeof(char*));
        char *key = lines[i];
        char *end_of_key = strchr(lines[i], ' ');
        *end_of_key = '\0';

        char *neighbour = strtok(end_of_key + 4, ", ");
        int j = 0;
        while (neighbour != NULL)
        {
            neighbours[j++] = neighbour;
            neighbour = strtok(NULL, ", ");
        }
        neighbours[j] = NULL;
        shput(adj, key+1, neighbours);
    }
    return adj;
}

void free_adjacency_list(Node_To_Neighbours *adj)
{
    for (int i = 0; i < shlen(adj); i++) free(adj[i].value);
    shfree(adj);
}

void modify_state(Node_To_State *state, char *pulse_dest, char pulse_type, char *pulse_origin)
{
    Module_State *dest_state = shget(state, pulse_dest);
    Module_State *origin_state = shget(state, pulse_origin);
    if ((dest_state->type == '%') && (pulse_type == 'L')){
        dest_state->on = !dest_state->on;
        return;
    }

    if (origin_state->type == '&' || origin_state->type == '%') {
        origin_state->last_sent_pulse_type = pulse_type;
    }
}

Pulse **add_new_pulses_to_queue(Node_To_Neighbours *adj, Node_To_State *state, char *pulse_dest, char pulse_type, Pulse **queue)
{
    Module_State *dest_state = shget(state, pulse_dest);

    int pulse_type_to_send;
    if (dest_state->type == '%'){
        if (pulse_type == 'L') pulse_type_to_send = dest_state->on ? 'H' : 'L';
        else return queue;
    }
    else if (dest_state->type == '&'){
        // TODO: Make more efficient by having quick way to lookup if all_recent_were_high
        int all_recent_were_high = 1;
        for (int i=0; i < shlen(adj); i++){
            char **node_neighbours = adj[i].value;
            while (*node_neighbours != NULL){
                if (strcmp(*node_neighbours, pulse_dest) == 0){
                    Module_State *neighbour_state = shget(state, adj[i].key);
                    if (neighbour_state->last_sent_pulse_type == 'L') all_recent_were_high = 0;
                }
                node_neighbours++;
            }
        }
        pulse_type_to_send = all_recent_were_high ? 'L' : 'H';
    }
    else {
        //broadcaster
        pulse_type_to_send = pulse_type;
    }

    char **dest_neighbours = shget(adj, pulse_dest);
    while (*dest_neighbours != NULL){
        Pulse *new_pulse = create_new_pulse(pulse_dest, *dest_neighbours, pulse_type_to_send);

        arrput(queue, new_pulse);
        dest_neighbours++;
    }

    return queue;
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

    Node_To_Neighbours *adj = create_adjacency_list(lines, linecount);
    Node_To_State *start_state = create_new_state_dict(lines, linecount);



    // ###### BFS LOGIC
    size_t low_pulse_count = 0;
    size_t high_pulse_count = 0;
    size_t button_press_count = 0;
    Node_To_State *current_state = create_new_state_dict(lines, linecount);
        
    while (button_press_count < 1000){
        button_press_count += 1;

        Pulse **queue = NULL;
        Pulse *start_pulse = create_new_pulse("button", "broadcaster", 'L');
        arrput(queue, start_pulse);

        while (arrlen(queue) > 0){ 
            Pulse *current = queue[0];
            arrdel(queue, 0); // TODO: make more efficient with queue Data structure or with level-order traversal
            printf("processing pulse with destination: %s\n", current->destination);
            if (current->type == 'L') low_pulse_count += 1;
            else high_pulse_count += 1;
            modify_state(current_state, current->destination, current->type, current->origin);

            printf("len_queue_before: %zu\n", arrlen(queue));
            queue = add_new_pulses_to_queue(adj, current_state, current->destination, current->type, queue);
            printf("len_queue_after: %zu\n", arrlen(queue));

            free(current);
        }
        if (are_state_dicts_identical(start_state, current_state)) break;
    }
    printf("pressed button %zu times before found loop\n", button_press_count);
    printf("low_pulse_count: %zu\n", low_pulse_count);
    printf("high_pulse_count: %zu\n", high_pulse_count);
    if (1000 % button_press_count != 0){
        printf("Error, button_press_count does not divide 1000\n");
        exit(1);
    }

    size_t result = (1000 / button_press_count) * (1000 / button_press_count) * low_pulse_count * high_pulse_count;
    printf("part1 result: %zu\n", result);


    // ###### END BFS LOGIC
    free_adjacency_list(adj);
    for (int i = 0; i < linecount; i++) free(lines[i]);
    free(lines);
    free_state_dict(start_state);
}

