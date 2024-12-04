with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

grid = [[char for char in line] for line in lines]
ROWS = len(grid)
COLS = len(grid[0])


def x_mas_present(r: int, c: int):
    if r < 1 or r > ROWS-2 or c < 1 or c > COLS-2 or grid[r][c] != "A":
        return False
    diag1 = {grid[r-1][c-1], grid[r+1][c+1]}
    diag2 = {grid[r-1][c+1], grid[r+1][c-1]}
    return diag1 == diag2 == {"M", "S"}



xmas_count = 0
for r in range(ROWS):
    for c in range(COLS):
        if x_mas_present(r,c):
            xmas_count += 1

print(xmas_count)