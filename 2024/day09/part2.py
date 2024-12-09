with open("input.txt") as f:
    s = f.read().strip()
file_id_to_info = {} #id: (start_idx, size)
disk = []
for i in range(0, len(s), 2):
    file_id_to_info[i//2] = (len(disk), int(s[i]))
    for _ in range(int(s[i])):
        disk.append(i//2)
    if i+1 < len(s):
        for _ in range(int(s[i+1])):
            disk.append(".")
disk_i_to_runlength = [1 for _ in range(len(disk))]
for i in range(len(disk)-2, -1, -1):
    if disk[i] == disk[i+1]:
        disk_i_to_runlength[i] += disk_i_to_runlength[i+1]

cur_file = max(file_id_to_info.keys())
while cur_file >= 0:
    old_start_idx, file_size = file_id_to_info[cur_file]
    new_start_i = 0
    while new_start_i < old_start_idx:
        if disk[new_start_i] == "." and disk_i_to_runlength[new_start_i] >= file_size:
            for i in range(new_start_i, new_start_i+file_size):
                disk[i] = cur_file
            for i in range(old_start_idx, old_start_idx+file_size):
                disk[i] = "."
            break
        new_start_i += 1
    cur_file -= 1

    

checksum = 0
for i, num in enumerate(disk):
    if num == ".":
        continue
    checksum += i*num

print(checksum)