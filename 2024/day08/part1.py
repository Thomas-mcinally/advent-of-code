from collections import defaultdict
import sys
sys.setrecursionlimit(10000)

with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

grid = [[char for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])

def node_in_bounds(r,c):
    return 0 <= r < ROWS and  0 <= c < COLS

signal_to_antennas = defaultdict(list)
for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] == ".":
            continue
        signal_to_antennas[grid[r][c]].append((r,c))

antinode_locations = set()
for group in signal_to_antennas.values():
    for i1 in range(len(group)):
        for i2 in range(i1+1, len(group)):
            [r1, c1], [r2, c2] = group[i1], group[i2]
            dr, dc = r2-r1, c2-c1

            r, c = r1, c1

            antinode1_r, antinode1_c = r2+dr, c2+dc
            antinode2_r, antinode2_c = r1-dr, c1-dc
            if node_in_bounds(antinode1_r, antinode1_c):
                antinode_locations.add((antinode1_r, antinode1_c))
            if node_in_bounds(antinode2_r, antinode2_c):
                antinode_locations.add((antinode2_r, antinode2_c))

print(len(antinode_locations))