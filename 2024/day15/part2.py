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


def push_starting_from(r,left_c,right_c,dr,dc):
    next_r, next_left_c, next_right_c = r+dr, left_c+dc, right_c+dc    
    if dr != 0:
        # pushing up or down
        if grid[next_r][next_left_c] == "[":
            push_starting_from(next_r, next_left_c, next_right_c, dr, dc)
        if grid[next_r][next_left_c] == "]":
            push_starting_from(next_r, next_left_c-1, next_left_c, dr, dc)
        if grid[next_r][next_right_c] == "[":
            push_starting_from(next_r, next_right_c, next_right_c+1, dr, dc)
        if grid[next_r][next_left_c] == "." and grid[next_r][next_right_c] == ".":
            grid[next_r][next_left_c] = "["
            grid[next_r][next_right_c] = "]"
            grid[r][left_c] = "."
            grid[r][right_c] = "."

    elif dc == 1:
        # pushing right
        if grid[r][right_c+1] == "[":
            push_starting_from(r, right_c+1, right_c+2, dr, dc)
        if grid[r][right_c+1] == ".":
            grid[r][right_c+1] = "]"
            grid[r][right_c] = "["
            grid[r][left_c] = "."
    elif dc == -1:
        # pushing left
        if grid[r][left_c-1] == "]":
            push_starting_from(r, left_c-2, left_c-1, dr, dc)
        if grid[r][left_c-1] == ".":
            grid[r][left_c-1] = "["
            grid[r][left_c] = "]"
            grid[r][right_c] = "."
    


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

    if grid[cur_r+dr][cur_c+dc] == "[":
        push_starting_from(cur_r+dr, cur_c+dc, cur_c+dc+1, dr, dc)
    elif grid[cur_r+dr][cur_c+dc] == "]":
        push_starting_from(cur_r+dr, cur_c+dc-1, cur_c+dc, dr, dc)

    if grid[cur_r+dr][cur_c+dc] == ".":
        grid[cur_r][cur_c] = "."
        grid[cur_r+dr][cur_c+dc] = "@"
        cur_r += dr
        cur_c += dc
print(get_grid_score())


# debug
    # 1447376 too high

    # If pushing two or moore blocks in a row up or down, one of them getting stuck means that all get stuck