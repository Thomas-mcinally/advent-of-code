with open("input.txt") as f:
    s = f.read().strip()

disk = []
for i in range(0, len(s), 2):
    for _ in range(int(s[i])):
        disk.append(i//2)
    if i+1 < len(s):
        for _ in range(int(s[i+1])):
            disk.append(".")

l, r = 0, len(disk)-1
while l < r:
    while l < len(disk) and disk[l] != ".":
        l += 1
    while r >= 0 and disk[r] == ".":
        r -= 1
    
    if l < len(disk) and r >= 0 and l < r and disk[l] == "." and disk[r] != ".":
        disk[l], disk[r] = disk[r], disk[l]
        l += 1
        r -= 1

checksum = 0
for i, num in enumerate(disk):
    if num == ".":
        continue
    checksum += i*num

print(checksum)