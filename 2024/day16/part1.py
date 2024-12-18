import heapq


with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()
grid = [[char for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])
STEP_COST = 1
TURN_COST = 1000
DIR_TO_DELTAS = {
    0: (-1, 0), #north
    1: (0, 1),  #east
    2: (1, 0),  #south
    3: (0, -1), #west
}

def find_start_pos():
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "S":
                return (r,c)
    raise

def dijkstras_shortest_path_to_end_starting_from(start_r, start_c, start_dir):
    seen = set()
    q = [(0, start_r, start_c, start_dir)] #min heap (total_points, r, c, dir)
    while q:
        total_points, r, c, dir = heapq.heappop(q)
        if grid[r][c] == "E":
            return total_points
        if (r,c,dir) in seen or grid[r][c] == "#":
            continue
        seen.add((r,c,dir))

        dr, dc = DIR_TO_DELTAS[dir]
        heapq.heappush(q, (total_points+STEP_COST, r+dr, c+dc, dir))
        heapq.heappush(q, (total_points+TURN_COST, r, c, (dir+1)%4))
        heapq.heappush(q, (total_points+TURN_COST, r, c, (dir-1)%4))
    
    return -1


start_r, start_c = find_start_pos()
print(dijkstras_shortest_path_to_end_starting_from(start_r, start_c, 1))
        
        