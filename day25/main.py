from collections import defaultdict
from copy import deepcopy
from random import randint

# General solution possible with Kergers mincut algo
# Implement Kergers in python first to get a working version, do it in C afterwards

# Doesnt work yet :()


adjacency_list = defaultdict(lambda: defaultdict(int))  # {node: {neighbor: edge_count}}
input_lines = open('input.txt').read().splitlines()

for line in input_lines:
    start, neighbours_string = line.split(":")
    neighbours = neighbours_string.strip().split(" ")

    for neighbour in neighbours:
        adjacency_list[start][neighbour] += 1
        adjacency_list[neighbour][start] += 1


min_cut = 0
iterations = 0
while iterations < 1000 and min_cut != 3:
    adjacency_list_copy = deepcopy(adjacency_list)
    while len(adjacency_list_copy) > 2:
        # select random key from adjacency list
        start = list(adjacency_list_copy.keys())[randint(0, len(adjacency_list_copy) - 1)]
        start_neighbours = adjacency_list_copy[start]

        finish = list(start_neighbours.keys())[randint(0, len(start_neighbours) - 1)]
        finish_neighbours = adjacency_list_copy[finish]

        # make neighbours of finish neighbours of start instead
        for key, value in finish_neighbours.items():
            del adjacency_list_copy[key][finish]
            if key == start: continue
            start_neighbours[key] += value
            adjacency_list_copy[key][start] += value


        del adjacency_list_copy[finish]
    
    iterations += 1
    node1, node2 = [key for key in adjacency_list_copy.keys()]
    min_cut = adjacency_list_copy[node1][node2]






