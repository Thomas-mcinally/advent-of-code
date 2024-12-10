with open("input.txt") as f:
    s = f.read().strip()

lines = s.splitlines()
grid = [[int(char) if char != "." else -1 for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])

def explore(r,c, peaks_found):
    if grid[r][c] == 9:
        peaks_found.add((r,c))
        return
    
    for next_r, next_c in [(r+1,c), (r-1,c), (r, c+1), (r, c-1)]:
        if next_r < 0 or next_r >= ROWS or next_c < 0 or next_c >= COLS or grid[next_r][next_c] != grid[r][c] + 1:
            continue
        explore(next_r, next_c, peaks_found)


result = 0
for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] != 0:
            continue
        peaks_found = set()
        explore(r,c, peaks_found)
        result += len(peaks_found)

print(result)
