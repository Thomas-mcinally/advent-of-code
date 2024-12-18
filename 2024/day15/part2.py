# DOESNT WORK YET


with open("small_input.txt") as f:
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

def push_starting_from(r,c,dr,dc):
    # Need to update this to work for expanded grid.
    # look for [] instead of O and modify movement logic
    if grid[r][c] != "O" or r+dr < 0 or r+dr>=ROWS or c+dc < 0 or c+dc>=COLS:
        return
    push_starting_from(r+dr, c+dc, dr, dc)
    if grid[r+dr][c+dc] == ".":
        grid[r+dr][c+dc] = "O"
        grid[r][c] = "."

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
cur_r, cur_c = get_start_pos()
for move in instructions:
    dr, dc = MOVE_TO_DR_DC[move]

    push_starting_from(cur_r+dr, cur_c+dc, dr, dc)
    if grid[cur_r+dr][cur_c+dc] == ".":
        grid[cur_r][cur_c] = "."
        grid[cur_r+dr][cur_c+dc] = "@"
        cur_r += dr
        cur_c += dc
print(get_grid_score())
# Doesnt work because i havent accounted for:
    # Pushing right side of box up also pushes the left side up
