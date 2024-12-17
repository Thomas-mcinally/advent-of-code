import re


COLS = 101
ROWS = 103
SECONDS_PASSED = 100

with open("input.txt") as f:
    s = f.read().strip()
robots = []
for line in s.splitlines():
    c, r, dc, dr = (int(num) for num in re.findall(r'(-?\d+)', line))
    robots.append((c,r,dc,dr))

q1, q2, q3, q4 = 0, 0, 0, 0
for c, r, dc, dr in robots:
    final_c = (c + dc * SECONDS_PASSED) % COLS
    final_r = (r + dr * SECONDS_PASSED) % ROWS

    if final_c <= COLS//2-1 and final_r <= ROWS//2-1:
        q1 += 1
    elif final_c >= COLS - COLS//2 and final_r <= ROWS//2-1:
        q2 += 1
    elif final_c <= COLS//2-1 and final_r >= ROWS - ROWS//2:
        q3 += 1
    elif final_c >= COLS - COLS//2 and final_r >= ROWS - ROWS//2:
        q4 += 1

print(q1*q2*q3*q4)
