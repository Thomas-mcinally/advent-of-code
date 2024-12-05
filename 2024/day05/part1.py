from collections import defaultdict


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

good_sequences = [seq for seq in sequences if is_sequence_good(seq)]
result = sum(seq[len(seq)//2] for seq in good_sequences)
print(result)


# Think this problem is related to Topological sort, but haven't figured out how to apply it