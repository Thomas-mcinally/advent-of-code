from functools import cache


with open("input.txt") as f:
    s = f.read().strip()

lines = s.splitlines()
grid = [[int(char) if char != "." else -1 for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])

@cache
def explore(r,c):
    if grid[r][c] == 9:
        return 1
    
    result = 0
    for next_r, next_c in [(r+1,c), (r-1,c), (r, c+1), (r, c-1)]:
        if next_r < 0 or next_r >= ROWS or next_c < 0 or next_c >= COLS or grid[next_r][next_c] != grid[r][c] + 1:
            continue
        result += explore(next_r, next_c)
    return result


result = 0
for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] != 0:
            continue
        result += explore(r,c)

print(result)
