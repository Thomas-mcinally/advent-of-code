from collections import defaultdict


def dfs(s: str, key: list[int], i: int, j: int, dot_count_s: list[int], cache: dict) -> int:
    if i >= len(s) and j==len(key):
        return 1
    if i >= len(s):
        return 0
    if j >= len(key):
        if s[i] != '#':
            return dfs(s, key, i+1, j, dot_count_s, cache)
        return 0
    if i+key[j] > len(s):
        return 0
    if (i,j) in cache:
        return cache[(i,j)]


    if (
        s[i] != "." 
        and dot_count_s[i] == dot_count_s[i+key[j]-1] 
        and (i+key[j] == len(s) or s[i+key[j]] != "#")
        ):
        cache[(i,j)] += dfs(s, key, i+key[j]+1, j+1, dot_count_s, cache)
    if s[i] != "#":
        cache[(i,j)] += dfs(s, key, i+1, j, dot_count_s, cache)
    return cache[(i,j)]

with open("input.txt", "r") as file:
    input = file.read().splitlines()
total = 0
total_2 = 0
for line in input:
    s, key = line.split(" ")
    key = [int(x) for x in key.split(",")]

    dot_s_count = [1 if char == "." else 0 for char in s]
    for i in range(1,len(dot_s_count)):
        dot_s_count[i] += dot_s_count[i-1]

    total += dfs(s, key, 0, 0, dot_s_count, defaultdict(int))



    s_part_2 = "?".join([s]*5)
    key_part_2 = key*5
    dot_s_count_part_2 = [1 if char == "." else 0 for char in s_part_2]
    for i in range(1,len(dot_s_count_part_2)):
        dot_s_count_part_2[i] += dot_s_count_part_2[i-1]
    total_2 += dfs(s_part_2, key_part_2, 0, 0, dot_s_count_part_2, defaultdict(int))
print(total)
print(total_2)

