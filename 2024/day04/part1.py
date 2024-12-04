with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

grid = [[char for char in line] for line in lines]
TARGET_WORD = "XMAS"
ROWS = len(grid)
COLS = len(grid[0])


def word_present_starting_from(r: int, c: int, i: int, dr: int, dc: int):
    if i == len(TARGET_WORD):
        return True
    if r < 0 or c < 0 or r >= ROWS or c >= COLS or grid[r][c] != TARGET_WORD[i]:
        return False

    return word_present_starting_from(r+dr, c+dc, i+1, dr, dc)



xmas_count = 0
for r in range(ROWS):
    for c in range(COLS):
        if word_present_starting_from(r, c, 0, 1, 0):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, -1, 0):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, 0, 1):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, 0, -1):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, 1, 1):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, 1, -1):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, -1, 1):
            xmas_count += 1
        if word_present_starting_from(r, c, 0, -1, -1):
            xmas_count += 1

print(xmas_count)