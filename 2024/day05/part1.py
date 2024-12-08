from collections import defaultdict


with open("input.txt") as f:
    s = f.read().strip()
sections = s.split("\n\n")
rule_lines = sections[0].splitlines()
rules = [rule.split("|") for rule in rule_lines]
sequences = [[int(num) for num in line.split(",")] for line in sections[1].splitlines()]

node_to_banned_after = defaultdict(set)
for first, second in rules:
    node_to_banned_after[int(second)].add(int(first))

def is_sequence_good(sequence):
    banned = set()
    is_good = True
    for node in sequence:
        if node in banned:
            is_good = False
            break
        banned |= node_to_banned_after[node]
    return is_good

good_sequences = [seq for seq in sequences if is_sequence_good(seq)]
result = sum(seq[len(seq)//2] for seq in good_sequences)
print(result)


# Think this problem is related to Topological sort, but haven't figured out how to apply it