with open("input.txt") as f:
    s = f.read().strip()
map, instructions = s.split("\n\n")
instructions = [char for char in instructions if char != "\n"]
grid = [[char for char in line] for line in map.splitlines()]
ROWS, COLS = len(grid), len(grid[0])
MOVE_TO_DR_DC = {
    "<": ( 0,-1),
    ">": ( 0, 1),
    "^": (-1, 0),
    "v": ( 1, 0)
}


def push_starting_from(r,c_frontier: set,dr,dc):
    next_r = r+dr    
    if dr != 0:
        # pushing up or down
        if any(grid[next_r][c] == "#" for c in c_frontier):
            # blocked
            return
        if any(grid[next_r][c] in "[]" for c in c_frontier):
            next_c_frontier = set()
            for c in c_frontier:
                if grid[next_r][c] == "[":
                    next_c_frontier.add(c)
                    next_c_frontier.add(c+1)
                elif grid[next_r][c] == "]":
                    next_c_frontier.add(c)
                    next_c_frontier.add(c-1)
            push_starting_from(next_r, next_c_frontier, dr, dc)
        
        if all(grid[next_r][c] == "." for c in c_frontier):
            for c in c_frontier:
                grid[next_r][c] = grid[r][c]
                grid[r][c] = "."

    elif dc == 1:
        # pushing right 
        front_c = next(c for c in c_frontier if grid[r][c] == "]")
        if grid[r][front_c+1] == "[":
            push_starting_from(r, {front_c+2}, dr, dc)
        if grid[r][front_c+1] == ".":
            grid[r][front_c+1] = "]"
            grid[r][front_c] = "["
            grid[r][front_c-1] = "."
    elif dc == -1:
        # pushing left
        front_c = next(c for c in c_frontier if grid[r][c] == "[")
        if grid[r][front_c-1] == "]":
            push_starting_from(r, {front_c-2}, dr, dc)
        if grid[r][front_c-1] == ".":
            grid[r][front_c-1] = "["
            grid[r][front_c] = "]"
            grid[r][front_c+1] = "."
    


def get_start_pos():
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "@":
                return (r,c)
    raise

def get_grid_score():
    score = 0
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] != "[":
                continue
            score += 100*r + c
    return score

def resize_grid():
    global COLS
    global grid
    new_grid = [["." for _ in range(COLS*2)] for _ in range(ROWS)]
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "#":
                new_grid[r][c*2] = "#"
                new_grid[r][c*2+1] = "#"
            elif grid[r][c] == "O":
                new_grid[r][c*2] = "["
                new_grid[r][c*2+1] = "]"
            elif grid[r][c] == "@":
                new_grid[r][c*2] = "@"

    grid = new_grid
    COLS = len(grid[0])

resize_grid()
total_moves = len(instructions)
cur_r, cur_c = get_start_pos()
for i, move in enumerate(instructions):
    dr, dc = MOVE_TO_DR_DC[move]

    if grid[cur_r+dr][cur_c+dc] == "[":
        push_starting_from(cur_r+dr, {cur_c+dc, cur_c+dc+1}, dr, dc)
    elif grid[cur_r+dr][cur_c+dc] == "]":
        push_starting_from(cur_r+dr, {cur_c+dc-1, cur_c+dc}, dr, dc)

    if grid[cur_r+dr][cur_c+dc] == ".":
        grid[cur_r][cur_c] = "."
        grid[cur_r+dr][cur_c+dc] = "@"
        cur_r += dr
        cur_c += dc

print(get_grid_score())
