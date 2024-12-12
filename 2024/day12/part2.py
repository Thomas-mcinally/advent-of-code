with open("input.txt") as f:
    s = f.read().strip()


lines = s.splitlines()
grid = [[char for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])

def is_node_bottom_perimeter(r,c,area_nodes):
    return (r,c) not in area_nodes and (r+1,c) in area_nodes
def is_node_top_perimeter(r,c,area_nodes):
    return (r,c) not in area_nodes and (r-1,c) in area_nodes
def is_node_left_perimeter(r,c,area_nodes):
    return (r,c) not in area_nodes and (r,c+1) in area_nodes
def is_node_right_perimeter(r,c,area_nodes):
    return (r,c) not in area_nodes and (r,c-1) in area_nodes


def get_side_count(area_nodes: set) -> int:
    perimeter_candidates = set()
    for area_r, area_c in area_nodes:
        perimeter_candidates |= set([(area_r+1, area_c), (area_r-1, area_c), (area_r, area_c+1), (area_r, area_c-1)])

    sides = 0
    for r, c in perimeter_candidates:
        if is_node_top_perimeter(r,c,area_nodes) and not is_node_top_perimeter(r,c-1,area_nodes):
            sides += 1
        if is_node_bottom_perimeter(r,c,area_nodes) and not is_node_bottom_perimeter(r,c-1,area_nodes):
            sides += 1
        if is_node_left_perimeter(r,c,area_nodes) and not is_node_left_perimeter(r-1,c,area_nodes):
            sides += 1
        if is_node_right_perimeter(r,c,area_nodes) and not is_node_right_perimeter(r-1,c,area_nodes):
            sides += 1

    return sides     
 
def explore_island(r: int, c: int, char: str, island_nodes: set):
    if r < 0 or c < 0 or r >= ROWS or c >= COLS or grid[r][c] != char:
        return
    if (r,c) in island_nodes:
        return
    island_nodes.add((r,c))
    grid[r][c] = "#"
    explore_island(r+1, c, char, island_nodes)
    explore_island(r-1, c, char, island_nodes)
    explore_island(r, c+1, char, island_nodes)
    explore_island(r, c-1, char, island_nodes)

cost = 0

for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] == "#":
            continue

        area_nodes = set()
        explore_island(r,c,grid[r][c],area_nodes)
        sides = get_side_count(area_nodes)
        cost += len(area_nodes) * sides

print(cost)