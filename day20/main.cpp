#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#include "aoc_lib.h"

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

typedef struct {
    const char *origin;
    const char *destination;
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

typedef struct {
    char *key;
    Module_State *value;
} Node_To_State;

Pulse *create_new_pulse(const char *origin, const char *destination, char type)
{
    Pulse *pulse = (Pulse*)malloc(sizeof(Pulse));
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
        char *key = lines[i];
        if (key[0] != '&' && key[0] != '%') continue;
        Module_State *value = (Module_State*)malloc(sizeof(Module_State));
        value->type = key[0];
        value->on = 0;
        value->last_sent_pulse_type = 'L';
        shput(state, key+1, value);
    }

    Module_State *button_state = (Module_State*)malloc(sizeof(Module_State));
    button_state->type = '-';
    button_state->on = 0;
    button_state->last_sent_pulse_type = 'L';
    shput(state, "button", button_state);

    Module_State *broadcaster_state = (Module_State*)malloc(sizeof(Module_State));
    broadcaster_state->type = '-';
    broadcaster_state->on = 0;
    broadcaster_state->last_sent_pulse_type = 'L';
    shput(state, "broadcaster", broadcaster_state);


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

Node_To_Neighbours *create_adjacency_list(char **lines, int linecount)
{
    Node_To_Neighbours *adj = NULL;
    for (int i = 0; i < linecount; i++)
    {
        char **neighbours = (char**)malloc(10 * sizeof(char*));
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
        if (key[0] == '&' || key[0] == '%') shput(adj, key+1, neighbours);
        else shput(adj, key, neighbours); //broadcaster
    }
    return adj;
}

void free_adjacency_list(Node_To_Neighbours *adj)
{
    for (int i = 0; i < shlen(adj); i++) free(adj[i].value);
    shfree(adj);
}

void modify_state(Node_To_State *state, const char *pulse_dest, char pulse_type, const char *pulse_origin)
{
    if (shgeti(state, pulse_dest) == -1) return; // dest node has no neighbours. E.g. "output", "button"
    Module_State *dest_state = shget(state, pulse_dest);
    if ((dest_state->type == '%') && (pulse_type == 'L')){
        dest_state->on = !dest_state->on;
        return;
    }

    if (shgeti(state, pulse_origin) == -1) return; //origin has no state. 
    Module_State *origin_state = shget(state, pulse_origin);
    if (origin_state->type == '&' || origin_state->type == '%') {
        origin_state->last_sent_pulse_type = pulse_type;
    }
}

Pulse **add_new_pulses_to_queue(Node_To_Neighbours *adj, Node_To_State *state, const char *pulse_dest, char pulse_type, Pulse **queue)
{
    if (shgeti(adj, pulse_dest) == -1) return queue; // dest node has no neighbours. E.g. "output"
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
    Node_To_Neighbours *node_to_adj = create_adjacency_list(lines, linecount);
    Node_To_State *node_to_state = create_new_state_dict(lines, linecount);

    size_t low_pulse_count = 0;
    size_t high_pulse_count = 0;
    Pulse **queue = NULL;
    for (int _ = 0; _ < 1000; _++){
        Pulse *start_pulse = create_new_pulse("button", "broadcaster", 'L');
        arrput(queue, start_pulse);

        while (arrlen(queue) > 0){ 
            Pulse *current = queue[0];
            arrdel(queue, 0); // TODO: make more efficient with queue Data structure or with level-order traversal

            if (current->type == 'L') low_pulse_count += 1;
            else high_pulse_count += 1;
            modify_state(node_to_state, current->destination, current->type, current->origin);

            queue = add_new_pulses_to_queue(node_to_adj, node_to_state, current->destination, current->type, queue);
            free(current);
        }
    }

    printf("Part1 sol: %zu\n", low_pulse_count * high_pulse_count);


    arrfree(queue);
    free_adjacency_list(node_to_adj);
    free_state_dict(node_to_state);
    for (int i = 0; i < linecount; i++) free(lines[i]);
    free(lines);
}


//Part2 solved graphically. See part2.txt