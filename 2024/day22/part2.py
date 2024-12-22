
from collections import defaultdict


def mix(secret, value):
    return secret^value

def prune(secret):
    MOD = 16777216
    return secret % MOD

def get_next_secret(start: int) -> int:
    cur = prune(mix(start, start*64))
    cur = prune(mix(cur, cur//32))
    cur = prune(mix(cur, cur * 2048))
    return cur

with open("input.txt") as f:
    s = f.read().strip()
start_nums = [int(num) for num in s.splitlines()]

sequence_to_bananas = defaultdict(int)
for start in start_nums:
    seen_delta_sequences = set()
    delta_sequence = []
    cur = start
    for _ in range(2000):
        nxt = get_next_secret(cur)
        delta = (nxt%10) - (cur%10)
        delta_sequence.append(delta)
        cur = nxt
        if len(delta_sequence) > 4:
            delta_sequence.pop(0)
        if len(delta_sequence) == 4 and tuple(delta_sequence) not in seen_delta_sequences:
            seen_delta_sequences.add(tuple(delta_sequence))
            sequence_to_bananas[tuple(delta_sequence)] += (nxt%10)

result = max(sequence_to_bananas.values())
print(result)