from collections import namedtuple, deque
import heapq


Point = namedtuple("Point", ["r", "c"])


def dijkstras_best_path(grid, start: Point, end: Point):
    ROWS, COLS = len(grid), len(grid[0])
    seen = set()
    q = [(-float("inf"), start)] #(-score, point)
    while q:
        score, cur = heapq.heappop(q)
        if cur in seen:
            continue
        if cur == end:
            return -1*score
        seen.add(cur)
        for next_r, next_c in [(cur.r+1, cur.c), (cur.r-1, cur.c), (cur.r, cur.c+1), (cur.r, cur.c-1)]:
            if next_r<0 or next_r>=ROWS or next_c<0 or next_c>=COLS:
                continue
            next_score = max(score, -1*grid[next_r][next_c])
            heapq.heappush(q, (next_score, Point(next_r, next_c)))
    return -1


with open("input.txt") as f:
    s = f.read().strip()
corrupted_points = []
for line in s.splitlines():
    r,c = line.split(",")
    corrupted_points.append(Point(int(r), int(c)))

N = 70
grid = [[float("inf") for _ in range(N+1)] for _ in range(N+1)]
for i,point in enumerate(corrupted_points):
    grid[point.r][point.c] = i

result = dijkstras_best_path(grid, Point(0,0), Point(N,N))
print(corrupted_points[result])
