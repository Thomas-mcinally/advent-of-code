from collections import defaultdict
from copy import deepcopy
import random

# General solution possible with Kergers mincut algo
# Implemented in python because got lazy

adjacency_list = defaultdict(lambda: defaultdict(int))  # {node: {neighbor: edge_count}}
input_lines = open('input.txt').read().splitlines()

for line in input_lines:
    start, neighbours_string = line.split(":")
    neighbours = neighbours_string.strip().split(" ")

    for neighbour in neighbours:
        adjacency_list[start][neighbour] = 1
        adjacency_list[neighbour][start] = 1



min_cut = float("inf")
while min_cut != 3:
    adjacency_list_copy = deepcopy(adjacency_list)
    node_to_absorbed_nodes = {key: 1 for key in adjacency_list}
    while len(adjacency_list_copy) > 2:
        # select random key from adjacency list
        start = random.choice(list(adjacency_list_copy.keys()))
        start_neighbours = adjacency_list_copy[start]

        finish = random.choice(list(start_neighbours.keys()))
        finish_neighbours = adjacency_list_copy[finish]

        # remove "finish" node and redirect edges to/from it
        for key, value in finish_neighbours.items():
            del adjacency_list_copy[key][finish]
            if key == start: continue
            start_neighbours[key] += value
            adjacency_list_copy[key][start] += value


        node_to_absorbed_nodes[start] += node_to_absorbed_nodes[finish]
        del adjacency_list_copy[finish]
        del node_to_absorbed_nodes[finish]
    
    node1, node2 = [key for key in adjacency_list_copy.keys()]
    if adjacency_list_copy[node1][node2] < min_cut:
        min_cut = adjacency_list_copy[node1][node2]
        partition1 = node_to_absorbed_nodes[node1]
        partition2 = node_to_absorbed_nodes[node2]


print("min cut found")
print(partition1*partition2)
print(partition1)
print(partition2)
print(min_cut)


