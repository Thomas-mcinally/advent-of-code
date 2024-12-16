with open("small_input.txt") as f:
    s = f.read().strip()

MAX_BUTTON_PRESSES = 100
raw_games = s.split("\n\n")

parsed_games = []
for game in raw_games:
    game_lines = game.splitlines()
    press_a = None
    press_b = None
    prize = None
    for line in game_lines:
        comma_pos = line.index(",")
        if "Button A" in line:
            press_a = (int(line[12:comma_pos]), int(line[comma_pos+4:]))
        elif "Button B" in line:
            press_b = (int(line[12:comma_pos]), int(line[comma_pos+4:]))
        else:
            prize = (int(line[9:comma_pos]), int(line[comma_pos+4:]))
    parsed_games.append((press_a, press_b, prize))

total_tokens = 0
for press_a, press_b, prize in parsed_games:
    game_min_tokens = float("inf")
    for a_presses in range(MAX_BUTTON_PRESSES+1):
        delta_x = prize[0] - press_a[0]*a_presses
        delta_y = prize[1] - press_a[1]*a_presses

        if delta_x / press_b[0] == delta_y / press_b[1] and delta_x%press_b[0]==0:
            b_presses = delta_x // press_b[0]
            if game_min_tokens != float("inf"):
                print("found new sol!")
            game_min_tokens = min(game_min_tokens, a_presses*3 + b_presses)
    
    if game_min_tokens != float("inf"):
        total_tokens += game_min_tokens

print(total_tokens)

