"""
Solved graphically, see part2_before.dot and part2_after.dot
Good problem overview: https://www.reddit.com/r/adventofcode/comments/1hla5ql/2024_day_24_part_2_a_guide_on_the_idea_behind_the/

Discarded idea: Brute force?
~200 gates
need to swap 4pairs (8 in total)
200 ways to choose nr1
199 ways to choose nr2
...
basically 200**8 ways to swap 4 pairs
--> can't brute force, it will take too long to finish computing the result

"""


with open("input.txt") as f:
    s = f.read().strip()
original_lines = s.splitlines()
with open("input_part_2_solved.txt") as f:
    s2 = f.read().strip()
fixed_lines = s2.splitlines()

for l1, l2 in zip(original_lines, fixed_lines):
    if l1 != l2:
        print(f"old: {l1}")
        print(f"new: {l2}")



