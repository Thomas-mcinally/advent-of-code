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
            while node_in_bounds(r,c):
                antinode_locations.add((r,c))
                r += dr
                c += dc
            
            r, c = r1, c1
            while node_in_bounds(r,c):
                antinode_locations.add((r,c))
                r -= dr
                c -= dc
            

print(len(antinode_locations))