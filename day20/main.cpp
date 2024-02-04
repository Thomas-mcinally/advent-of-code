#include <cstring>
#include <string>
#include <vector>
#include <unordered_map>
#include <deque>

#include "aoc_lib.h"

struct Pulse {
    std::string origin;
    std::string destination;
    char type;
};

struct Module_State {
    char type;
    int on; // 0 or 1. Relevant for flipflop nodes
    char last_sent_pulse_type; // L or H
};

std::unordered_map<std::string, Module_State> create_new_state_dict(char **lines, int linecount) {
    std::unordered_map<std::string, Module_State> state;
    for (int i = 0; i < linecount; i++) {
        std::string line = lines[i];
        if (line[0] != '&' && line[0] != '%') continue; //broadcaster
        Module_State value;
        value.type = line[0];
        value.on = 0;
        value.last_sent_pulse_type = 'L';
        state[line.substr(1)] = value;
    }

    Module_State button_state;
    button_state.type = '-';
    button_state.on = 0;
    button_state.last_sent_pulse_type = 'L';
    state["button"] = button_state;

    Module_State broadcaster_state;
    broadcaster_state.type = '-';
    broadcaster_state.on = 0;
    broadcaster_state.last_sent_pulse_type = 'L';
    state["broadcaster"] = broadcaster_state;

    return state;
}

std::unordered_map<std::string, std::vector<std::string>>create_adjacency_list(char **lines, int linecount)
{
    std::unordered_map<std::string, std::vector<std::string>> adj;
    for (int i = 0; i < linecount; i++)
    {
        std::vector<std::string> neighbours;
        char *key = lines[i];
        char *end_of_key = strchr(lines[i], ' ');
        *end_of_key = '\0';

        char *neighbour = strtok(end_of_key + 4, ", ");
        while (neighbour != NULL)
        {
            neighbours.push_back(neighbour);
            neighbour = strtok(NULL, ", ");
        }
        if (key[0] == '&' || key[0] == '%') adj[key+1] = neighbours;
        else adj[key] = neighbours; //broadcaster
    }
    return adj;
}

void modify_state(std::unordered_map<std::string, Module_State>& state, std::string& pulse_dest, char pulse_type, std::string& pulse_origin)
{
    if (state.count(pulse_dest) == 0) return; // dest node has no neighbours. E.g. "output", "button"
    Module_State& dest_state = state[pulse_dest];
    if ((dest_state.type == '%') && (pulse_type == 'L')){
        dest_state.on = !dest_state.on;
        return;
    }

    if (state.count(pulse_origin) == 0) return; //origin has no state. 
    Module_State& origin_state = state[pulse_origin];
    if (origin_state.type == '&' || origin_state.type == '%') {
        origin_state.last_sent_pulse_type = pulse_type;
    }
}

void add_new_pulses_to_queue(std::unordered_map<std::string, std::vector<std::string>>& adj, std::unordered_map<std::string, Module_State>& state, std::string& pulse_dest, char pulse_type, std::deque<Pulse>& queue)
{
    if (adj.count(pulse_dest) == 0) return; // dest node has no neighbours. E.g. "output"
    Module_State& dest_state = state[pulse_dest];

    char pulse_type_to_send;
    if (dest_state.type == '%'){
        if (pulse_type == 'L') pulse_type_to_send = dest_state.on ? 'H' : 'L';
        else return;
    }
    else if (dest_state.type == '&'){
        // TODO: Make more efficient by having quick way to lookup if all_recent_were_high
        int all_recent_were_high = 1;
        for (const auto& pair : adj){
            const std::vector<std::string>& node_neighbours = pair.second;
            for (const auto &neighbour : node_neighbours){
                if (neighbour == pulse_dest){
                    Module_State& neighbour_state = state[pair.first];
                    if (neighbour_state.last_sent_pulse_type == 'L') all_recent_were_high = 0;
                }
            }

        }
        pulse_type_to_send = all_recent_were_high ? 'L' : 'H';
    }
    else {
        //broadcaster
        pulse_type_to_send = pulse_type;
    }

    std::vector<std::string>& dest_neighbours = adj[pulse_dest];
    for (const std::string& neighbour : dest_neighbours){
        Pulse new_pulse;
        new_pulse.origin = pulse_dest;
        new_pulse.destination = neighbour;
        new_pulse.type = pulse_type_to_send;

        queue.push_back(new_pulse);
    }

    return;
}

int main(int argc, char **argv) {
    if (argc != 2)
    {
        fprintf(stderr, "Please provide a single argument: the path to the file you want to parse\n");
        exit(1);
    }

    char *file_path = argv[1];
    char **lines = NULL;
    int linecount = read_file_to_lines(&lines, file_path);
    std::unordered_map<std::string, std::vector<std::string>> node_to_adj = create_adjacency_list(lines, linecount);
    std::unordered_map<std::string, Module_State> node_to_state = create_new_state_dict(lines, linecount);

    size_t low_pulse_count = 0;
    size_t high_pulse_count = 0;
    std::deque<Pulse> queue;
    for (int _ = 0; _ < 1000; _++){

        Pulse new_pulse;
        new_pulse.origin = "button";
        new_pulse.destination = "broadcaster";
        new_pulse.type = 'L';

        queue.push_back(new_pulse);

        while (queue.size() > 0){ 
            Pulse current = queue.front();
            queue.pop_front();
            if (current.type == 'L') low_pulse_count += 1;
            else high_pulse_count += 1;
            
            modify_state(node_to_state, current.destination, current.type, current.origin);
            add_new_pulses_to_queue(node_to_adj, node_to_state, current.destination, current.type, queue);
        }
    }

    printf("Part1 sol: %zu\n", low_pulse_count * high_pulse_count);
}