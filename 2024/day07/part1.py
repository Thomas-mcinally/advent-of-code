import sys
import time
sys.setrecursionlimit(10000)

with open("input.txt") as f:
    s = f.read().strip()
lines = s.splitlines()

def can_be_correct_starting_from(target: int, operands: list[int], amount: int, i: int) -> bool:
    # caching by (amount, i) not worth it because range of amount is so large
    if i == len(operands):
        return amount == target
    if amount > target:
        return False

    multiply_works = can_be_correct_starting_from(target, operands, amount*operands[i], i+1)
    adding_works = can_be_correct_starting_from(target, operands, amount+operands[i], i+1)
    return  multiply_works or adding_works


part1 = 0
for line in lines:
    colon_idx = line.index(":")
    result = int(line[:colon_idx])

    operands = [int(item) for item in line[colon_idx+2:].split(" ")]

    if can_be_correct_starting_from(result, operands, operands[0], 1):
        part1 += result
print(part1)
