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


valid_new_obstacle_positions = list()
seen = set() #(r,c,dir)
def explore(r,c, dir, new_obstacle_r, new_obstacle_c):
    if (r,c,dir) in seen:
        valid_new_obstacle_positions.append((new_obstacle_r, new_obstacle_c))
        return
    
    dr, dc = DIR_TO_DELTAS[dir]
    next_r, next_c = r+dr, c+dc
    if next_r < 0 or next_c < 0 or next_r >= ROWS or next_c >= COLS:
        return
    
    seen.add((r,c,dir))
    if grid[next_r][next_c] == "#" or (next_r == new_obstacle_r and next_c==new_obstacle_c):
        explore(r, c, (dir+1)%4, new_obstacle_r, new_obstacle_c)
    else:
        explore(next_r, next_c, dir, new_obstacle_r, new_obstacle_c)
        if (
            (new_obstacle_r is None) 
            and (next_r, next_c, 0) not in seen 
            and (next_r, next_c, 1) not in seen 
            and (next_r, next_c, 2) not in seen 
            and (next_r, next_c, 3) not in seen
        ):
            explore(r, c, (dir+1)%4, next_r, next_c) #place new obstacle at (next_r, next_c)
    seen.remove((r,c,dir))


start_r, start_c = get_guard_coords()

explore(start_r, start_c, 0, None, None)
print(len(valid_new_obstacle_positions))

# Backtracking solution 
# Max path length is ROWS*COLS and this path can split into 2 separate paths at every step
# O(ROWS^2 * COLS^2)

# WHY ISNT IT WORKING :() ?