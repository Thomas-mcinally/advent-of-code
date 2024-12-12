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

def get_sides_from_perimeter_nodes(perimeter_nodes: set, area_nodes: set) -> int:
    sides = 0

    for r, c in perimeter_nodes:
        if is_node_top_perimeter(r,c,area_nodes) and not is_node_top_perimeter(r,c-1,area_nodes):
            sides += 1
        if is_node_bottom_perimeter(r,c,area_nodes) and not is_node_bottom_perimeter(r,c-1,area_nodes):
            sides += 1
        if is_node_left_perimeter(r,c,area_nodes) and not is_node_left_perimeter(r-1,c,area_nodes):
            sides += 1
        if is_node_right_perimeter(r,c,area_nodes) and not is_node_right_perimeter(r-1,c,area_nodes):
            sides += 1

    return sides        
 
def dfs(r, c, char, area_nodes: set, perimeter_nodes:set):
    if r < 0 or c < 0 or r >= ROWS or c >= COLS or grid[r][c] != char:
        perimeter_nodes.add((r,c))
        return
    if (r,c) in area_nodes:
        return
    area_nodes.add((r,c))
    grid[r][c] = "#"
    dfs(r+1, c, char, area_nodes, permiteter_nodes)
    dfs(r-1, c, char, area_nodes, permiteter_nodes)
    dfs(r, c+1, char, area_nodes, permiteter_nodes)
    dfs(r, c-1, char, area_nodes, permiteter_nodes)

cost = 0

for r in range(ROWS):
    for c in range(COLS):
        if grid[r][c] == "#":
            continue

        area_nodes = set()
        permiteter_nodes = set()
        dfs(r,c,grid[r][c],area_nodes, permiteter_nodes)
        sides = get_sides_from_perimeter_nodes(permiteter_nodes, area_nodes)
        cost += len(area_nodes) * sides

print(cost)