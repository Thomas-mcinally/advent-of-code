from collections import defaultdict, namedtuple
import heapq


with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()
grid = [[char for char in line] for line in lines]
ROWS, COLS = len(grid), len(grid[0])
STEP_COST = 1
TURN_COST = 1000
DIR_TO_DELTAS = {
    0: (-1, 0), #north
    1: (0, 1),  #east
    2: (1, 0),  #south
    3: (0, -1), #west
}

State = namedtuple("State", ["r", "c", "dir"])

def find_start_pos():
    for r in range(ROWS):
        for c in range(COLS):
            if grid[r][c] == "S":
                return (r,c)
    raise

def dijkstras_shortest_path_to_end_starting_from(start_state: State) -> tuple[State, defaultdict]:
    end_state = State(-1,-1,-1)

    state_to_min_cost = defaultdict(lambda: float("inf"))
    q = [(0, start_state)] #min heap (total_points, state, prev_state)
    while q:
        total_points, state = heapq.heappop(q)
        if total_points > state_to_min_cost[state] or grid[state.r][state.c] == "#":
            continue
        state_to_min_cost[state] = total_points
        if grid[state.r][state.c] == "E":
            end_state = state
            break

        dr, dc = DIR_TO_DELTAS[state.dir]
        
        heapq.heappush(q, (total_points+STEP_COST, State(state.r+dr, state.c+dc, state.dir)))
        heapq.heappush(q, (total_points+TURN_COST, State(state.r, state.c, (state.dir+1)%4)))
        heapq.heappush(q, (total_points+TURN_COST, State(state.r, state.c, (state.dir-1)%4)))

    return end_state, state_to_min_cost

start_r, start_c = find_start_pos()
end_state, state_to_min_cost = dijkstras_shortest_path_to_end_starting_from(State(start_r, start_c, 1))
print(state_to_min_cost[end_state])