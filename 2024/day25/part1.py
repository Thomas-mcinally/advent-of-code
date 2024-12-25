with open("input.txt") as f:
    s = f.read().strip()

blocks = s.split("\n\n")

keys = [] #list[list[int]]
locks = []

for block in blocks:
    lines = block.splitlines()
    heights = [0 for _ in range(len(lines))]
    for line in lines:
        for i, char in enumerate(line):
            heights[i] += 1 if char == "#" else 0
    
    if lines[0][0] == ".":
        keys.append(heights)
    else:
        locks.append(heights)

good = 0
for lock in locks:
    for key in keys:
        if all(h1+h2 <= 7 for h1,h2 in zip(lock, key)):
            good += 1
print(good) 
    
