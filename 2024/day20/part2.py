import collections


def find_start(grid: list[str]) -> tuple:
    ROWS, COLS = len(grid), len(grid[0])
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "S":
                return r,c

def find_shortest_paths(grid: list[str]) -> dict:
    ROWS, COLS = len(grid), len(grid[0])
    start_r, start_c = find_start(grid)
    coords_to_shortest_path = {}
    q = collections.deque([(start_r, start_c,0)]) #(r,c,depth)
    while q:
        r,c,depth = q.popleft()
        if r < 0 or c < 0 or r >= ROWS or c >= COLS or (r,c) in coords_to_shortest_path or grid[r][c] == "#":
            continue
        coords_to_shortest_path[(r,c)] = depth
        for next_r, next_c in [(r+1,c), (r-1,c), (r,c+1), (r,c-1)]:
            q.append((next_r,next_c,depth+1))
    
    return coords_to_shortest_path

def count_good_cheats_starting_from(grid, coords_to_shortest_path, start_r,start_c):
    ROWS, COLS = len(grid), len(grid[0])
    cheat_end_positions = collections.defaultdict(lambda: float("inf")) #required cheat duration is min val needed for this (end_r, end_c)
    for delta_c in range(20 + 1):
        for delta_r in range((20)-delta_c + 1):
            cheat_end_positions[(start_r+delta_r, start_c+delta_c)] = min(delta_c+delta_r, cheat_end_positions[(start_r+delta_r, start_c+delta_c)])
            cheat_end_positions[(start_r+delta_r, start_c-delta_c)] = min(delta_c+delta_r, cheat_end_positions[(start_r+delta_r, start_c-delta_c)])
            cheat_end_positions[(start_r-delta_r, start_c+delta_c)] = min(delta_c+delta_r, cheat_end_positions[(start_r-delta_r, start_c+delta_c)])
            cheat_end_positions[(start_r-delta_r, start_c-delta_c)] = min(delta_c+delta_r, cheat_end_positions[(start_r-delta_r, start_c-delta_c)])
    good_cheats = 0
    for [end_r, end_c], cheat_duration in cheat_end_positions.items():
        if end_r < 0 or end_c < 0 or end_r >= ROWS or end_c >= COLS or grid[end_r][end_c] == "#":
            continue
        savings = coords_to_shortest_path[(end_r, end_c)] - coords_to_shortest_path[(start_r, start_c)]-cheat_duration
        if savings >= 100:
            good_cheats += 1
    
    return good_cheats


with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()
grid = [[char for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])
coords_to_shortest_path = find_shortest_paths(grid)

total_good_cheats = 0
for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] == "#":
            continue
        total_good_cheats += count_good_cheats_starting_from(grid, coords_to_shortest_path, r, c)
print(total_good_cheats)