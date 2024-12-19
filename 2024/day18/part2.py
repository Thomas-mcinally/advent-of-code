from collections import namedtuple, deque


Point = namedtuple("Point", ["r", "c"])


def shortest_path_length(grid, start: Point, end: Point):
    ROWS, COLS = len(grid), len(grid[0])
    seen = set()
    q = deque([(start, 0)]) #(point, depth)
    while q:
        cur, depth = q.popleft()
        if cur in seen:
            continue
        if cur == end:
            return depth
        seen.add(cur)
        for next_r, next_c in [(cur.r+1, cur.c), (cur.r-1, cur.c), (cur.r, cur.c+1), (cur.r, cur.c-1)]:
            if next_r<0 or next_r>=ROWS or next_c<0 or next_c>=COLS or grid[next_r][next_c] != ".":
                continue
            q.append((Point(next_r, next_c), depth+1))
    return -1


with open("input.txt") as f:
    s = f.read().strip()
corrupted_points = []
for line in s.splitlines():
    r,c = line.split(",")
    corrupted_points.append(Point(int(r), int(c)))

N = 70
grid = [["." for _ in range(N+1)] for _ in range(N+1)]


corrupted_bytes = 1
while True:
    corrupted_point = corrupted_points[corrupted_bytes-1]
    grid[corrupted_point.r][corrupted_point.c] = "#"

    result = shortest_path_length(grid, Point(0,0), Point(N,N))
    if result == -1:
        print(corrupted_point)
        break

    corrupted_bytes+=1