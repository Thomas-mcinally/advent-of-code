from decimal import Decimal
import re

def solve_equation_set(x1: int,y1: int,r1: int,x2: int,y2: int,r2: int) -> tuple[Decimal, Decimal]:
    # Button A: X+69, Y+23
    # Button B: X+27, Y+71
    # Prize: X=10000000018641, Y=10000000010279

    # n1*69x + n1*23y + n2*27x + n2*71y = 10000000018641x + 10000000010279y
    # (69*A + 27*B) == 10000000018641
    # (23*A + 71*B) == 10000000010279
    # Two equations with two variables -> one unique solution
    # Visualize as 2 linear graphs in a 2d plane, These lines only cross once. This is the solution
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
    ax, ay, bx, by, px, py = (int(num) for num in re.findall(r'(\d+)', game))
    px += 10000000000000
    py += 10000000000000
    parsed_games.append((ax, ay, bx, by, px, py))

total_tokens = 0
for ax, ay, bx, by, px, py  in parsed_games:
    a_presses, b_presses = solve_equation_set(ax, bx, px, ay, by, py)
    if a_presses < 0 or b_presses < 0 or not (a_presses==int(a_presses) and b_presses==int(b_presses)):
        continue
    total_tokens += a_presses*3 + b_presses
print(total_tokens)
