from collections import defaultdict

import sys
sys.setrecursionlimit(1000000)


with open("input.txt") as f:
    s = f.read().strip()
sections = s.split("\n\n")
rule_lines = sections[0].splitlines()
rules = [rule.split("|") for rule in rule_lines]
sequences = [[int(num) for num in line.split(",")] for line in sections[1].splitlines()]
adj = defaultdict(list)
for first, second in rules:
    adj[int(second)].append(int(first))

seq_to_start_node = {}
# startnode is the one with indegree of 0
# For each sequence, there should only be one, based on the fact that there is a unique allowed order

for i, seq in enumerate(sequences):
    start_candidates = set(seq)
    for node in seq:
        for neighbour in adj[node]:
            if neighbour in start_candidates:
                start_candidates.remove(neighbour)
    start_node = next(node for node in start_candidates)
    seq_to_start_node[i] = start_node

def topological_search(cur: int, path: list[int], allowed_nodes: set, seen: set) -> None:
    if cur in seen:
        return
    seen.add(cur)
    for neighbour in adj[cur]:
        if neighbour not in allowed_nodes:
            continue
        topological_search(neighbour, path, allowed_nodes, seen)
    path.append(cur)

good_sequences = []
bad_sequences = []
for i, seq in enumerate(sequences):
    allowed_nodes = set(seq)
    start_node = seq_to_start_node[i]
    correct_path = []
    topological_search(start_node, correct_path, allowed_nodes, set())
    if correct_path == seq:
        good_sequences.append(seq)
    else:
        bad_sequences.append(correct_path)

result = sum(seq[len(seq)//2] for seq in good_sequences)
print(result)
result2 = sum(seq[len(seq)//2] for seq in bad_sequences)
print(result2)


