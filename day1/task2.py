RAW_DIGIT_TO_DIGIT = {
    "one": 1,
    "two": 2,
    "three": 3,
    "four": 4,
    "five": 5,
    "six": 6,
    "seven" : 7,
    "eight": 8,
    "nine": 9,
    "1": 1,
    "2": 2,
    "3": 3,
    "4": 4,
    "5": 5,
    "6": 6,
    "7": 7,
    "8": 8,
    "9": 9
}

TOTAL = 0

with open("input.txt", "r") as f:
    lines  = f.readlines()

for line in lines:
    digits = []
    start_i = 0 
    for end_i in range(len(line)):
        if line[start_i:end_i+1] not in RAW_DIGIT_TO_DIGIT:
            print(line[start_i:end_i+1])
            print("Skipped")
            continue
        digits.append(RAW_DIGIT_TO_DIGIT[line[start_i:end_i+1]])
        start_i = end_i + 1


    TOTAL += int(f"{digits[0]}{digits[-1]}")

print(TOTAL)

'''

onine

'''