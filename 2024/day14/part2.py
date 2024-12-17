import re


COLS = 101
ROWS = 103
MAX_SECONDS = 10_000

with open("input.txt") as f:
    s = f.read().strip()
robots = []
for line in s.splitlines():
    c, r, dc, dr = (int(num) for num in re.findall(r'(-?\d+)', line))
    robots.append((c,r,dc,dr))

for seconds_passed in range(MAX_SECONDS+1):
    grid = [[0 for _ in range(COLS)] for _ in range(ROWS)]
    for c, r, dc, dr in robots:
        final_c = (c + dc * seconds_passed) % COLS
        final_r = (r + dr * seconds_passed) % ROWS

        grid[final_r][final_c] += 1
    print("")
    print(f"{seconds_passed} seconds passed")
    for row in grid:
        modified_row = ["#" if item != 0 else " " for item in row]
        print(modified_row)
