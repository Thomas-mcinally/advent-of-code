
from collections import defaultdict


with open("input.txt") as f:
    s = f.read().strip()

edges = [line.split("-") for line in s.splitlines()]
adj = defaultdict(set)
for a,b in edges:
    adj[a].add(b)
    adj[b].add(a)
nodes = [key for key in adj.keys()]

valid_triplets = []
for i1 in range(len(nodes)-2):
    for i2 in range(i1+1, len(nodes)-1):
        for i3 in range(i2+1, len(nodes)):
            one, two, three = nodes[i1], nodes[i2], nodes[i3]
            if two in adj[one] and three in adj[one] and three in adj[two] and "t" in [one[0], two[0], three[0]]:
                valid_triplets.append((one, two, three))

print(len(valid_triplets))
