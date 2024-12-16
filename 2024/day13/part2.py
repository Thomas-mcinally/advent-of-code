from decimal import Decimal

def solve_equation_set(x1: int,y1: int,r1: int,x2: int,y2: int,r2: int) -> tuple[Decimal, Decimal]:
    # Button A: X+69, Y+23
    # Button B: X+27, Y+71
    # Prize: X=10000000018641, Y=10000000010279

    # n1*69x + n1*23y + n2*27x + n2*71y = 10000000018641x + 10000000010279y
    # (69*A + 27*B) == 10000000018641
    # (23*A + 71*B) == 10000000010279
    # Two equations with two variables -> one unique solution
    # Visualize as 2 linear graphs in a 2d plane, These lines only cross once. This is the solution

    # B = (10000000018641 - 69A)/27
    # 23*A + 71*(10000000018641 - 69A)/27  = 10000000010279
    # 23A -71*69/27 A = 10000000010279 - 71*10000000018641/27
    # A =(10000000010279 - 71*10000000018641/27)/(23 - 71*69/27)
    # B = (10000000018641 - 69*A)/27
    x1: Decimal = Decimal(x1)
    y1: Decimal = Decimal(y1)
    r1: Decimal = Decimal(r1)
    x2: Decimal = Decimal(x2)
    y2: Decimal = Decimal(y2)
    r2: Decimal = Decimal(r2)
    x: Decimal = (r2 - y2*r1/y1) / (x2 - y2*x1/y1)
    y: Decimal = (r1 - x1*x)/y1
    x = x.quantize(Decimal("1.000"))
    y = y.quantize(Decimal("1.000"))
    return (x,y)

with open("input.txt") as f:
    s = f.read().strip()

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
            prize = (int(line[9:comma_pos])+ 10000000000000, int(line[comma_pos+4:]) + 10000000000000)
    parsed_games.append((press_a, press_b, prize))

total_tokens = 0
for press_a, press_b, prize in parsed_games:
    a_presses, b_presses = solve_equation_set(press_a[0], press_b[0], prize[0], press_a[1], press_b[1], prize[1])
    if a_presses < 0 or b_presses < 0 or not (a_presses==int(a_presses) and b_presses==int(b_presses)):
        continue
    total_tokens += a_presses*3 + b_presses
print(total_tokens)
