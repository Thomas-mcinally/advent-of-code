from collections import defaultdict
import itertools

with open("input.txt") as f:
    s = f.read().strip()
sections = s.split("\n\n")
rule_lines = sections[0].splitlines()
rules = [rule.split("|") for rule in rule_lines]
sequences = [[int(num) for num in line.split(",")] for line in sections[1].splitlines()]

node_to_banned_after = defaultdict(list)
for first, second in rules:
    node_to_banned_after[int(second)].append(int(first))

def is_sequence_good(sequence):
    banned = set()
    good = True
    for node in sequence:
        if node in banned:
            good = False
            break
        for banned_node in node_to_banned_after[node]:
            banned.add(banned_node)
    return good

bad_sequences = [seq for seq in sequences if not is_sequence_good(seq)]

result = 0
print(f"total bad sequences: {len(bad_sequences)}")
for i, seq in enumerate(bad_sequences):
    print(f"processing sequence: {i}")
    for permutation in itertools.permutations(seq):
        if is_sequence_good(permutation):
            result += permutation[len(permutation)//2]

# TOO SLOW - Probably need to figure out the Topological sort solution
print(result)


# there is a "right" order -> only 1 path through graph for each seq
# -> every node must appear in rules (if it doesnt, the node can appear anywhere in the order and there isnt 1 "right" path)
# -> topological sort across graph then order seq based on this path