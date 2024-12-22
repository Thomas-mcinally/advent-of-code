
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

total = 0
for start in start_nums:
    cur = start
    for _ in range(2000):
        cur = get_next_secret(cur)
    total += cur
print(total)