
with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

l1, l2 = [], []
for line in lines:
    [item1, item2] = line.split("   ")
    l1.append(int(item1))
    l2.append(int(item2))

l1.sort()
l2.sort()

result = 0
for item1, item2 in zip(l1, l2):
    result += abs(item1 - item2)

print(result)