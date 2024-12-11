from functools import cache


with open("input.txt") as f:
    s = f.read().strip()

stones = [int(num) for num in s.split(" ")]

@cache
def num_stones_starting_from(num, blinks):
    if blinks == 0:
        return 1

    if num == 0:
        result = num_stones_starting_from(1, blinks-1)
    elif len(str(num)) % 2 == 0:
        length = len(str(num))
        num1 = int(str(num)[:length//2])
        num2 = int(str(num)[length//2:])
        result = num_stones_starting_from(num1, blinks-1) + num_stones_starting_from(num2, blinks-1)
    else:
        result = num_stones_starting_from(num*2024, blinks-1)
    return result

result = sum(num_stones_starting_from(stone, 75) for stone in stones)
print(result)