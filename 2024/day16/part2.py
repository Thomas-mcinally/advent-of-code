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

def dijkstras_shortest_path_to_end_starting_from(start_state: State) -> tuple[State, defaultdict, defaultdict]:
    dummy_state = State(-1,-1,-1)
    end_state = dummy_state

    state_to_min_cost = defaultdict(lambda: float("inf"))
    state_to_prev_states = defaultdict(set)
    q = [(0, start_state, dummy_state)] #min heap (total_points, state, prev_state)
    while q:
        total_points, state, prev_state = heapq.heappop(q)
        if total_points > state_to_min_cost[state] or grid[state.r][state.c] == "#":
            continue
        if total_points == state_to_min_cost[state] and prev_state != dummy_state:
            state_to_prev_states[state].add(prev_state)
        elif prev_state != dummy_state:
            state_to_prev_states[state] = {prev_state}
        state_to_min_cost[state] = total_points
        if grid[state.r][state.c] == "E":
            end_state = state
            break

        dr, dc = DIR_TO_DELTAS[state.dir]
        
        heapq.heappush(q, (total_points+STEP_COST, State(state.r+dr, state.c+dc, state.dir), state))
        heapq.heappush(q, (total_points+TURN_COST, State(state.r, state.c, (state.dir+1)%4), state))
        heapq.heappush(q, (total_points+TURN_COST, State(state.r, state.c, (state.dir-1)%4), state))

    return end_state, state_to_min_cost, state_to_prev_states

def backtrace_path(end_state, state_to_prev_states):
    # Backtrace from E, using state_to_prev_states
    min_path_nodes = set()
    q = [end_state]
    while q:
        state = q.pop()
        min_path_nodes.add((state.r,state.c))
        for prev_state in state_to_prev_states[state]:
            q.append(prev_state)

    for r in range(ROWS):
        for c in range(COLS):
            if (r,c) in min_path_nodes:
                grid[r][c] = "O"
    with open("output.txt", "w") as file:
        # Iterate through each sublist
        for row in grid:
            # Join the sublist into a single string with spaces and write it to the file
            file.write(" ".join(row) + "\n")
    return min_path_nodes


start_r, start_c = find_start_pos()
end_state, state_to_min_cost, state_to_prev_states = dijkstras_shortest_path_to_end_starting_from(State(start_r, start_c, 1))
min_path_nodes = backtrace_path(end_state, state_to_prev_states)
print(len(min_path_nodes))