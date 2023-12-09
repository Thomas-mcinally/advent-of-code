total = 0

with open("input.txt", "r") as f:
    lines  = f.readlines()

for line in lines:
    digits = [c for c in line if c.isdigit()]
    total += int(digits[0] + digits[-1])

print(total)