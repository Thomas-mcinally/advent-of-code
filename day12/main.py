from collections import defaultdict


def dfs(s: str, key: list[int], i: int, j: int, dot_count_s: list[int], cache: list[int]) -> int:
    if j==len(key):
        if i >= len(s):
            return 1
        if s[i] != "#":
            return dfs(s, key, i+1, j, dot_count_s, cache)
        return 0

    if i+key[j] > len(s):
        return 0
    if cache[i*len(key)+j] != 0:
        return cache[i*len(key)+j]


    if (
        s[i] != "."
        and dot_count_s[i] == dot_count_s[i+key[j]-1] 
        and (i+key[j] == len(s) or s[i+key[j]] != "#")
        ):
        cache[i*len(key)+j] += dfs(s, key, i+key[j]+1, j+1, dot_count_s, cache)
    if s[i] != "#":
        cache[i*len(key)+j] += dfs(s, key, i+1, j, dot_count_s, cache)
    return cache[i*len(key)+j]

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
    cache = [0] * (len(s)*len(key))
    total += dfs(s, key, 0, 0, dot_s_count, cache)



    s_part_2 = "?".join([s]*5)
    key_part_2 = key*5
    dot_s_count_part_2 = [1 if char == "." else 0 for char in s_part_2]
    cache_2 = [0] * (len(s_part_2)*len(key_part_2))
    for i in range(1,len(dot_s_count_part_2)):
        dot_s_count_part_2[i] += dot_s_count_part_2[i-1]
    total_2 += dfs(s_part_2, key_part_2, 0, 0, dot_s_count_part_2, cache_2)
print(total)
print(total_2)

