from decimal import Decimal
import re

def solve_equation_set(x1: Decimal,y1: Decimal,r1: Decimal,x2: Decimal,y2: Decimal,r2: Decimal) -> tuple[Decimal, Decimal]:
    # Button A: X+69, Y+23, Button B: X+27, Y+71, Prize: X=10000000018641, Y=10000000010279
    # n1*69x + n1*23y + n2*27x + n2*71y = 10000000018641x + 10000000010279y
    # (69*A + 27*B) == 10000000018641
    # (23*A + 71*B) == 10000000010279

    # Two equations with two variables -> one unique solution
    # Visualize as 2 linear graphs in a 2d plane, These lines only cross once. This is the solution

    A: Decimal = (r2 - y2*r1/y1) / (x2 - y2*x1/y1)
    B: Decimal = (r1 - x1*A)/y1
    A = A.quantize(Decimal("1.00000"))
    B = B.quantize(Decimal("1.00000"))
    return (A,B)

with open("input.txt") as f:
    s = f.read().strip()

raw_games = s.split("\n\n")

parsed_games = []
for game in raw_games:
    ax, ay, bx, by, px, py = (Decimal(num) for num in re.findall(r'(\d+)', game))
    px += 10000000000000
    py += 10000000000000
    parsed_games.append((ax, ay, bx, by, px, py))

total_tokens = 0
for ax, ay, bx, by, px, py  in parsed_games:
    a_presses, b_presses = solve_equation_set(ax, bx, px, ay, by, py)
    if a_presses < 0 or b_presses < 0 or not (a_presses==int(a_presses) and b_presses==int(b_presses)):
        continue
    total_tokens += int(a_presses)*3 + int(b_presses)
print(total_tokens)
