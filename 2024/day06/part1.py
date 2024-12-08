import sys
sys.setrecursionlimit(10000)

with open("input.txt") as f:
    s = f.read().strip()

lines = s.splitlines()
grid = [[char for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])
DIR_TO_DELTAS = {
    0: (-1, 0), #north
    1: (0, 1),  #east
    2: (1, 0),  #south
    3: (0, -1), #west
}
def get_guard_coords() -> tuple[int, int]:
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "^":
                return r, c


seen = set() #(r,c,dir)
def explore(r,c, dir):
    if (r,c,dir) in seen:
        raise Exception("Cycle found, but None expected")
    seen.add((r,c,dir))

    grid[r][c] = "X"
    dr, dc = DIR_TO_DELTAS[dir]
    next_r, next_c = r+dr, c+dc
    if next_r < 0 or next_c < 0 or next_r >= ROWS or next_c >= COLS:
        return
    if grid[next_r][next_c] == "#":
        explore(r, c, (dir+1)%4)
    else:
        explore(next_r, next_c, dir)



start_r, start_c = get_guard_coords()

explore(start_r,start_c,0)
result = 0
for r in range(ROWS):
    for c in range(COLS):
        result += 1 if grid[r][c] == "X" else 0

print(result)


# DFS sol
# Path never splits
# Max path length ROWS*COLS
# Time O(ROWS*COLS)
# Space O(ROWS*COLS)