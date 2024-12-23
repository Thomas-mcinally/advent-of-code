from collections import defaultdict

with open("input.txt") as f:
    s = f.read().strip()
edges = [line.split("-") for line in s.splitlines()]
adj = defaultdict(set)
for a,b in edges:
    adj[a].add(b)
    adj[b].add(a)
nodes = [node for node in adj.keys()]

largest_group = set()
def construct_group_starting_from(i: int, group: set) -> None:
    if i == len(nodes):
        global largest_group
        if len(group) > len(largest_group):
            largest_group = group.copy()
        return
    
    construct_group_starting_from(i+1, group)
    if all(nodes[i] in adj[cur] for cur in group):
        group.add(nodes[i])
        construct_group_starting_from(i+1, group)
        group.remove(nodes[i])

construct_group_starting_from(0, set())

print(",".join(sorted([name for name in largest_group])))