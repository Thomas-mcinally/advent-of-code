import collections

with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

l1, l2 = [], []
for line in lines:
    [item1, item2] = line.split("   ")
    l1.append(int(item1))
    l2.append(int(item2))

l2_counts = collections.Counter(l2)

result = 0
for num in l1:
    result += num*l2_counts[num]

print(result)